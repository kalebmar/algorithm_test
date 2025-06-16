// Different algorithm for the second problem
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ID_LENGTH 10

typedef struct
{
    uint32_t x, y;
    char id[ID_LENGTH];
    uint32_t hashedID;
} Point;


float distanceFromOrigin(uint32_t x, uint32_t y)
{
    float fx = (float)x;
    float fy = (float)y;
    return sqrt(fx * fx + fy * fy);
}

uint32_t simple_hash(const char *str) {
    uint32_t sum = 0;
    while (*str)
        sum += *str++;
    return sum;
}

int compare_hashedID(const void *a, const void *b) {
    uint32_t ua = *(const uint32_t*)a;
    uint32_t ub = *(const uint32_t*)b;

    if (ua < ub) return -1;
    if (ua > ub) return 1;
    return 0;
}

float CalculateBiggestRadius(const Point *points, uint32_t len)
{

    if (len == 0)
        return 0.0f;

    float distance;

    Point *pointArray = malloc(len * sizeof(Point));

    if (pointArray == NULL)
        return 0.0f;
    // Error handling must be implemented

    memcpy(pointArray, points, len * sizeof(Points));

    for(uint32_t i = 0; i < len; i++)
    pointArray[i].hashedID = simple_hash(pointArray[i].id);

    // Sort the array to group elements with the same hashedID next to each other
    qsort(pointArray, len, sizeof(Point), compare_hashedID);

    // Make a function for this part
    float smallDist = 0.0f;
    float bigDist = 0.0f;
    float a;
    float b;
    bool notSimilar;
    uint32_t smallDistNum;


    // Current approach compares each ID only with the next one
    // To be corrected: all entries with the same hashedID must be compared
    // For each hashedID, store the smallest and second smallest radius
    // Then update the corresponding distance accordingly
    for(uint32_t i = 0; i < len - 1; i++){
    similar = strcmp(pointArray[i].id, pointArray[i+1]);
    if(notSimilar){ //ID-s match
        a = distanceFromOrigin(pointArray[i].x, pointArray[i].y);
        b = distanceFromOrigin(pointArray[i+1].x, pointArray[i+1].y);
        
    }
    }

   
    free(pointArray);
    return distance;
}