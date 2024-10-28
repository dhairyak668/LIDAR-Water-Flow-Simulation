#include <stdio.h>
#include <stdlib.h>
#include <float.h>  //for DBL_MAX 
#include <math.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

void stat1(){

    double x, y, height;
    double minZ = DBL_MAX; //better than setting to null. Thus even the first value will be considered min/max.
    double maxZ = -DBL_MAX; 

    double totalHeight = 0.0;
    int count = 0;

    double minX = 0, minY = 0, maxX = 0, maxY = 0;

    //will run until fscanf reads 3 inputs(returns 3). will exit at any error or EOF
    while(fscanf(stdin, "%lf %lf %lf", &x, &y, &height) == 3) { 
        
        if(height < minZ){
            minX = x;
            minY = y;
            minZ = height;
        }

        if(height > maxZ){
            maxX = x;
            maxY = y;
            maxZ = height;
        }

        totalHeight += height;
        count++;
    }

    double avgHeight = (count > 0) ? (totalHeight/count) : 0.0;

    printf("Minimum height: %lf at (%lf, %lf)\n",minZ, minX, minY);
    printf("Maximun height: %lf at (%lf, %lf)\n",maxZ, maxX, maxY);
    printf("Average height: %lf\n", avgHeight);
}

pointcloud_t* readPointCloudData(FILE* stream){
    pointcloud_t* pointcloud = malloc(sizeof(pointcloud_t));
    if(!pointcloud){
        fprintf(stderr,"unable to allocate memory for pointcloud_t in readPointCloudData\n");
        return NULL;
    }
    pointcloud->points = malloc(sizeof(List));
    if(!(pointcloud->points)){
        fprintf(stderr,"unable to allocate memory for List in pointcloud_t in readPointCloudData\n");
        free(pointcloud);
        return NULL;
    }
    if(fscanf(stream,"%d",&(pointcloud->cols)) != 1){
        fprintf(stderr,"Incorrect File Structure. Error in reading number of columns in pointcloud_t in readPointCloudData\n");
        free(pointcloud->points);
        free(pointcloud);
        return NULL;
    }

    if(listInit(pointcloud->points,sizeof(pcd_t)) != 0){ //returns 1 on fail
        free(pointcloud->points);
        free(pointcloud);
        return NULL;
    }

    double x,y,z;
    double minX = NAN, minY = NAN, minZ = NAN, maxX = NAN, maxY = NAN, maxZ = NAN;
    
    while (fscanf(stream,"%lf %lf %lf",&x,&y,&z)==3)
    {
        pcd_t* point = malloc(sizeof(pcd_t));
        if(point == NULL){
            fprintf(stderr,"error in allocating memory for point");
            // free(pc->data);
            // free(pc);
            free(pointcloud->points->data);
            free(pointcloud->points);
            free(pointcloud);
            return NULL;
        }

        point->x = x;
        point->y = y;
        point->z = z;
        minX = (isnan(minX)) ? x : (x < minX) ? x : minX;
        minY = (isnan(minY)) ? y : (y < minY) ? y : minY;
        minZ = (isnan(minZ)) ? z : (z < minZ) ? z : minZ;
        maxX = (isnan(maxX)) ? x : (x > maxX) ? x : maxX;
        maxY = (isnan(maxY)) ? y : (y > maxY) ? y : maxY;
        maxZ = (isnan(maxZ)) ? z : (z > maxZ) ? z : maxZ;

        //water initialization should be done in other method
        // point->wd = 0.0;

        listAddEnd(pointcloud->points, point);
        //since listAddEnd copies point to l->data, memory for point will be wasted
        free(point);
    }
    pointcloud->rows = (pointcloud->points->size)/(pointcloud->cols);

    pointcloud->stats.maxX = maxX;
    pointcloud->stats.minX = minX;
    pointcloud->stats.minY = minY;
    pointcloud->stats.maxY = maxY;
    pointcloud->stats.minZ = minZ;
    pointcloud->stats.maxZ = maxZ;
    pointcloud->stats.heightRange = maxZ-minZ;
    pointcloud->stats.xInterval = (maxX-minX)/(pointcloud->cols -1);
    pointcloud->stats.yInterval = (maxY-minY)/(pointcloud->rows -1);

    return pointcloud;   
}

