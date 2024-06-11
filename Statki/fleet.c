#include "common.h"
#include "stdbool.h"
#include "fleet.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "helpers.h"

Position verticalOffset = { 0, 1 };
Position horizontalOffset = { 1, 0 };

typedef struct {
    Position* positions;
    int size;
} PositionArray;

// Funkcja generuj�ca flot� statk�w
// Zasada dzia�ania:
// 1. Iterujemy po typach statk�w, w kolejno�ci od najwi�kszego do najmniejszego
//    (Zaczynaj�c od postawienia wi�kszych statk�w wyst�pi mniejsze ryzyko nie znalezienia miejsca na statek)
// 2. Dla ka�dego typu statku pobieramy ilo��, kt�r� dla niego nale�y wygenerowa�
// 3. Statek dodajemy do tablicy
Ship* generateFleet() {
    Ship* fleet = NULL;
    int tempFleetSize = 0;

    // generowanie statk�w, zaczynaj�c od najwi�kszych, bo b�dzie mniej problem�w z kolizjami
    for (ShipType shipType = FOUR_MAST; shipType >= SINGLE_MAST; shipType--) {
        int shipCount = mapShipTypeToShipCount(shipType);
        for (int i = 0; i < shipCount; i++) {
            fleet = realloc(fleet, (tempFleetSize + 1) * sizeof(Ship));
            fleet[tempFleetSize++] = generateShip(shipType, fleet, tempFleetSize);
        }
    }

    return fleet;
}

// Funkcja odczytuj�ca flot� z pliku
Ship* getFleet(char* fileName) {
    Ship* fleet= (Ship*)malloc(FLEET_SIZE * sizeof(Ship));
    char line[256];

    FILE* file = fopen(fileName, "r");
    if(file == NULL) {
        printf("Nie mozna otworzyc pliku\n");
        return NULL;
    }

    for (int i = 0; i < FLEET_SIZE; i++) {
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


        if (i != FLEET_SIZE - 1) {
            fgets(line, sizeof(line), file); // odczytaj pust� lini� kt�ra odziela statki
        }
    }
    
    fclose(file);

    return fleet;
}

// Funkcja pomocnicza mapuj�ca typ statku na ilo�� statk�w do wygenerowania
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

// Funkcja pomocnicza pozwalaj�ca umie�ci� maszt statku na planszy, na podstawie poprzedniego masztu.
// Do umiejscowienia brany jest pod uwag� kierunek u�o�enia statku
Position positionMast(Position previousMastPosition, Direction direction) {
    if (direction == VERTICAL) {
        return addOffsetToPosition(previousMastPosition, verticalOffset);
    }

    return addOffsetToPosition(previousMastPosition, horizontalOffset);
}

bool checkCollision(Position occupiedPosition, Position shipMastPosition){
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; i <= 1; i++) {
            if (areThePositionsEqual(occupiedPosition, addOffsetToPosition(shipMastPosition, (Position){i, j}))) {
                return true;
            }
        }
    }

    return false;
}

// Funkcja sprawdzaj�ca czy okre�lona pozycja na tablicy jest ju� okupowana i czy nie koliduje z innymi statkami
bool isPositionOccupied(Position position, Ship* fleet, int fleetSize, int boardSize) {
    for (int i = 0; i < fleetSize; i++) {
        Ship ship = fleet[i];
        for (int j = 0; j < ship.type; j++) {
            if (checkCollision(ship.shipMasts[j].position, position)) {
                return true;
            }
        }
    }
    return false;
}

bool canPlaceShipHorizontally(int x, int y, ShipType shipType, Ship* fleet, int fleetSize) {
    if (x + shipType <= BOARD_SIZE) {
        int freeHorizontalSpots = 1;
        for (int i = 0; i < shipType; i++) {
            if (!isPositionOccupied((Position) { x + i, y }, fleet, fleetSize, BOARD_SIZE)) {
                freeHorizontalSpots++;
            }
            else {
                break;
            }
        }
        
        return freeHorizontalSpots == shipType;
    }

    return false;
}

bool canPlaceShipVertically(int x, int y, ShipType shipType, Ship* fleet, int fleetSize) {
    if (y + shipType <= BOARD_SIZE) {
   
        int freeVerticalSpots = 0;
        for (int i = 0; i < shipType; i++) {
            if (!isPositionOccupied((Position){x, y + i}, fleet, fleetSize, BOARD_SIZE)) {
                freeVerticalSpots++;
            }
            else {
                break;
            }
        }

        return freeVerticalSpots == shipType;
    }

    return false;
}

// Funkcja zwracaj�ca wszystkie punkty w kt�rym mo�na umiejscowi� statek
// Przy sprawdzaniu brane s� pod uwag�: d�ugo�� statku, kierunek, rozmieszczenie innych statk�w
// Zwr�cone punkty mog� pos�u�y� jako koordynata pierwszego masztu statku
PositionArray findAvailableShipPositions(ShipType shipType, Ship* fleet, int fleetSize, Direction direction) {
    PositionArray availablePositions = {NULL, 0};
    
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            bool canPlaceShip = direction == VERTICAL ?
                canPlaceShipVertically(x, y, shipType, fleet, fleetSize) : canPlaceShipHorizontally(x, y, shipType, fleet, fleetSize);
            
            if(canPlaceShip) {
                availablePositions.positions = realloc(availablePositions.positions, (availablePositions.size + 1) * sizeof(Position));
                availablePositions.positions[availablePositions.size++] = (Position){ x, y };
            }
        }
    }
    

    return availablePositions;
}

// Funkcja generuj�ca statek
// Zasada dzia�ania:
// 1. Losowany jest kierunek w jakim postawiony mo�e by� statek
// 2. Wyszukiwane s� pozycje w kt�rych statek mo�e by� umieszczony.
//    Przy okre�laniu tych pozycji brane s� pod uwag�: d�ugo�� statku, kierunek, rozmieszczenie innych statk�w
// 3. Spo�r�d wyszukanych pozycji losowana jest jedna z nich
// 4. Wylosowana pozycja staje si� koordynat� pierwszego masztu, kolejne maszty s� generowane poprzez przesuni�cie (offset) tej koordynaty w wylosowanym kierunku
// 5. Maszty zostaj� dodane do statku
Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize) {
    Ship ship;
    ship.type = shipType;
    ship.shipMasts = (ShipMast*)malloc(shipType * sizeof(ShipMast));

    srand(time(NULL));
    Direction direction = rand() % 2;
    printf("direction: %d \n", direction);

    PositionArray availableShipPositions = findAvailableShipPositions(shipType, fleet, fleetSize, direction);

    srand(time(NULL));
    Position firstMastPosition = availableShipPositions.positions[rand() % availableShipPositions.size];

    ship.shipMasts[0] = (ShipMast){ firstMastPosition, false };
    for (int i = 1; i < shipType; i++) {
        Position mastPosition = positionMast(ship.shipMasts[i - 1].position, direction);
        ship.shipMasts[i] = (ShipMast){ mastPosition, false };
    }
    return ship;
}
