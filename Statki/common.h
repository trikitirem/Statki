#pragma once
#include <stdbool.h>

#define BOARD_SIZE 10
#define MAX_SHIP_LENGTH 4
#define SINGLE_MAST_COUNT 4
#define TWO_MAST_COUNT 3
#define THREE_MAST_COUNT  2
#define FOUR_MAST_COUNT  1
// #define ALL_SHIPS_COUNT (SINGLE_MAST_COUNT + TWO_MAST_COUNT + THREE_MAST_COUNT + FOUR_MAST_COUNT)
#define ALL_SHIPS_COUNT 3
#define ALL_SHIPS_MASTS 3

typedef enum {
    SINGLE_MAST = 1,
    TWO_MAST = 2,
    THREE_MAST = 3,
    FOUR_MAST = 4
} ShipType;

typedef struct {
    int x;
    int y;

} Position;

typedef struct {
    Position position;
    bool hit;
} ShipMast;

typedef struct {
    ShipType type;
    ShipMast* shipMasts;
} Ship;


bool areThePositionsEqual(Position position1, Position position2);
void displayPosition(Position position);
void displayPositionArray(Position* positions, int size);
int findPositionIndex(Position* positions, int size, Position positionToFind);
void displayShip(Ship ship);
