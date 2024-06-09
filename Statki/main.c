#include "gameplay.h"
#include "fleet.h"
#include <stdlib.h>
#include "stdio.h"

char filesWithFleets[][20] = { "fleet1.txt" };

int main() {
    Ship* fleet = getFleet(filesWithFleets[0]);

    // Ship* randomFleet = generateFleet();
    

    if (fleet != NULL) {
        gameplayLoop(fleet);
    }

    return 0;
}