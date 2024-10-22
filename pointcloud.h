#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "util.h"

void stat1(const char *filename);
void readPointCloudData(FILE* stream, int *rasterWidth, List* pc);
void imagePointCloud(List* l, int width, char* filename);
unsigned int mapHeightToColor(double height, Stats* s);

#endif