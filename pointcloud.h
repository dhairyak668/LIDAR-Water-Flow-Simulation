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
 * a pointcloud structure with the List of points and other variables.
 * 
 * @param stream The input stream to read the data from.
 * @return A pointer to the pointcloud_t structure initialized with the data from stream.
 */
pointcloud_t* readPointCloudData(FILE* stream);

/**
 * Initializes the water depth (wd) value for all points to 0.
 *
 * This function sorts the points in the point cloud into a new list based on their x and y coordinates.
 * The function also initializes the north, south, east, and west pointers for each point with (minX, minY) being South-West.
 *
 * @param pointcloud A pointer to the pointcloud_t structure to be initialized.
 * @return An integer indicating the success or failure of the initialization.
 *         Typically, a return value of 0 indicates success, while a non-zero
 *         value indicates an error.
 */
int initializeWatershed(pointcloud_t *);

/**
 * Creates a bitmap image from the point cloud data and saves it to the given filename.
 * 
 * @param pointList Pointer to the pointcloud_t structure containing point cloud data.
 * @param filename The name of the file to save the bitmap image.
 */
void imagePointCloud(pointcloud_t* pc, char* filename);

/**
 * Maps a height value to a grayscale color based on its position within the given stats.
 * 
 * @param height The height value to map to color.
 * @param s Pointer to the Stats structure containing height statistics.
 * @return The RGB color value representing the grayscale color.
 */
unsigned int mapHeightToColor(double height, Stats* s);

