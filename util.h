#ifndef UTIL_H
#define UTIL_H

#define INDEX(row, column, num_columns) (((row) * (num_columns)) + column)

typedef struct pcd pcd_t;

struct pcd{
    double x;
    double y;
    double z;
    double waterAmt;

    pcd_t* north;
    pcd_t* south;
    pcd_t* east;
    pcd_t* west;
    
};

typedef struct {
    int max_size;
    int max_element_size;
    void* data;
    int size;
}List;

typedef struct {
    double minHeight;
    double maxHeight;
    double range;
}Stats;

void* allocateArray(int rows, int columns);
int listInit(List* l, int max_elmt_size);
void listAddEnd(List* l, void* elmt);
void* listGet(List* l, int index);
int getMaxListSize(List* l);
int getCurrentListSize(List* l);
void computeStats(List* l, Stats* stats);

#endif
