#include "gameplay.h"
#include "fleet.h"
#include <stdlib.h>


int main() {
    Ship* fleet = getFleet();

    gameplayLoop(fleet);

    free(fleet);
    return 0;
}