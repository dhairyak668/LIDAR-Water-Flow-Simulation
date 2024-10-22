coms3270P1

LIDAR Water Flow Simulation

Project Overview

This project simulates water flow over terrain using LIDAR data. It processes point cloud data to determine where water is likely to pool based on terrain height.

Features
- Stat1
    - Reads point cloud data in XYZ from stdin
    - Calculates and displays:
        - Minimum height and its coordinates
        - Maximum height and its coordinates
        - Average height of the terrain

- ReadPointCloud
    - Reads point cloud data from a specified input stream and populates a dynamic list with the data points

- ImagePointCloud
    - Generates a bitmap image of the terrain using the processed point cloud data.

Requirements
- C compiler (e.g., GCC)
- Make utility

How to Build
1. Clone the repository:

   git clone https://git.las.iastate.edu/dhairyak/coms3270p1.git
   cd coms3270p1

Known Errors
- stat1 function does not check for .xyz format. 
- readPointCloud and listInit assumes list pointer in argument is allocated beforehand
- stderr prints in case of memory allocation fail or file reading fail in the code. Free's memory and returns from code.