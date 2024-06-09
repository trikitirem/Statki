#include "common.h"
#include "stdbool.h"
#include "fleet.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Position verticalOffset = { 0, 1 };
Position horizontalOffset = { 1, 0 };

// Funkcja generuj¹ca flotê statków
Ship* generateFleet() {
    Ship* fleet = (Ship*)malloc(ALL_SHIPS_COUNT * sizeof(Ship));
    int tempFleetSize = 0;

    // generowanie statków, zaczynaj¹c od najwiêkszych, bo bêdzie mniej problemów z kolizjami
    for (ShipType shipType = FOUR_MAST; shipType >= SINGLE_MAST; shipType--) {
        int shipCount = mapShipTypeToShipCount(shipType);

        // dla ka¿dego typu statku generujemy okreœlon¹ dla niego iloœæ statków
        for (int i = 0; i < shipCount; i++) {
            Ship ship = generateShip(shipType, fleet, tempFleetSize);
            fleet[tempFleetSize] = ship;

            tempFleetSize++;
        }
    }

    return fleet;
}

// Funkcja odczytuj¹ca flotê z pliku
Ship* getFleet(char* fileName) {
    Ship* fleet= (Ship*)malloc(ALL_SHIPS_COUNT * sizeof(Ship));
    char line[256];

    FILE* file = fopen(fileName, "r");
    if(file == NULL) {
        printf("Nie mozna otworzyc pliku\n");
        return NULL;
    }

    for (int i = 0; i < ALL_SHIPS_COUNT; i++) {
        int shipsMastCount, rowInput;
        char colInput;

        fgets(line, sizeof(line), file);
        sscanf_s(line, "%d", &shipsMastCount);

        fleet[i].type = shipsMastCount;
        fleet[i].shipMasts = (ShipMast*)malloc(shipsMastCount * sizeof(ShipMast));

        for (int j = 0; j < shipsMastCount; j++) {
            fgets(line, sizeof(line), file);
            sscanf_s(line, "%c%d", &colInput, (unsigned int)sizeof(colInput), &rowInput);

            fleet[i].shipMasts[j].hit = false;
            fleet[i].shipMasts[j].position.x = convertLetterToCoordinate(colInput);
            fleet[i].shipMasts[j].position.y = rowInput - 1;
        }


        if (i != ALL_SHIPS_COUNT - 1) {
            fgets(line, sizeof(line), file); // odczytaj pust¹ liniê która odziela statki
        }
    }
    
    fclose(file);

    return fleet;
}


int mapShipTypeToShipCount(ShipType shipType) {
    switch (shipType){
    case SINGLE_MAST:
        return SINGLE_MAST_COUNT;
    case TWO_MAST:
        return TWO_MAST_COUNT;
    case THREE_MAST: 
        return THREE_MAST_COUNT;
    default:
        return FOUR_MAST_COUNT;
    }
}

bool isMastOnBoard (Position position) {
    if (position.x >= 0 && position.x <= 9 && position.y >= 0 && position.y <= 9) {
        return true;
    }

    return false;
}


Position positionMast(Position previousMastPosition, Direction direction) {
    if (direction == VERTICAL) {
        return addOffsetToPosition(previousMastPosition, verticalOffset);
    }

    return addOffsetToPosition(previousMastPosition, horizontalOffset);
}

Position* extractMastPositionsFromShip(Ship ship) {
    Position* currentShipMastPositions = (Position*)malloc(ship.type * sizeof(Position));
    for (int i = 0; i < ship.type; i++) {
        currentShipMastPositions[i] = ship.shipMasts[i].position;
    }
    
    return currentShipMastPositions;
}

bool checkCollision(Position occupiedPosition, Position shipMastPosition){
    Position offset;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; i <= 1; i++) {
            offset.x = i;
            offset.y = j;
            
            if (areThePositionsEqual(occupiedPosition, addOffsetToPosition(shipMastPosition, offset))) {
                return true;
            }
        }
    }

    return false;
}

bool collides(Position* occupiedPositions, int occupiedPositionsCount, Ship ship) {
    Position* currentShipMastPositions = extractMastPositionsFromShip(ship);

    for (int i = 0; i < occupiedPositionsCount; i++) {
        for (int j = 0; j < ship.type; j++) {
            if (checkCollision(occupiedPositions[i], currentShipMastPositions[j])) {
                free(currentShipMastPositions);
                return true;
            }
        }
    }

    free(currentShipMastPositions);
    return false;
}


Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize) {
    Ship ship;
    ship.type = shipType;

    // Lista ju¿ zajêtych pozycji, bêdzie u¿yta do wykrywania kolizji
    Position* occupiedPositions = (Position*)malloc(ALL_SHIPS_MASTS * sizeof(Position));
    int occupiedPositionsCount = 0;

    srand(time(NULL));
    while (true) {
        bool allMastsOnBoard = true;
        ship.shipMasts = (ShipMast*)malloc(shipType * sizeof(ShipMast));

        Position positionOfFirstMast = { rand() % BOARD_SIZE, rand() % BOARD_SIZE };
        Direction direction = rand() % 2;

        ship.shipMasts[0].position = positionOfFirstMast;
        ship.shipMasts[0].hit = false;

        // generujemy resztê masztów
        for (int i = 1; i < shipType; i++) {
            Position mastPosition = positionMast(ship.shipMasts[i - 1].position, direction);
            bool onBoard = isMastOnBoard(mastPosition);

            if (!onBoard) {
                allMastsOnBoard = false;
                break;
            }
        }

        // je¿eli statek w ca³oœci znajduje siê na planszy i nie koliduje z innymi statkami to go zwróæ (pêtla siê zatrzyma)
        if (allMastsOnBoard && !collides(occupiedPositions, occupiedPositionsCount, ship)) {
            return ship;
        }
        else {
            free(ship.shipMasts);
        }
    }

    free(occupiedPositions);
}
