#include "common.h"
#include "stdbool.h"
#include "fleet.h"
#include <stdlib.h>
#include <stdio.h>

Ship* getFleet() {
    Ship fleet[ALL_SHIPS_COUNT];
    char line[256];

    FILE* file = fopen("fleet1.txt", "r");
    if(file == NULL) {
        printf("Nie mozna otworzyc pliku\n");
        return NULL;
    }

    for (int i = 0; i < ALL_SHIPS_COUNT; i++) {
        int shipsModuleCount, x, y;

        fgets(line, sizeof(line), file);
        sscanf_s(line, "%d", &shipsModuleCount);

        fleet[i].type = shipsModuleCount;
        fleet[i].shipModules = (ShipModule*)malloc(shipsModuleCount * sizeof(ShipModule));

        for (int j = 0; j < shipsModuleCount; j++) {
            fgets(line, sizeof(line), file);
            sscanf_s(line, "%d,%d", &x, &y);

            fleet[i].shipModules[j].hit = false;
            fleet[i].shipModules[j].position.x = x;
            fleet[i].shipModules[j].position.y = y;
        }

        if (i != ALL_SHIPS_COUNT - 1) {
            fgets(line, sizeof(line), file); // odczytaj pust¹ liniê która odziela statki
        }
    }
    
    fclose(file);

    return fleet;
}

/*
Ship* generateFleet() {
    Ship* fleet;
    fleet = (Ship*)malloc(ALL_SHIPS_COUNT * sizeof(Ship));

    fleet[0].type = SINGLE_MAST;
    fleet[0].position[0].x = 3; // C
    fleet[0].position[0].y = 3;
    fleet[0].position[0].hit = false;

    fleet[1].type = SINGLE_MAST;
    fleet[1].position[0].x = 5; // E
    fleet[1].position[0].y = 5;
    fleet[1].position[0].hit = false;

    fleet[2].type = SINGLE_MAST;
    fleet[2].position[0].x = 5; // E
    fleet[2].position[0].y = 1;
    fleet[2].position[0].hit = false;

    return fleet;
}
*/
