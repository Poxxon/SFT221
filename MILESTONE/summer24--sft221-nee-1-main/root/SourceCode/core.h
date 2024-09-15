#ifndef CORE_H
#define CORE_H
#include <stdio.h>
#include "mapping.h"

struct Shipment
{
    int weight;
    int volume;
    struct Point destination;
};
// Milestone 3_ Function Specification
/**
 * Function: findValidTruckPaths
 * - Populates the "routes" array with routes that reach the given shipment destination.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @param truck - Truck struct containing the route the truck travels on the map.
 * @param map - Map struct containing all the points (squares) in the map.
 * @param routes - Array of pointers to Route structs to store the valid routes.
 * @param size - Pointer to an integer to store the number of valid routes.
 * @returns - void, populates the "routes" array and updates the "size" variable.
 */
void findValidTruckPaths(struct Shipment shipment, struct Route route, struct Map* map, struct Route* validRoutes[], int* size);

/**
 * Function: getBestRoute
 * - Finds the index of the route with the shortest distance among the valid routes in the "routes" array.
 * @param routes - Array of Route structs containing all the valid routes.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @param size - Number of valid routes in the "routes" array.
 * @returns - int, the index of the route in the "routes" array with the shortest distance. Returns -1 if no valid route is found.
 */

int hasDestination(const struct Route* route, struct Shipment shipment);

/**
 * Function: printRoute
 * - Prints the points (coordinates) of a route to the console.
 * @param route - Route struct containing the points (coordinates) of the route.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - void, does not return a value, only prints to the console.
 */
void printRoute(struct Route route, struct Shipment shipment);

/**
 * Checks if a given route intersects with the map.
 *
 * @param route The route to check for intersection.
 * @param map   A pointer to the map structure.
 * @return      1 if the route intersects with the map, 0 otherwise.
 */
int isBuildingIntersected(const struct Route route, const struct Map* map);

/**
 * Calculates the best route for a given shipment.
 *
 * This function takes an array of Route pointers, a Shipment object, and the size of the array as parameters.
 * It calculates and returns the index of the best route for the given shipment.
 *
 * @param routes An array of Route pointers.
 * @param shipment The Shipment object for which the best route needs to be calculated.
 * @param size The size of the routes array.
 * @return The index of the best route for the given shipment.
 */
int getBestRoute(struct Route* validRoutes[MAX_ROUTE], struct Shipment shipment, int size);

/**
 * Checks if a truck is overloaded with a given shipment.
 *
 * @param truck The truck to check.
 * @param ship The shipment to compare with the truck's capacity.
 * @return 1 if the truck is overloaded, 0 otherwise.
 */
int isTruckOverloaded(struct Truck truck, struct Shipment ship);

/**
 * Checks if the box size of a truck exceeds a given limit.
 *
 * @param truck The truck to check.
 * @param boxSize The size of the box to compare against the limit.
 * @return 1 if the box size exceeds the limit, 0 otherwise.
 */
int isBoxSizeExceeded(struct Truck truck, int boxSize);

/**
 * Checks if the given box size is valid for cargo.
 *
 * @param boxsize The size of the box.
 * @return 1 if the box size is valid for cargo, 0 otherwise.
 */

/**
 * validates if the provided box size is acceptable.
 *
 * @param boxsize size of the box .
 * @returns 1 if box size is valid
 */
int validCargo(int boxsize);

/**
 * validates weight of a shipment.
 *
 * @param weight The weight of the shipment
 * @returns 1 if the weight is between 1 and 2500 kilograms, 0 otherwise.
 */
int validateWeight(int weight);

/**
 * validates destination 
 * destination must fit within the grid
 *
 * @param destination1 row number of the destination.
 * @param destination2 column letter of the destination.
 * @returns 1 if the destination is within the valid range, 0 otherwise.
 */
int validateDestination(int destination1, char destination2);

/**
 * parses a destination string into a point structure.
 *
 * @param destination string containing destination.
 * @returns struct Point representing parsed destination.
 */
struct Point parseDestination(const char* destination);

/**
 * finds best truck based on proximity to a given destination.
 *
 * @param dest point representing destination.
 * @param trucks array of Truck structs representing available trucks.
 * @param numTrucks number of trucks in array.
 * @returns Truck struct that is closest to destination.
 */
struct Truck findBestTruck(struct Point dest, struct Truck trucks[], int numTrucks);



int calculateDiversion(struct Map* map, struct Point destination, struct Route routes[], int numRoutes, struct Route diversionPaths[]);




#endif // CORE_H