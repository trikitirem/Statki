#pragma once
#include "common.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
} Direction;


Ship* getFleet(char* fileName);
Ship* generateFleet();

int mapShipTypeToShipCount(ShipType shipType);
bool isMastOnBoard(Position position);
Position positionMast(Position previousMastPosition, Direction direction);
bool collides(Position* occupiedPositions, int occupiedPositionsCount, Ship ship);
Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize);