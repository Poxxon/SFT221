#include "mapping.h"
#include "core.h"
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>
#include <math.h>

//  Function to find valid truck paths that reach the given shipment destination
void findValidTruckPaths(struct Shipment shipment, struct Route route, struct Map* map, struct Route* validRoutes[], int* size) {
    struct Route diversionRoute = shortestPath(map, route.points[0], shipment.destination);
    if (diversionRoute.numPoints > 0) {
        validRoutes[(*size)++] = &route;
    }
}

// Function to check if a route has the given shipment destination
int hasDestination(const struct Route* route, struct Shipment shipment)
{
    for (int i = 0; i < route->numPoints; i++)
    {
        // Check if the route has the shipment's destination
        if (route->points[i].row == shipment.destination.row && route->points[i].col == shipment.destination.col)
        {
            return 1; // The route has the shipment's destination
        }
    }
    return 0; // The route does not have the shipment's destination
}

// Function to print the points (coordinates) of a route
void printRoute(struct Route route, struct Shipment shipment)
{
    printf("Route to Shipment (Destination: (%d, %d)):\n", shipment.destination.row, shipment.destination.col);
    for (int i = 0; i < route.numPoints; i++)
    {
        printf("(%d, %d) ", route.points[i].row, route.points[i].col);
    }
    printf("\n");
}

// Function to check if a given route intersects with any buildings on the map
int isBuildingIntersected(const struct Route route, const struct Map* map)
{
    for (int i = 0; i < route.numPoints; i++)
    {
        // Check if the point in the route is a building on the map
        if (map->squares[route.points[i].row][route.points[i].col] == 2)
        {
            return 1; // The route intersects with a building
        }
    }
    return 0; // The route does not intersect with any buildings
}

// Function to get the index of the route with the shortest distance among valid routes
int getBestRoute(struct Route* routes[MAX_ROUTE], struct Shipment shipment, int size)
{
    int shortestDistance = INT_MAX;
    int shortestIndex = -1;

    for (int i = 0; i < size; i++)
    {
        // Calculate the distance from the route's starting point to the shipment's destination
        int routeDistance = distance(&routes[i]->points[0], &shipment.destination);
        if (routeDistance < shortestDistance)
        {
            // Update the shortest distance and corresponding index
            shortestDistance = routeDistance;
            shortestIndex = i;
        }
    }

    return shortestIndex; // Return the index of the route with the shortest distance
}

// Function to check if a truck is overloaded with a given shipment
int isTruckOverloaded(struct Truck truck, struct Shipment ship)
{
    // Check if adding the shipment's weight exceeds the truck's capacity limit
    return (truck.weightCapacity + ship.weight) > 1000 ? 0 : 1;
}

// Function to check if the box size of a truck exceeds a given limit
int isBoxSizeExceeded(struct Truck truck, int boxSize)
{
    // Calculate new capacity if the box is added
    float newVolumeCapacity = truck.volumeCapacity + boxSize;

    // Check if new capacity exceeds the maximum allowed
    return newVolumeCapacity > 36 ? 0 : 1;
}

// Function to check if the cargo box size is valid
int validCargo(int size) {
    return size == 1 || size == 3 || size == 5 ;
}
int validateWeight(int weight) {
    return weight >= 1 && weight <= 2500;
}

int validateDestination(int destination1, char destination2) {
    destination2 = toupper(destination2);
    return destination1 >= 1 && destination1 <= 25 && destination2 >= 'A' && destination2 <= 'Y';
}

// parsing the coordinates entered by user
struct Point parseDestination(const char* destination) {
    struct Point pt;
    int row;
    char col;
    sscanf(destination, "%d%c", &row, &col);
    pt.row = row - 1;  // Assuming rows are 1-based from input
    pt.col = col - 'A';  // Convert column letter to zero-based index
    return pt;
}

// find best truck
struct Truck findBestTruck(struct Point dest, struct Truck trucks[], int numTrucks) {
    double minDist = DBL_MAX;  
    int bestTruckIdx = -1;

    //  iterate through trucks
    for (int i = 0; i < numTrucks; i++) {
        struct Route route = trucks[i].currentRoute;

        // iterate through points in truck route
        for (int j = 0; j < route.numPoints; j++) {
            double dist = distance(&dest, &route.points[j]);
            if (dist < minDist) {
                minDist = dist;
                bestTruckIdx = i;
            }
        }
    }

    return (bestTruckIdx != -1) ? trucks[bestTruckIdx] : (struct Truck){0}; // return best truck
}


// find diversion

int calculateDiversion(struct Map* map, struct Point destination, struct Route routes[], int numRoutes, struct Route diversionPaths[]) {
    int count = 0;
    for (int i = 0; i < numRoutes; i++) {
        int closestIndex = getClosestPoint(&routes[i], destination);
        if (closestIndex >= 0 && closestIndex < routes[i].numPoints) {  
            struct Point closestPoint = routes[i].points[closestIndex];
            struct Route diversionPath = shortestPath(map, closestPoint, destination);
            if (diversionPath.numPoints > 0 && !isBuildingIntersected(diversionPath, map)) {
                diversionPaths[i] = diversionPath;
                count++;
            }
        }
    }
    return count;
}


