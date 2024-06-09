#pragma once

// W tym pliku znajduj� si� wszystkie funkcje obs�uguj�ce rozgrywk� 

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

// Funkcja obs�uguj�ca rozgrywk�
// Powtarzany jest w niej cykl gry, do czasu a� nie zostan� zatopione wszystkie statki
void gameplayLoop(Ship* fleet);

// Funkcja pozwalaj�ca wybra� koordynaty celu
// Je�eli koordynaty by�y ju� wcze�niej podane, u�ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja pozwalaj�ca wybra� koordynaty celu
// Je�eli koordynaty by�y ju� wcze�niej podane, u�ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja sprawdzaj�ca czy strza� trafi� w kt�ry� z maszt�w statku
// Zwraca indeks trafionego masztu
// Je�eli �aden masz nie zosta� trafiony, zwraca -1
int findMastPositionIndex(Ship ship, Position hitPosition);

// Funkcja sprawdzaj�ca czy maszt kt�rego� ze statk�w zosta� trafiony
// Zwraca indeks statku oraz indeks masztu
// Gdy nie dosz�o do trafienia, dla obydwu parametr�w zwracane jest -1
ShipMastPosition confirmHit(Ship* fleet, Position hitPosition);

// Funkcja sprawdzaj�ca czy podany statek zaton��
bool shipSunken(Ship ship);

// Funkcja kt�ra obs�uguje wystrzelenie pocisku
// Zwraca informacj� czy kt�ry� ze statk�w zosta� trafiony, zatopiony oraz koordynaty wystrza�u
HitFeedback fireShot(Ship* fleet, Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);

// Funkcja wy�wietlaj�ca u�ytkownikowi informacj� o dokonanym przez niego strzale 
void displayShotFeedbackMessage(HitFeedback hitFeedback);