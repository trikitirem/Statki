#include "gameplay.h"
#include "fleet.h"
#include <stdlib.h>
#include "stdio.h"
#include "common.h"

char filesWithFleets[][20] = { "fleet1.txt" };

int main() {
    /*
    int currentGame = 0;
    while (true);
    {
        Ship* fleet = currentGame < 5 ? getFleet(filesWithFleets[currentGame]) : generateFleet();
        if (fleet != NULL) {
            gameplayLoop(fleet);
        }
        
        currentGame++;
        freeFleetMemory(fleet);
    }
    */

    Ship* fleet = generateFleet();
    if (fleet != NULL) {
        gameplayLoop(fleet);
    }
    
    return 0;
}