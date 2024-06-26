#pragma once
#include "common.h"

// Funkcja wyświetlająca konkretne pole na planszy
void displayBoardField(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount, Position boardFieldPosition);

// Funkcja wyświetlająca planszę gry
void displayBoard(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);
