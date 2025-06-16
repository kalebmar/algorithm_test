// Use test_2.1 instead of test_2 — faster algorithm
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ID_LENGTH 10

enum sorts
{
    qsort,     // 0
    insertsort // 1
};

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

// Insertion sort
// qsort might be a better choice here with lots of data points
void insertSortByDistance(Point *points, uint32_t len)
{
    float *pointDistances = malloc(len * sizeof(float));

    if (pointDistances == NULL)
        // Error handling must be implemented

    for (uint32_t i = 0; i < len; i++)
        pointDistances[i] = distanceFromOrigin(points[i].x, points[i].y);

    for (uint32_t i = 1; i < len; i++)
    {
        float key = pointDistances[i];
        Point pKey = points[i];
        uint32_t j = i - 1;

        // While left value is bigger, shift right
        while (j >= 0 && pointDistances[j] > key)
        {
            pointDistances[j + 1] = pointDistances[j];
            points[j + 1] = points[j];
            j--;
        }

        pointDistances[j + 1] = key;
        points[j + 1] = pkey;
    }
    free(pointDistances);
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

void qsortByDistance(Point *points, uint32_t len)
{
    qsort(points, len, sizeof(Point), compareByDistance);
}

float CalculateBiggestRadius(const Point *points, uint32_t len, uint8_t sortSelector)
{

    if (len == 0)
        return 0.0f;

    float distance;
    bool foundDuplicate = false;

    Point *pointArray = malloc(len * sizeof(Point));

    if (pointArray == NULL)
        return 0.0f;
    // Error handling must be implemented

    memcpy(pointArray, points, len * sizeof(Point));
    switch (sortSelector)
    {
    case qsort:
        qsortByDistance(pointArray, len);
        break;
    case insertsort:
        insertSortByDistance(pointArray, len);
        break;
    default:
        qsortByDistance(pointArray, len);
        break;
    }
    
    // Iterate through the sorted points to find the farthest point from origin
    // while ensuring no duplicate IDs have been encountered
    for (uint32_t i = 0; i < len; i++)
    {
        // Check all previous points to detect duplicate IDs
        for (uint32_t j = 0; j < i; j++)
        {
            // If a duplicate ID is found, break out of the inner loop
            if (strcmp(pointArray[j].id, pointArray[i].id) == 0)
            {
                foundDuplicate = true;
                break;
            }
        }
        // If a duplicate was found, stop checking further
        if (foundDuplicate)
            break;
       // Only update distance if the current point ID is unique
        distance = distanceFromOrigin(pointArray[i].x, pointArray[i].y);
    }

    free(pointArray);
    return distance;
}