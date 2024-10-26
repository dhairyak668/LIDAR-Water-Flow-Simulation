#pragma once
#include "util.h"



/**
 * Function to calculate and print the Minimum Height, Maximum Height 
 * along with their respective (x, y) coordinates and Average Height.
 * Reads from standard input.
 */
void stat1();

/**
 * Reads point cloud data from the given stream and initializes 
 * a List structure with the points.
 * expects memory allocation (malloc call) for list is already done
 * 
 * @param stream The input stream to read the data from.
 * @param rasterWidth Pointer to store the number of columns.
 * @param pc Pointer to the List structure that will hold the point cloud data.
 */
void readPointCloudData(FILE* stream, int *rasterWidth, List* pc);

/**
 * Creates a bitmap image from the point cloud data and saves it to the given filename.
 * 
 * @param l Pointer to the List structure containing point cloud data.
 * @param width The width of the image to be created.
 * @param filename The name of the file to save the bitmap image.
 */
void imagePointCloud(List* pointsList, int width, char* filename);

int initializeWatershed(pointcloud_t *);

/**
 * Maps a height value to a grayscale color based on its position within the given stats.
 * 
 * @param height The height value to map to color.
 * @param s Pointer to the Stats structure containing height statistics.
 * @return The RGB color value representing the grayscale color.
 */
unsigned int mapHeightToColor(double height, Stats* s);