int initializeWatershed(pointcloud_t * pointcloud){

    if(!pointcloud){
        fprintf(stderr,"invalid pointer to pointcloud_t provided\n");
        return 1;
    }

    List* newList = malloc(sizeof(List));
    if(!newList){
        fprintf(stderr,"failed to allocate memory for newList in initializeWaterShed\n");
        return 1;
    }

    newList->data = malloc(getMaxListSize(pointcloud->points));
    if(!newList->data){
        fprintf(stderr,"failed to allocate memory for data in newList in initializeWaterShed\n");
        free(newList);
        return 1;
    }

    newList->max_element_size = pointcloud->points->max_element_size;
    newList->size = pointcloud->points->size;
    newList->max_size = pointcloud->points->max_size;

    double minX = pointcloud->stats.minX;
    double minY = pointcloud->stats.minY;
    double xInterval = pointcloud->stats.xInterval;
    double yInterval = pointcloud->stats.yInterval;
    int rows = pointcloud->rows;
    int cols = pointcloud->cols;

    for(int i = 0; i<rows;i++){
        for(int j = 0; j<cols;j++){
            pcd_t* point = (pcd_t*)listGet(pointcloud->points,INDEX(i,j,cols));
            if (!point) {
                fprintf(stderr, "Error in retrieving point from original list in initializeWatershed\n");
                free(newList->data);
                free(newList);
                return 1;
            }
            point->wd = 0.0;

            int colIndex = (int)((point->x - minX)/xInterval);
            int rowIndex = (int)((point->y - minY)/yInterval);
            if(listSet(newList,INDEX(rowIndex,colIndex,cols),point) != 0){
                fprintf(stderr,"Unable to copy data from original list to newList in initializeWatershed\n");
                free(newList->data);
                free(newList);
                return 1;
            }
        }
    }
    free(pointcloud->points->data);
    free(pointcloud->points);
    pointcloud->points = newList;

    for(int i = 0; i<rows;i++){
        for(int j = 0; j<cols;j++){
            pcd_t* point = (pcd_t*)listGet(pointcloud->points,INDEX(i,j,cols));
            point->north = (i == rows-1) ? NULL : (pcd_t*)listGet(pointcloud->points,INDEX(i+1,j,cols));
            point->south = (i == 0) ? NULL : (pcd_t*)listGet(pointcloud->points,INDEX(i-1,j,cols));
            point->east = (j == cols-1) ? NULL : (pcd_t*)listGet(pointcloud->points,INDEX(i,j+1,cols));
            point->west = (j == 0) ? NULL : (pcd_t*)listGet(pointcloud->points,INDEX(i,j-1,cols));
        }
    }

    return 0;

}

void imagePointCloud(pointcloud_t* pc, char* filename){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    int height = pc->rows;
    int width = pc->cols;
    Bitmap* bmp = bm_create(width,height);
    if(!bmp){
        fprintf(stderr,"unable to create Bitmap.\n");
        return;
    }

    for(int i = 0; i<height;i++){
        for(int j = 0; j<width;j++){
            pcd_t* point = (pcd_t*)listGet(pc->points,INDEX(i,j,width));
            if (!point) {
                fprintf(stderr, "Error in retrieving point from list in imagePointCloud\n");
                bm_free(bmp);
                return;
            }
            unsigned int color = mapHeightToColor(point->z, &(pc->stats));
            bm_set(bmp, j, i, color);
        }
    }
    if(bm_save(bmp,filename) != 1){ //returns 1 on success
        fprintf(stderr,"Unable to save bitmap.\n");
        bm_free(bmp);
        return;
    }
    bm_free(bmp);
}

