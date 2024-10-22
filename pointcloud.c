#include <stdio.h>
#include <stdlib.h>
#include <float.h>  //for DBL_MAX 
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"


void stat1(){

    double x, y, height;
    double minHeight = DBL_MAX; //better than setting to null. Thus even the first value will be considered min/max.
    double maxHeight = -DBL_MAX; 

    double totalHeight = 0.0;
    int count = 0;

    double minX = 0, minY = 0, maxX = 0, maxY = 0;

    //will run until fscanf reads 3 inputs(returns 3). will exit at any error or EOF
    while(fscanf(stdin, "%lf %lf %lf", &x, &y, &height) == 3) { 
        
        if(height < minHeight){
            minX = x;
            minY = y;
            minHeight = height;
        }

        if(height > maxHeight){
            maxX = x;
            maxY = y;
            maxHeight = height;
        }

        totalHeight += height;
        count++;
    }

    double avgHeight = (count > 0) ? (totalHeight/count) : 0.0;

    printf("Minimum height: %lf at (%lf, %lf)\n",minHeight, minX, minY);
    printf("Maximun height: %lf at (%lf, %lf)\n",maxHeight, maxX, maxY);
    printf("Average height: %lf\n", avgHeight);
}


void readPointCloudData(FILE* stream, int* rasterWidth, List* pc){
    
    if(fscanf(stream,"%d",rasterWidth) != 1){
        fprintf(stderr,"Error in reading number of columns \n");
        return;
    }

    if(listInit(pc,sizeof(pcd_t)) == 1){
        return;
    }

    double x,y,z;
    
    while (fscanf(stream,"%lf %lf %lf",&x,&y,&z)==3)
    {
        pcd_t* point = malloc(sizeof(pcd_t));
        if(point == NULL){
            fprintf(stderr,"error in allocating memory for point");
            // free(pc->data);
            // free(pc);
            return;
        }
        point->x = x;
        point->y = y;
        point->z = z;
        point->waterAmt = 0.0;

        listAddEnd(pc, point);
        //since listAddEnd copies point to l->data memory for point will be wasted
        free(point);
    }   
}

void imagePointCloud(List* l, int width, char* filename){
    Stats stats;
    computeStats(l, &stats);

    int height = l->size / width;
    Bitmap* bmp = bm_create(width,height);
    if(!bmp){
        fprintf(stderr,"unable to create Bitmap.\n");
        return;
    }

    for(int i = 0; i<height;i++){
        for(int j = 0; j<width;j++){
            pcd_t* point = (pcd_t*)listGet(l,INDEX(i,j,width)); //might replace macro with actual expression
            unsigned int color = mapHeightToColor(point->z, &stats);
            bm_set(bmp, j, i, color);
        }
    }
    if(bm_save(bmp,filename) != 1){
        fprintf(stderr,"Unable to save bitmap.\n");
    }
    bm_free(bmp);

}

unsigned int mapHeightToColor(double height, Stats* s){
    double bucket = (height - s->minHeight)/s->range;
    unsigned char greyscale = (unsigned char)(bucket * 255);
    return bm_rgb(greyscale,greyscale,greyscale);
}


