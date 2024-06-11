#include "gameplay.h"
#include "fleet.h"
#include <stdlib.h>
#include "stdio.h"
#include "common.h"
#include "keyboard.h"

char filesWithFleets[][20] = { "fleet1.txt", "fleet2.txt", "fleet3.txt", "fleet4.txt", "fleet5.txt" };

int main() {
    int currentGame = 0;
    while (true)
    {
        Ship* fleet = currentGame < 5 ? getFleet(filesWithFleets[currentGame]) : generateFleet();
        if (fleet != NULL) {
            gameplayLoop(fleet);
        }
        
        currentGame++;
        freeFleetMemory(fleet);

        if (!getUserConfirmation()) {
            break;
        }


        system('cls');
    }
    return 0;
}