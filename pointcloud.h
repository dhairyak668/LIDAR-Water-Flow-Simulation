#pragma once
#include "util.h"

typedef struct{
    List* points;
    int rows;
    int cols;
    Stats stats;
    double wcoef;
    double ecoef;
}pointcloud_t;

/**
 * @brief Function to calculate and print the Minimum Height, Maximum Height 
 * along with their respective (x, y) coordinates and Average Height.
 * Reads from standard input.
 */
void stat1();

/**
 * @brief Reads point cloud data from the given stream and initializes 
 * a pointcloud structure with the List of points and other variables.
 * 
 * @param stream The input stream to read the data from.
 * @return A pointer to the pointcloud_t structure initialized with the data from stream.
 */
pointcloud_t* readPointCloudData(FILE* stream);

/**
 * @brief Initializes the water depth (wd) value for all points to 0.
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
 * @brief Creates a bitmap image from the point cloud data and saves it to the given filename.
 * 
 * @param pointList Pointer to the pointcloud_t structure containing point cloud data.
 * @param filename The name of the file to save the bitmap image.
 */
void imagePointCloud(pointcloud_t* pc, char* filename);

/**
 * @brief Processes a point cloud to simulate water effects and saves the result to an image file.
 *
 * This function takes a pointcloud_t and applies a water effect based on the specified maximum water depth.
 * The processed point cloud is then saved as an image to the specified file.
 *
 * @param pc Pointer to the point cloud structure to be processed.
 * @param maxwd Maximum water depth to be used in the simulation.
 * @param filename Name of the file where the resulting image will be saved.
 */
void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);

/**
 * @brief Adds a uniform amount of water to each point in the point cloud.
 *
 * This function iterates through all the points in the given point cloud and 
 * adds the specified amount of water to each point.
 *
 * @param pc Pointer to the point cloud structure.
 * @param amount The amount of water to add to each point in the point cloud.
 */
void watershedAddUniformWater(pointcloud_t* pc, double amount);

/**
 * @brief Performs a single step of the watershed algorithm on the given point cloud.
 * 
 * allocates memory for an array of doubles to store the changes in water depth for each point.
 * calculates the change in water depth for each point in the point cloud using the calculateChangeInWater function.
 * updates the water depth of each point in the point cloud based on the calculated changes.
 * @param pc Pointer to the point cloud structure.
 */
void watershedStep(pointcloud_t* pc);

/**
 * @brief Maps the water depth of a point to a corresponding blue color value.
 * 
 * @param point Pointer to the pcd_t point data structure.
 * @param maxwd Maximum water depth value for normalization.
 * @param s Pointer to the statistics structure.
 * @return unsigned int Color value corresponding to the water depth.
 */
unsigned int mapWaterDepthToColor(pcd_t* point, double maxwd, Stats* s);

/**
 * @brief Maps a given height value to a corresponding color value.
 *
 * This function takes a height value and a pointer to a Stats structure,
 * and returns an unsigned integer representing the color associated with
 * the given height using the bm_rgb() function in bpm.c The mapping is based on the statistical data provided
 * in the Stats structure.
 *
 * @param height The height value to be mapped to a color.
 * @param s A pointer to a Stats structure containing statistical data
 *          used for the height-to-color mapping.
 * @return An unsigned integer representing the color corresponding to
 *         the given height.
 */
unsigned int mapHeightToColor(double height, Stats* s);


/**
 * @brief Sets the wcoef for the given pointcloud_t.
 * 
 * @param pc Pointer to the point cloud structure.
 * @param wcoef The wcoef to be set.
 */
void setWcoef(pointcloud_t* pc, double wcoef);

/**
 * @brief Sets the ecoef for the given pointcloud_t.
 * 
 * @param pc Pointer to the point cloud structure.
 * @param ecoef The ecoef to be set.
 */
void setEcoef(pointcloud_t* pc, double ecoef);

/**
 * @brief Calculates the function in part 8 based on the given point, its neighbor, and a wcoef.
 *
 *
 * @param point A pointer to the point cloud data structure representing the point.
 * @param neighbor A pointer to the point cloud data structure representing the neighbor.
 * @param wcoef A double representing the wcoef.
 * @return A double representing the result of the calculation.
 */
double calculateFunc(pcd_t* point, pcd_t* neighbor, double wcoef);

/**
 * @brief Calculates the change in water depth for a given point.
 *
 * This function calculates the change in water depth for the specified point,
 * using a wcoef and an ecoef.
 *
 * @param point A pointer to the point cloud data structure representing the point.
 * @param wcoef A double representing the wcoef.
 * @param ecoef A double representing the ecoef.
 * @return A double representing the change in water depth.
 */
double calculateChangeInWater(pcd_t* point,double wcoef, double ecoef);
