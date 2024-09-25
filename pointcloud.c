#include <stdio.h>
#include <float.h>  //for DBL_MAX 
#include "pointcloud.h"

/**
 * function to calculate and print Minimum Height, Maximum Height along with their respective (x,y)coordinates 
 * and Average Height
 * param: takes filename
 */
void stat1(const char *filename)
{
    FILE *file = fopen(filename,"r");

    if(file == NULL){
        perror("Error in opening file\n");
        return;
    }

    double x, y, height;
    double minHeight = DBL_MAX; //better than setting to null. Thus even the first value will be considered min/max.
    double maxHeight = -DBL_MAX; 

    double totalHeight = 0.0;
    int count = 0;

    double minX = 0, minY = 0, maxX = 0, maxY = 0;

    //will run until fscanf reads 3 inputs(returns 3). will exit at any error or EOF
    while(fscanf(file, "%lf %lf %lf", &x, &y, &height) == 3) { 
        
        if(height < minHeight){
            minX = x;
            minY = y;
            minHeight = height;
        }

        if(height > maxHeight){
            maxX = x;
            maxY = y;
            maxHeight = height;
        }

        totalHeight += height;
        count++;
    }

    fclose(file);

    double avgHeight = (count > 0) ? (totalHeight/count) : 0.0;

    printf("Minimum height: %lf at (%lf, %lf)\n",minHeight, minX, minY);
    printf("Maximun height: %lf at (%lf, %lf)\n",maxHeight, maxX, maxY);
    printf("Average height: %lf\n", avgHeight);
}

int main(int argc, char *argv[]){
    //checks if filename has been passed in cmd
    if(argc != 2){
        printf("Use as: %s <filename>\n",argv[0]);
        return 1;
    }
    stat1(argv[1]);
    return 0;
}