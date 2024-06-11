#pragma once
#include "common.h"

// Funkcja wyœwietlaj¹ca konkretne pole na planszy
void displayBoardField(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount, Position boardFieldPosition);

// Funkcja wyœwietlaj¹ca planszê gry
void displayBoard(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);
