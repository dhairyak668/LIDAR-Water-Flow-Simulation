# Developer Documentation for LIDAR Water Flow Simulation

## Overview
This project simulates water flow over terrain using LIDAR data, providing insight into where water is likely to pool based on terrain height.

## Code Structure
### File Organization
- `pointcloud.c`: Contains the main implementation of the program, including the stat1, readPointCloudData, and imagePointCloud functions.
- `pointcloud.h`: Header file containing function prototypes for point cloud processing functions.
- `util.c`: Implementation of utility functions for managing dynamic lists, memory allocation, and computing statistics.
- `util.h`: Header file declaring the utility functions.
- `bmp.c`: Implementation of functions for creating and manipulating bitmap images.
- `bmp.h`: Header file declaring bitmap functions.
- `parta.c`: Implements main method to test stat1 function
- `display.c`: Implements main method to test partb
- `watershed.c`: Implements water flow simulation over the terrain.
- `Makefile`: Used to compile the project.
- `testfiles`: Directory containing test files in .xyz format.

### Key Functions
#### `pointcloud.c`
```c
1) void stat1();
2) pointcloud_t* readPointCloudData(FILE* stream);
3) void imagePointCloud(List* l, int width, char* filename);
4) void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);
5) void watershedAddUniformWater(pointcloud_t* pc, double amount);
6) void watershedStep(pointcloud_t* pc);
7) int initializeWatershed(pointcloud_t *);
8) unsigned int mapWaterDepthToColor(pcd_t* point, double maxwd, Stats* s);
9) unsigned int mapHeightToColor(double height, Stats* s);
10) void setWcoef(pointcloud_t* pc, double wcoef);
11) void setEcoef(pointcloud_t* pc, double ecoef);
12) double calculateFunc(pcd_t* point, pcd_t* neighbor, double wcoef);
13) double calculateChangeInWater(pcd_t* point,double wcoef, double ecoef);

```

####`util.c` 
```c
1) void* allocateArray(int rows, int columns);
2) int listInit(List* l, int max_elmt_size);
3) void listAddEnd(List* l, void* elmt);
4) void* listGet(List* l, int index);
5) int getMaxListSize(List* l);
6) int getCurrentListSize(List* l);
7) void computeStats(List* l, Stats* stats);
```
