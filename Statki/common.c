#include <stdbool.h>
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

bool areThePositionsEqual(Position position1, Position position2) {
	if (position1.x == position2.x && position1.y == position2.y)
		return true;

	return false;
}

void displayPosition(Position position) {
	printf("x: %d, y: %d", position.x, position.y);
}

void displayPositionArray(Position* positions, int size) {
    for (int i = 0; i < size; i++) {
        displayPosition(positions[i]);
        printf("\n");
    }
}

int findPositionIndex(Position* positions, int size, Position positionToFind) {
    for (int i = 0; i < size; i++) {
        if (positions[i].x == positionToFind.x && positions[i].y == positionToFind.y) {
            return i;
        }
    }
    return -1;
}

void displayShip(Ship ship) {
    for (int i = 0; i < ship.type; i++) {
        printf("Maszt %d: \n", i + 1);
        displayPosition(ship.shipMasts[i].position);
        printf("\n");
    }
}