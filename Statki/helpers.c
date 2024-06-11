#include "common.h"
#include <stdio.h>

// W tym pliku znajduj¹ siê funkcje pomocnicze, które by³y pomocne przy debugowaniu

void displayPosition(Position position) {
    printf("x: %d, y: %d", position.x, position.y);
}

void displayPositionArray(Position* positions, int size) {
    for (int i = 0; i < size; i++) {
        displayPosition(positions[i]);
        printf("\n");
    }
}

void displayShip(Ship ship) {
    for (int i = 0; i < ship.type; i++) {
        printf("Maszt %d: \n", i + 1);
        displayPosition(ship.shipMasts[i].position);
        printf("\n");
    }
}

void displayFleet(Ship* fleet) {
    for (int i = 0; i < FLEET_SIZE; i++) {
        displayShip(fleet[i]);
        printf("\n");
    }
}

