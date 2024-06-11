#include "common.h"
#include "stdbool.h"
#include "fleet.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "helpers.h"

Position verticalOffset = { 0, 1 };
Position horizontalOffset = { 1, 0 };

// Funkcja generuj¹ca flotê statków
// Zasada dzia³ania:
// 1. Iterujemy po typach statków, w kolejnoœci od najwiêkszego do najmniejszego
//    (Zaczynaj¹c od postawienia wiêkszych statków wyst¹pi mniejsze ryzyko nie znalezienia miejsca na statek)
// 2. Dla ka¿dego typu statku pobieramy iloœæ, któr¹ dla niego nale¿y wygenerowaæ
// 3. Statek dodajemy do tablicy
Ship* generateFleet() {
    Ship* fleet = NULL;
    int tempFleetSize = 0;

    srand(time(NULL));

    // generowanie statków, zaczynaj¹c od najwiêkszych, bo bêdzie mniej problemów z kolizjami
    for (ShipType shipType = FOUR_MAST; shipType >= SINGLE_MAST; shipType--) {
        int shipCount = mapShipTypeToShipCount(shipType);
        for (int i = 0; i < shipCount; i++) {
            fleet = realloc(fleet, (tempFleetSize + 1) * sizeof(Ship));
            fleet[tempFleetSize++] = generateShip(shipType, fleet, tempFleetSize);
        }
    }

    return fleet;
}

// Funkcja odczytuj¹ca flotê z pliku
Ship* getFleet(char* fileName) {
    Ship* fleet=(Ship*)malloc(FLEET_SIZE * sizeof(Ship));
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
            fgets(line, sizeof(line), file); // odczytaj pust¹ liniê która odziela statki
        }
    }
    
    fclose(file);

    return fleet;
}

// Funkcja pomocnicza mapuj¹ca typ statku na iloœæ statków do wygenerowania
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

// Funkcja pomocnicza pozwalaj¹ca umieœciæ maszt statku na planszy, na podstawie poprzedniego masztu.
// Do umiejscowienia brany jest pod uwagê kierunek u³o¿enia statku
Position positionMast(Position previousMastPosition, Direction direction) {
    if (direction == VERTICAL) {
        return addOffsetToPosition(previousMastPosition, verticalOffset);
    }

    return addOffsetToPosition(previousMastPosition, horizontalOffset);
}

// Funkcja sprawdzaj¹ca kolizje z innymi statkami
// Zasada dzia³ania:
// Aby aby sprawdzic czy pozycja i pole wokó³ niej nie s¹ okupowane dodawane s¹ do niej przesuniêcia.
// Przesuniêcia s¹ generowane w pêtlach.
// Je¿eli przesuniêcie w osi x bêdzie równe -1, to sprawdzamy pozycje z lewej strony od punktu s¹ okupowane, je¿eli 1 to z prawej
// Dla osi y dzia³a to tak samo. 
// W taki sposób mo¿emy sprawdziæ wszystkie pozycje wokó³ naszego pola i nasze pole
bool checkCollision(Position occupiedPosition, Position shipMastPosition){
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (areThePositionsEqual(occupiedPosition, addOffsetToPosition(shipMastPosition, (Position){x, y}))) {
                return true;
            }
        }
    }

    return false;
}

// Funkcja sprawdzaj¹ca czy okreœlona pozycja na tablicy jest ju¿ okupowana i czy nie koliduje z innymi statkami
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

// Funkcja sprawdzaj¹ca czy mo¿na na danym umieœciæ pierwszy maszt statku poziomego
bool canPlaceShipHorizontally(int x, int y, ShipType shipType, Ship* fleet, int fleetSize) {
    if (x + shipType <= BOARD_SIZE) {
        int freeHorizontalSpots = 0;
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

// Funkcja sprawdzaj¹ca czy mo¿na na danym umieœciæ pierwszy maszt statku pionowego
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

// Funkcja zwracaj¹ca wszystkie punkty w którym mo¿na umiejscowiæ statek
// Przy sprawdzaniu brane s¹ pod uwagê: d³ugoœæ statku, kierunek, rozmieszczenie innych statków
// Zwrócone punkty mog¹ pos³u¿yæ jako koordynata pierwszego masztu statku
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

// Funkcja generuj¹ca statek
// Zasada dzia³ania:
// 1. Losowany jest kierunek w jakim postawiony mo¿e byæ statek
// 2. Wyszukiwane s¹ pozycje w których statek mo¿e byæ umieszczony.
//    Przy okreœlaniu tych pozycji brane s¹ pod uwagê: d³ugoœæ statku, kierunek, rozmieszczenie innych statków
// 3. Spoœród wyszukanych pozycji losowana jest jedna z nich
// 4. Wylosowana pozycja staje siê koordynat¹ pierwszego masztu, kolejne maszty s¹ generowane poprzez przesuniêcie (offset) tej koordynaty w wylosowanym kierunku
// 5. Maszty zostaj¹ dodane do statku
Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize) {
    Ship ship;
    ship.type = shipType;
    ship.shipMasts = (ShipMast*)malloc(shipType * sizeof(ShipMast));

    Direction direction = rand() % 2;
    PositionArray availableShipPositions = findAvailableShipPositions(shipType, fleet, fleetSize, direction);

    if (availableShipPositions.size != 0) {
        Position firstMastPosition = availableShipPositions.positions[rand() % availableShipPositions.size];

        ship.shipMasts[0] = (ShipMast){ firstMastPosition, false };
        for (int i = 1; i < shipType; i++) {
            Position mastPosition = positionMast(ship.shipMasts[i - 1].position, direction);
            ship.shipMasts[i] = (ShipMast){ mastPosition, false };
        }
        return ship;
    }
}
