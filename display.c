#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"


int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr,"Use as: %s <filename>\n",argv[0]);
        return 1;
    }

    char* inputFileName = argv[1];
    FILE* inputFile = fopen(inputFileName,"r");
    if(!inputFile){
        fprintf(stderr,"could not open file %s\n",inputFileName);
        return 1;
    }

    // List* l = malloc(sizeof(List));
    // if(!l){
    //     fprintf(stderr,"Error in allocating memory for List\n");
    //     fclose(inputFile);
    //     return 1;
    // }

    // int width;

    pointcloud_t* pc = readPointCloudData(inputFile);
    fclose(inputFile);
    if (!pc) {
        fprintf(stderr, "Error reading point cloud data\n");
        return 1;
    }
    char outfile[] = "out.gif";
    imagePointCloud(pc,outfile);
    printf("GIF saved as %s\n",outfile);

    
    return 0;
}