void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    int height = pc->rows;
    int width = pc->cols;
    Bitmap* bmp = bm_create(width,height);
    if(!bmp){
        fprintf(stderr,"unable to create Bitmap.\n");
        return;
    }

    for(int i = 0; i<height;i++){
        for(int j = 0; j<width;j++){
            pcd_t* point = (pcd_t*)listGet(pc->points,INDEX(i,j,width));
            if (!point) {
                fprintf(stderr, "Error in retrieving point from list in imagePointCloudWater\n");
                bm_free(bmp);
                return;
            }
            unsigned int color = mapWaterDepthToColor(point, maxwd, &(pc->stats));
            bm_set(bmp, j, i, color);
        }
    }
    if(bm_save(bmp,filename) != 1){
        fprintf(stderr,"Unable to save bitmap.\n");
        bm_free(bmp);
        return;
    }
    bm_free(bmp);
}


void watershedAddUniformWater(pointcloud_t* pc, double amount){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    for(int i = 0; i<pc->rows;i++){
        for(int j = 0; j<pc->cols;j++){
            pcd_t* point = (pcd_t*)listGet(pc->points,INDEX(i,j,pc->cols));
            if (!point) {
                fprintf(stderr, "Error in retrieving point from list in watershedAddUniformWater\n");
                return;
            }
            point->wd += amount;
        }
    }
}

void watershedStep(pointcloud_t* pc){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    double* changes = malloc(sizeof(double) * pc->points->size);
    if(!changes){
        fprintf(stderr,"Error in allocating memory for changes[Array] in watershedStep\n");
        return;
    }
    for(int index = 0; index < pc->points->size; index++){
        pcd_t* point = (pcd_t*)listGet(pc->points,index);
        // if (!point) handled in calculateChangeInWater
        changes[index] = calculateChangeInWater(point,pc->wcoef,pc->ecoef);
    }

    for(int index = 0; index < pc->points->size; index++){
        pcd_t* point = (pcd_t*)listGet(pc->points,index);
        if(!point){
            fprintf(stderr,"Error in retrieving point from list in watershedStep\n");
            free(changes);
            return;
        }
        point->wd += changes[index];
    }
    free(changes);
}

unsigned int mapWaterDepthToColor(pcd_t* point, double maxwd, Stats* s){
    if(!point){
        fprintf(stderr,"Invalid pointer to pcd_t in mapWaterDepthToColor\n");
        return 0;
    }
    if(!s){
        fprintf(stderr,"Invalid pointer to Stats in mapWaterDepthToColor\n");
        return 0;
    }
    double bucket = (point->z - s->minZ)/s->heightRange;
    unsigned char greyscale = (unsigned char)(bucket * 255);
    double blueRatio = fmin((point->wd/maxwd),1.0);
    // printf("blueRatio: %lf\n",blueRatio);
    unsigned char blueScale = (blueRatio == 1.0) ? (unsigned char)(255) : (unsigned char)(greyscale*(1.0+blueRatio));
    greyscale = (unsigned char)(greyscale * (1.0 - blueRatio));
    return bm_rgb(greyscale,greyscale,255);
}


unsigned int mapHeightToColor(double height, Stats* s){
    if(!s){
        fprintf(stderr,"Invalid pointer to Stats in mapHeightToColor\n");
        return 0;
    }
    double bucket = (height - s->minZ)/s->heightRange;
    unsigned char greyscale = (unsigned char)(bucket * 255);
    return bm_rgb(greyscale,greyscale,greyscale);
}

void setWcoef(pointcloud_t* pc, double wcoef){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    pc->wcoef = wcoef;
}

void setEcoef(pointcloud_t* pc, double ecoef){
    if(!pc){
        fprintf(stderr,"Invalid pointer to pointcloud_t\n");
        return;
    }
    pc->ecoef = ecoef;
}

double calculateFunc(pcd_t* point, pcd_t* neighbor, double wcoef){
    if(!point || !neighbor){
        return 0.0;
    }
    return (point->z + point->wd - neighbor->z - neighbor->wd) * wcoef;
}

double calculateChangeInWater(pcd_t* point,double wcoef, double ecoef){
    if(!point){
        return 0.0;
    }
    double change = 0.0;
    change += calculateFunc(point,point->north,wcoef);
    change += calculateFunc(point,point->south,wcoef);
    change += calculateFunc(point,point->east,wcoef);
    change += calculateFunc(point,point->west,wcoef);
    return (change - (point->wd * ecoef));
}


