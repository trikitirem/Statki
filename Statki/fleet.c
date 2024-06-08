#include "common.h"
#include "stdbool.h"
#include "fleet.h"
#include <stdlib.h>
#include <stdio.h>

Ship* getFleet() {
    Ship* fleet= (Ship*)malloc(ALL_SHIPS_COUNT * sizeof(Ship));
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
        fleet[i].shipMasts = (ShipMast*)malloc(shipsModuleCount * sizeof(ShipMast));

        for (int j = 0; j < shipsModuleCount; j++) {
            fgets(line, sizeof(line), file);
            sscanf_s(line, "%d,%d", &x, &y);

            fleet[i].shipMasts[j].hit = false;
            fleet[i].shipMasts[j].position.x = x;
            fleet[i].shipMasts[j].position.y = y;
        }

        if (i != ALL_SHIPS_COUNT - 1) {
            fgets(line, sizeof(line), file); // odczytaj pust¹ liniê która odziela statki
        }
    }
    
    fclose(file);

    return fleet;
}
