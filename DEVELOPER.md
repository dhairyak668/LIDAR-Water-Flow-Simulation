# Developer Documentation for LIDAR Water Flow Simulation

## Overview
This project simulates water flow over terrain using LIDAR data, providing insight into where water is likely to pool based on terrain height.

## Code Structure
### File Organization
- `pointcloud.c`: Contains the main implementation of the program, including the `stat1` function. Also has `main` method to trial execute stat1.
- `pointcloud.h`: Header file containing function prototypes and necessary includes.
- `Makefile`: Used to compile the project.
- `testfiles`: Directory with test files in .xyz format

### Key Functions
#### `pointcloud.c`
##### `stat1`
```c
void stat1(const char *filename);