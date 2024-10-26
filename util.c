#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <string.h> 
#include <float.h>


void* allocateArray(int row, int column){

    double **arr = malloc(sizeof(double *) * row);

    if(arr == NULL){
        fprintf(stderr, "Error in allocating memory for array\n");
        return NULL;
    }

    for(int i = 0; i < row; i++){
        arr[i] = malloc(sizeof(double) * column);

        if(arr[i] == NULL){
            fprintf(stderr, "Error in allocating memory for array\n");

            //makes sure the memory for the previously allocated rows is freed before freeing main array
            for(int j = 0 ;j <i; j++,free(arr[j]));

            free(arr);
            return NULL;
        }
    }

    return arr;
}


int listInit(List* l, int max_elmt_size){

    // l = malloc(sizeof(List));
    // if(!l){
    //     fprintf(stderr,"Error in allocating memory for List\n");
    //     return 1;
    // }

    l->max_size = 10;
    l->max_element_size = max_elmt_size;
    l->size = 0;
    l->data = malloc(getMaxListSize(l));

    if(l->data == NULL){
        fprintf(stderr, "Error in allocating memory for data in listInit\n");
        // free(l);
        return 1;
    }

    return 0;
}

void listAddEnd(List* l, void* elmt){

    if(!l){
        fprintf(stderr,"invalid pointer to list\n");
        return;
    }
    
    if(!elmt){
        fprintf(stderr,"invalid pointer to element\n");
        return;
    }
    
    if(l->size >= l->max_size){
        l->max_size *= 2;

        //using a second pointer to allocate double the size of memory 
        void * temp = malloc(getMaxListSize(l));
        if(temp == NULL){
            fprintf(stderr, "Error in allocating memory for temp in listAddEnd\n");
            return;
        }
        memcpy(temp,l->data,getCurrentListSize(l));
        free(l->data);
        l->data = temp;
    }
    
    //cast to char* for better pointer arithematic
    memcpy((char *)l->data + (getCurrentListSize(l)),elmt,l->max_element_size);
    l->size++;
}

void* listGet(List* l, int index){
    
    if(!l){
        fprintf(stderr,"invalid pointer to list\n");
        return NULL;
    }

    if(index < 0 || index >= l->size){
        fprintf(stderr,"index out of bounds\n");
        return NULL;
    }
    
    return (char*)l->data + (index * l->max_element_size);
}

int listSet(List* l, int index, void* elmt){
    if(!l){
        fprintf(stderr,"Invalid List to listSet\n");
        return -1;
    }
    if(index < 0 || index > l->max_size){
        fprintf(stderr,"Invalid index value to listSet\n");
        return -1;
    }
    memcpy((char *)l->data + (index * l->max_element_size),elmt,l->max_element_size);
    return 0;
}

int getMaxListSize(List* l){
    return (l->max_size) * (l->max_element_size);
}

int getCurrentListSize(List* l){
    return (l->size) * (l->max_element_size);
}

void computeStats(List* l, Stats* stats){
    
    stats->minZ = DBL_MAX;
    stats->maxZ = -DBL_MAX;
    stats->minX = DBL_MAX;
    stats->maxX = -DBL_MAX;
    stats->minY = DBL_MAX;
    stats->maxY = -DBL_MAX;

    for (int i = 0; i < l->size; i++) {
        pcd_t* point = (pcd_t*)listGet(l, i);
        if (point->z < stats->minZ) stats->minZ = point->z;
        if (point->z > stats->maxZ) stats->maxZ = point->z;
        if (point->x < stats->minX) stats->minX = point->x;
        if (point->x > stats->maxX) stats->maxX = point->x;
        if (point->y < stats->minY) stats->minY = point->y;
        if (point->y > stats->maxY) stats->maxY = point->y;

    }

    stats->heightRange = stats->maxZ - stats->minZ;
}




// int main(int argc, char const *argv[])
// {
//     /* code */

//     double ** arr = (double **)allocateArray(3,5);

//     if(arr == NULL){
//         exit(-1);
//     }
//     for(int i = 0; i<3; i++){
//         for(int j = 0; j<5; j++){
//             printf("%lf ", arr[i][j]);
//         }
//         printf("\n");
//     }
//     freeArray(arr,3);
//     return 0;
// }
