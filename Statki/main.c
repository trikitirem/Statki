#include "gameplay.h"
#include "fleet.h"
#include <stdlib.h>
#include "stdio.h"


int main() {
    Ship* fleet = getFleet();
    gameplayLoop(fleet);

    return 0;
}