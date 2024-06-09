#pragma once

// W tym pliku znajduj¹ siê wszystkie funkcje obs³uguj¹ce rozgrywkê 

#include "common.h"
#include <stdbool.h>

typedef struct {
	bool targetHit;
	bool sunken;
	Position hitPosition;
} HitFeedback;

typedef struct {
	int ship;
	int mast;
} ShipMastPosition;

// Funkcja obs³uguj¹ca rozgrywkê
// Powtarzany jest w niej cykl gry, do czasu a¿ nie zostan¹ zatopione wszystkie statki
void gameplayLoop(Ship* fleet);

// Funkcja pozwalaj¹ca wybraæ koordynaty celu
// Je¿eli koordynaty by³y ju¿ wczeœniej podane, u¿ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja pozwalaj¹ca wybraæ koordynaty celu
// Je¿eli koordynaty by³y ju¿ wczeœniej podane, u¿ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja sprawdzaj¹ca czy strza³ trafi³ w któryœ z masztów statku
// Zwraca indeks trafionego masztu
// Je¿eli ¿aden masz nie zosta³ trafiony, zwraca -1
int findMastPositionIndex(Ship ship, Position hitPosition);

// Funkcja sprawdzaj¹ca czy maszt któregoœ ze statków zosta³ trafiony
// Zwraca indeks statku oraz indeks masztu
// Gdy nie dosz³o do trafienia, dla obydwu parametrów zwracane jest -1
ShipMastPosition confirmHit(Ship* fleet, Position hitPosition);

// Funkcja sprawdzaj¹ca czy podany statek zaton¹³
bool shipSunken(Ship ship);

// Funkcja która obs³uguje wystrzelenie pocisku
// Zwraca informacjê czy któryœ ze statków zosta³ trafiony, zatopiony oraz koordynaty wystrza³u
HitFeedback fireShot(Ship* fleet, Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja wyœwietlaj¹ca u¿ytkownikowi informacjê o dokonanym przez niego strzale 
void displayShotFeedbackMessage(HitFeedback hitFeedback);