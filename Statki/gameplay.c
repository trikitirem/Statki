// W tym pliku znajduj� si� wszystkie funkcje obs�uguj�ce rozgrywk� 

#include <stdbool.h>
#include "common.h"
#include "gameplay.h"
#include <stdio.h>
#include "keyboard.h"
#include "board.h"
#include <stdlib.h>
#include <stdlib.h>

// Funkcja obs�uguj�ca rozgrywk�
// Powtarzany jest w niej cykl gry, do czasu a� nie zostan� zatopione wszystkie statki
void gameplayLoop(Ship* fleet) {
	int targetHitsCount = 0;
	Position targetHits[ALL_SHIPS_MASTS];

	int missedHitsCount = 0;
	Position missedHits[BOARD_SIZE * BOARD_SIZE - ALL_SHIPS_MASTS];

	int sunkenCount = 0;

	while (sunkenCount < ALL_SHIPS_COUNT) {
		displayBoard(targetHits, targetHitsCount, missedHits, missedHitsCount);
		HitFeedback hitFeedback = fireShot(fleet, targetHits, targetHitsCount, missedHits, missedHitsCount);

		system("cls");

		if (!hitFeedback.targetHit) {
			missedHits[missedHitsCount] = hitFeedback.hitPosition;
			missedHitsCount++;
		}
		else {
			targetHits[targetHitsCount] = hitFeedback.hitPosition;
			targetHitsCount++;

			if (hitFeedback.sunken) sunkenCount++;
		}
		displayShotFeedbackMessage(hitFeedback);
	}

	system("cls");
	printf("Wygranko\n\n\n");
}

// Funkcja pozwalaj�ca wybra� koordynaty celu
// Je�eli koordynaty by�y ju� wcze�niej podane, u�ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
	while (true) {
		Position hitPosition = handlePositionInput();

		bool hitPositionInTargetHits = findPositionIndex(targetHits, targetHitsCount, hitPosition) != -1;
		bool hitPositionInMissedHits = findPositionIndex(missedHits, missedHitsCount, hitPosition) != -1;

		if (!hitPositionInTargetHits && !hitPositionInMissedHits) {
			return hitPosition;
		}

		printf("Juz wykonano strzal na ta pozycje\n");
	}
}

// Funkcja sprawdzaj�ca czy strza� trafi� w kt�ry� z maszt�w statku
// Zwraca indeks trafionego masztu
// Je�eli �aden masz nie zosta� trafiony, zwraca -1
int findMastPositionIndex(Ship ship, Position hitPosition) {
	for (int i = 0; i < ship.type; i++) {
		if (ship.shipMasts[i].position.x == hitPosition.x && ship.shipMasts[i].position.y == hitPosition.y) {
			return i;
		}
	}
	return -1;
}

// Funkcja sprawdzaj�ca czy maszt kt�rego� ze statk�w zosta� trafiony
// Zwraca indeks statku oraz indeks masztu
// Gdy nie dosz�o do trafienia, dla obydwu parametr�w zwracane jest -1
ShipMastPosition confirmHit(Ship* fleet, Position hitPosition) {
	for (int i = 0; i < ALL_SHIPS_COUNT; i++) {		
		int mast = findMastPositionIndex(fleet[i], hitPosition);

		if (mast != -1) {
			fleet[i].shipMasts[mast].hit = true;
			ShipMastPosition shipMastPosition = { i, mast };
			return shipMastPosition;
		}
	}

	ShipMastPosition empty = {-1, -1};
	return empty;
}

// Funkcja sprawdzaj�ca czy podany statek zaton��
bool shipSunken (Ship ship) {
	for (int i = 0; i < ship.type; i++) {
		if (!ship.shipMasts[i].hit) {
			return false;
		}
		
	}

	return true;
}

// Funkcja kt�ra obs�uguje wystrzelenie pocisku
// Zwraca informacj� czy kt�ry� ze statk�w zosta� trafiony, zatopiony oraz koordynaty wystrza�u
HitFeedback fireShot(Ship* fleet, Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
	Position hitPosition = aim(targetHits, targetHitsCount, missedHits, missedHitsCount);
	ShipMastPosition mastPosition = confirmHit(fleet, hitPosition);

	if (mastPosition.ship == -1 || mastPosition.mast == -1) {
		HitFeedback negativeHitFeedback = {false, false, hitPosition};
		return negativeHitFeedback;
	}

	if (shipSunken(fleet[mastPosition.ship])) {
		HitFeedback sunkenHitFeedback = { true, true, hitPosition };
		return sunkenHitFeedback;
	}

	HitFeedback hitFeedback = { true, false, hitPosition };
	return hitFeedback;
}

// Funkcja wy�wietlaj�ca u�ytkownikowi informacj� o dokonanym przez niego strzale 
void displayShotFeedbackMessage(HitFeedback hitFeedback) {
	if(!hitFeedback.targetHit) {
		printf("pudlo\n");
	}
	else if (hitFeedback.sunken) {
		printf("trafiony zatopiony\n");
	}
	else {
		printf("trafiony\n");
	}

	printf("\n");
}

