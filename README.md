# coms3270P1

# LIDAR Water Flow Simulation

## Project Overview
This project simulates water flow over terrain using LIDAR data. It processes point cloud data to determine where water is likely to pool based on terrain height.

## Features
- Stat1
    - Reads point cloud data in XYZ format
    - Calculates and displays:
        - Minimum height and its coordinates
        - Maximum height and its coordinates
        - Average height of the terrain

## Requirements
- C compiler (e.g., GCC)
- Make utility

## File Structure
- `pointcloud.c`: Contains the main implementation of the program.
- `pointcloud.h`: Header file with function declarations.
- `Makefile`: To compile the project.
- `test1.xyz`: Sample data file for testing with average height 1.
- `test.xyz` : Sample data file for testing with 1,000,000 entries

## How to Build
1. Clone the repository:
   ```bash
   git clone https://git.las.iastate.edu/dhairyak/coms3270p1.git
   cd coms3270p1

## Known Errors
- stat1 function does not check for .xyz file format. Accepts general char stream for filename
- stat1 prints error statement in case of error in opening file
- main method prints error statement incase of wrong input arguments