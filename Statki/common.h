#pragma once

// W tym pliku znajduje si� wszystko co mo�e by� u�yteczne w wielu plikach aplikacji

#include <stdbool.h>

// Definicje sta�ych
// Zmieniaj�c te parametry mo�na zmieni� rozgrywk� np. poprzez zwi�kszenie planszy czy zmienienie ilo�ci statk�w
// Uwaga! Zmienienie tych parametr�w mo�e zepsu� rozgrywk� dla plansz wczytywanych z plik�w tekstowych
#define BOARD_SIZE 10
#define SINGLE_MAST_COUNT 4
#define TWO_MAST_COUNT 3
#define THREE_MAST_COUNT  2
#define FOUR_MAST_COUNT  1
#define ALL_SHIPS_COUNT (SINGLE_MAST_COUNT + TWO_MAST_COUNT + THREE_MAST_COUNT + FOUR_MAST_COUNT)
#define ALL_SHIPS_MASTS (SINGLE_MAST_COUNT * 4 + TWO_MAST_COUNT * 3 + THREE_MAST_COUNT * 2 + FOUR_MAST_COUNT)

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

// Funckcja poruwnuj�ca dwie pozycje
// Zwraca prawd� gdy dla obydwu pozycji koordynaty x i y s� takie same
bool areThePositionsEqual(Position position1, Position position2);

// Funkcja sprawdzaj�ca czy w tablicy pozycji wyst�puje podana
// Zwraca indeks znalezionej pozycji, lub -1 gdy taka nie zostanie znaleziona
int findPositionIndex(Position* positions, int size, Position positionToFind);

// Konwertuje liter� na liczb�, kt�ra mo�e by� u�yta jako koordynata
int convertLetterToCoordinate(char letter);

// Sprawdza czy podana koordynata mo�e le�e� na planszy gry
bool isCoordinateCorrect(int index);

// Dodaje przesuni�cie do pozycji
Position addOffsetToPosition(Position position, Position offset);
