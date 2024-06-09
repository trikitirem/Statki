#include <stdbool.h>
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// Funckcja poruwnuj�ca dwie pozycje
// Zwraca prawd� gdy dla obydwu pozycji koordynaty x i y s� takie same
bool areThePositionsEqual(Position position1, Position position2) {
	if (position1.x == position2.x && position1.y == position2.y)
		return true;

	return false;
}

// Funkcja sprawdzaj�ca czy w tablicy pozycji wyst�puje podana
// Zwraca indeks znalezionej pozycji, lub -1 gdy taka nie zostanie znaleziona
int findPositionIndex(Position* positions, int size, Position positionToFind) {
    for (int i = 0; i < size; i++) {
        if (areThePositionsEqual(positions[i], positionToFind)) {
            return i;
        }
    }
    return -1;
}

// Konwertuje liter� na liczb�, kt�ra mo�e by� u�yta jako koordynata
int convertLetterToCoordinate(char letter) {
    return (int)toupper(letter) - 65;
}

// Sprawdza czy podana koordynata mo�e le�e� na planszy gry
bool isCoordinateCorrect(int index) {
    if (index >= 0 && index < BOARD_SIZE)
        return true;

    return false;
}

// Dodaje przesuni�cie do pozycji
Position addOffsetToPosition(Position position, Position offset) {
    Position newPosition = { position.x + offset.x, position.y + offset.y };
    return newPosition;
}