#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointcloud.h"

int main(int argc, char* argv[]) {
    if (argc < 8 || argc > 9) {
        fprintf(stderr, "Usage: %s <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <maxwdepth> [<seq>]\n", argv[0]);
        return 1;
    }

    char* ifile = argv[1];
    int iter, seq = 0;
    sscanf(argv[2], "%d", &iter);
    double iwater, wcoef, ecoef, maxwdepth;
    sscanf(argv[3], "%lf", &iwater);
    sscanf(argv[4], "%lf", &wcoef);
    sscanf(argv[5], "%lf", &ecoef);
    char* ofilebase = argv[6];
    sscanf(argv[7], "%lf", &maxwdepth);
    if (argc == 9) {
        sscanf(argv[8], "%d", &seq);
    }
    printf("argc: %d\n", argc);
    printf("Input file: %s\n", ifile);
    printf("Iterations: %d\n", iter);
    printf("Initial water: %f\n", iwater);
    printf("Water coefficient: %f\n", wcoef);
    printf("Evaporation coefficient: %f\n", ecoef);
    printf("Output file base: %s\n", ofilebase);
    printf("Max water depth: %f\n", maxwdepth);
    printf("Sequence: %d\n", seq);

    FILE* inputFile = fopen(ifile, "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening input file: %s\n", ifile);
        return 1;
    }

    pointcloud_t* pc = readPointCloudData(inputFile);
    fclose(inputFile);
    if (!pc) {
        fprintf(stderr, "Error reading point cloud data\n");
        return 1;
    }

    pc->wcoef = wcoef;
    pc->ecoef = ecoef;

    if (initializeWatershed(pc) != 0) {
        fprintf(stderr, "Error initializing watershed\n");
        free(pc->points->data);
        free(pc->points);
        free(pc);
        return 1;
    }

    watershedAddUniformWater(pc, iwater);

    for (int i = 0; i < iter; i++) {
        watershedStep(pc);
        if (seq > 0 && (i + 1) % seq == 0) {
            char filename[256];
            sprintf(filename, "%s%d.gif", ofilebase, i + 1);
            imagePointCloudWater(pc, maxwdepth, filename);
        }
    }

    char finalFilename[256];
    sprintf(finalFilename, "%s.gif", ofilebase);
    imagePointCloudWater(pc, maxwdepth, finalFilename);

    free(pc->points->data);
    free(pc->points);
    free(pc);

    return 0;
}