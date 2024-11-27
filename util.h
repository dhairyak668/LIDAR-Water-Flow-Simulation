#pragma once

#define INDEX(row, column, num_columns) (((row) * (num_columns)) + column)

typedef struct pcd pcd_t;

/**
 * Structure that represents the details of a point in xyz format
 * 
 * It has these members:
 * 
 * *`double x` - represents the x coordinate
 * *`double y` - represents the y coordinate
 * *`double z` - represents the height of the point
 * *`double waterAmt` - 
 * *`double north` - 
 * *`double south` - 
 * *`double east` - 
 * *`double west` - 
 */
struct pcd{
    double x;
    double y;
    double z;
    double wd;

    pcd_t* north;
    pcd_t* south;
    pcd_t* east;
    pcd_t* west;
    
};

/**
 * Structure that mimics the List Data_Stucture
 * 
 * It has these members:
 * 
 * *`int max_size` - represents the maxium size allocated for this array. Can change with expansion
 * *`int max_element_size` - represents the maximun size of each element in the list
 * *`void* data` - pointer to memory that stores all the elements of the list. Generic void* type
 * *`int size` - represents the current size of the List or the current number of elements added in the list
 * 
 * `max_size / max_element_size` can be used to find maximum number of elements list can store
 * `size / max_element_size` can be used to find current number of elements in the list
 * 
 */
typedef struct {
    int max_size;
    int max_element_size;
    void* data;
    int size;
}List;

/**
 * Structure to store specific information.
 * Specially created to store information on List of points(pcd_t)
 * 
 * It has these members:
 * 
 * *`double minZ` - stores the minimum height of all the points in the list
 * *`double maxZ` - stores the maximum height of all the points in the list
 * *`double heightRange` - stores the range of heights of the points in the list
 */
typedef struct {
    double minZ;
    double maxZ;
    double minX;
    double minY;
    double maxX;
    double maxY;
    double xInterval;
    double yInterval;
    double heightRange;
}Stats;

/**
 * Allocates a 2D array of doubles with the specified number of rows and columns.
 * 
 * @param rows The number of rows to allocate.
 * @param columns The number of columns to allocate.
 * @return A pointer to the allocated 2D array, or NULL if allocation fails.
 */
void* allocateArray(int rows, int columns);

/**
 * Initializes a List structure for holding elements of specified size.
 * Expects the memory allocation for list is already done
 * 
 * @param l Pointer to the List structure to initialize.
 * @param max_elmt_size The maximum size of each element.
 * @return 0 on success, 1 on failure.
 */
int listInit(List* l, int max_elmt_size);

/**
 * Adds an element to the end of the List.
 * Doubles memory allocated for list->data if size == max_size
 * 
 * @param l Pointer to the List structure.
 * @param elmt Pointer to the element to add.
 */
void listAddEnd(List* l, void* elmt);

/**
 * Retrieves an element at the specified index from the List.
 * 
 * @param l Pointer to the List structure.
 * @param index The index of the element to retrieve.
 * @return Pointer to the element, or NULL if the index is out of bounds.
 */
void* listGet(List* l, int index);

/**
 * Sets the element at the specified index in the list.
 *
 * @param l Pointer to the list.
 * @param index The index at which the element should be set.
 * @param element Pointer to the element to be set.
 * @return An integer indicating success (0) or failure (-1).
 */
int listSet(List* l, int index, void* element);

/**
 * Calculates and returns the maximum size of the List in bytes.
 * 
 * @param l Pointer to the List structure.
 * @return The maximum size in bytes.
 */
int getMaxListSize(List* l);

/**
 * Calculates and returns the current size of the List in bytes.
 * 
 * @param l Pointer to the List structure.
 * @return The current size in bytes.
 */
int getCurrentListSize(List* l);

/**
 * Computes the minimum and maximum heights in the List of points,
 * and stores the results in the given Stats structure.
 * 
 * @param l Pointer to the List structure containing points.
 * @param stats Pointer to the Stats structure to store results.
 */
void computeStats(List* l, Stats* stats);


