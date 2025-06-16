// Different algorithm for the second problem
// This function finds the smallest radius that still includes 
// at least two points with the same ID. It works by first 
// sorting the points by ID (and by distance if IDs match), 
// then scanning adjacent pairs to find the closest matching pair 
// per unique ID. If no matching IDs are found, it returns the 
// distance of the farthest point from the origin.
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

#define ID_LENGTH 10

typedef struct
{
    uint32_t x, y;
    char id[ID_LENGTH];
} Point;

float distanceFromOrigin(uint32_t x, uint32_t y)
{
    float fx = (float)x;
    float fy = (float)y;
    return sqrt(fx * fx + fy * fy);
}

int compare_hashedID(const void *a, const void *b)
{
    Point ua = *(const Point *)a;
    Point ub = *(const Point *)b;

    // a < b -> return -1
    // a > b -> return 1
    // a == b -> distance
    uint8_t id_cmp = strcmp(ua.id, ub.id);
    if (id_cmp < 0) // ua->id < ub->id
        return -1;
    else if (id_cmp > 0) // ua->id > ub->id
        return 1;
    else
    { // ua->id == ub->id
        float distA = distanceFromOrigin(ua.x, ua.y);
        float distB = distanceFromOrigin(ub.x, ub.y);
        if (distA < disbB)
            return -1;
        else if (distA > distB)
            return 1;
        else // distA == distB
            return 0;
    }
}

int compareByDistance(const void *a, const void *b)
{
    const Point *pointA = (const Point *)a;
    const Point *pointB = (const Point *)b;
    float distA = distanceFromOrigin(pointA->x, pointA->y);
    float distB = distanceFromOrigin(pointB->x, pointB->y);
    if (distA < distB)
        return -1;
    if (distA > distB)
        return 1;
    return 0;
}

float CalculateBiggestRadius(const Point *points, uint32_t len)
{
    uint8_t similarID;
    float biggestRadius = FLT_MAX;
    float newRadius = 0.0f;
    char lastID[ID_LENGTH] = "";

    if (len == 0)
        return 0.0f;

    float distance;

    Point *pointArray = malloc(len * sizeof(Point));

    if (pointArray == NULL)
        return 0.0f;
    // Error handling must be implemented

    memcpy(pointArray, points, len * sizeof(Point));

    // Sort the array to group elements with the same ID next to each other
    qsort(pointArray, len, sizeof(Point), compare_hashedID);

    for (uint32_t i = 0; i < len - 2; i++)
    {   
        // ID-s match
        similarID = strcmp(pointArray[i].id, pointArray[i + 1].id);
        // Points are ordered by distance in case ID-s match
        // We can ignore points that are further with the same ID
        if (similarID == 0 && strcmp(lastID, pointArray[i].id) != 0)
        {  
            strcpy(lastID, pointArray[i].id);
            newRadius = distanceFromOrigin(pointArray[i + 1].x, pointArray[i + 1].y);
            if (newRadius < biggestRadius)
                biggestRadius = newRadius;
        }
    }

    // In case there are no similar ID-s
    if(biggestRadius == FLT_MAX){
        qsort(pointArray, len, sizeof(Point), compareByDistance);
        biggestRadius = distanceFromOrigin(pointArray[len - 1].x, pointArray[len - 1].y);
    }
    free(pointArray);
    return biggestRadius;
}