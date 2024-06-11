#pragma once
#include "common.h"

// Funkcja wy�wietlaj�ca konkretne pole na planszy
void displayBoardField(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount, Position boardFieldPosition);

// Funkcja wy�wietlaj�ca plansz� gry
void displayBoard(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);
