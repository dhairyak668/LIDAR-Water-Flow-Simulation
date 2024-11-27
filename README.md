# coms3270P1 LIDAR Water Flow Simulation

## Project Overview

This project simulates water flow over terrain using LIDAR data. It processes point cloud data to determine where water is likely to pool based on terrain height.

## Features
- Stat1
    - Reads point cloud data in XYZ from stdin
    - Calculates and displays:
        - Minimum height and its coordinates
        - Maximum height and its coordinates
        - Average height of the terrain

    #### Usage
    1. To run the Stat1 analysis, use the following command:

    ```sh
    ./stat < inputfile.xyz
    ```

    2. The `inputfile.xyz` file should contain the point cloud data in XYZ format.

- ReadPointCloud
    - Reads point cloud data from a specified input stream and populates a dynamic list with the data points

- ImagePointCloud
    - Generates a bitmap image of the terrain using the processed point cloud data.

        #### Usage
        1. To generate the bitmap image, use the following command:

        ```sh
        ./display inputfile.xyz
        ```

        2. The `inputfile.xyz` file should contain the processed point cloud data.

        3. the output will be a .gif file


    - Watershed
        - Simulates water flow over the terrain
        - Identifies and marks watershed areas where water is likely to accumulate
        - Outputs the watershed regions as a separate data file for further analysis

        #### Usage
        1. To run the watershed simulation, use the following command:

        ```sh
        /watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <maxwd> <seq>
        ```

    2. The `<ifile>.xyz` file should contain the point cloud data, and the `<ofilebase>.gif` file will contain the results of the simulation.


## Requirements
- C compiler (e.g., GCC)
- Make utility

## How to Build
1. Clone the repository:

   git clone https://git.las.iastate.edu/dhairyak/coms3270p1.git
   cd coms3270p1

## Known Errors
- stat1 function does not check for .xyz format. 
- readPointCloud and listInit assumes list pointer in argument is allocated beforehand
- stderr prints in case of memory allocation fail or file reading fail in the code. Free's memory and returns from code.