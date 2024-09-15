#include <stdio.h>
#include "core.h"
#include "mapping.h"

int main() {
    struct Map map = populateMap(); 
    struct Truck trucks[] = {  // Initialize trucks
        {1, 0, 2500, 0, 100, getBlueRoute()},
        {2, 0, 2500, 0, 100, getGreenRoute()},
        {3, 0, 2500, 0, 100, getYellowRoute()}
    };
    int numTrucks = sizeof(trucks) / sizeof(trucks[0]);
    int weight, size;
    char destination[10];
    int stop = 0;

    printf("=================\n");
    printf("Seneca Polytechnic Deliveries\n");
    printf("=================\n");

    while (!stop) {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        scanf("%d %d %s", &weight, &size, destination);

        if (weight == 0 && size == 0 && destination[0] == 'x') {
            stop = 1;
            printf("Thanks for shipping with Seneca Polytechnic!\n");
            continue;
        }

        struct Point dest = parseDestination(destination);
        if (!validateDestination(dest.row + 1, dest.col + 'A')) {
            printf("Invalid destination\n");
            continue;
        }
        if (!validCargo(size)) {
            printf("Invalid size\n");
            continue;
        }
        if (!validateWeight(weight)) {
            printf("Invalid weight (must be 1-2500 Kg.)\n");
            continue;
        }

        struct Route routes[numTrucks]; 
        for (int i = 0; i < numTrucks; i++) {
            routes[i] = trucks[i].currentRoute;
        }

        struct Route diversionPaths[numTrucks]; 
        int diversions = calculateDiversion(&map, dest, routes, numTrucks, diversionPaths);

        if (diversions > 0) {
            printf("diversions calculated, details:\n");
            for (int i = 0; i < diversions; i++) {
                printf("Route %d diversion path: ", i + 1);
                for (int j = 0; j < diversionPaths[i].numPoints; j++) {
                    printf("(%d, %d) ", diversionPaths[i].points[j].row, diversionPaths[i].points[j].col);
                }
                printf("\n");
            }
        } else {
            printf("No diversions necessary or possible.\n");
        }
    }

    return 0;
}
