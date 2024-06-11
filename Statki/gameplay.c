// W tym pliku znajduj¹ siê wszystkie funkcje obs³uguj¹ce rozgrywkê 

#include <stdbool.h>
#include "common.h"
#include "gameplay.h"
#include <stdio.h>
#include "keyboard.h"
#include "board.h"
#include <stdlib.h>
#include <stdlib.h>

// Funkcja obs³uguj¹ca rozgrywkê
// Powtarzany jest w niej cykl gry, do czasu a¿ nie zostan¹ zatopione wszystkie statki
void gameplayLoop(Ship* fleet) {
	int targetHitsCount = 0;
	Position* targetHits= NULL;

	int missedHitsCount = 0;
	Position* missedHits = NULL;

	int sunkenCount = 0;

	while (sunkenCount < FLEET_SIZE) {
		displayBoard(targetHits, targetHitsCount, missedHits, missedHitsCount);
		HitFeedback hitFeedback = fireShot(fleet, targetHits, targetHitsCount, missedHits, missedHitsCount);

		system("cls");

		if (!hitFeedback.targetHit) {
			missedHits = realloc(missedHits, (missedHitsCount + 1) * sizeof(Position));
			missedHits[missedHitsCount++] = hitFeedback.hitPosition;
		}
		else {
			targetHits = realloc(targetHits, (targetHitsCount + 1) * sizeof(Position));
			targetHits[targetHitsCount++] = hitFeedback.hitPosition;

			if (hitFeedback.sunken) sunkenCount++;
		}
		displayShotFeedbackMessage(hitFeedback);
	}

	free(targetHits);
	free(missedHits);

	system("cls");
	printf("\n\n\nWygrana!!!!!!\n\n\n");
}

// Funkcja pozwalaj¹ca wybraæ koordynaty celu
// Je¿eli koordynaty by³y ju¿ wczeœniej podane, u¿ytkownik zostanie poproszony o podanie innych 
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
	while (true) {
		Position hitPosition = getPositionInput();

		bool hitPositionInTargetHits = findPositionIndex(targetHits, targetHitsCount, hitPosition) != -1;
		bool hitPositionInMissedHits = findPositionIndex(missedHits, missedHitsCount, hitPosition) != -1;

		if (!hitPositionInTargetHits && !hitPositionInMissedHits) {
			return hitPosition;
		}

		printf("Juz wykonano strzal na ta pozycje\n");
	}
}

// Funkcja sprawdzaj¹ca czy strza³ trafi³ w któryœ z masztów statku
// Zwraca indeks trafionego masztu
// Je¿eli ¿aden masz nie zosta³ trafiony, zwraca -1
int findMastPositionIndex(Ship ship, Position hitPosition) {
	for (int i = 0; i < ship.type; i++) {
		if (ship.shipMasts[i].position.x == hitPosition.x && ship.shipMasts[i].position.y == hitPosition.y) {
			return i;
		}
	}
	return -1;
}

// Funkcja sprawdzaj¹ca czy maszt któregoœ ze statków zosta³ trafiony
// Zwraca indeks statku oraz indeks masztu
// Gdy nie dosz³o do trafienia, dla obydwu parametrów zwracane jest -1
ShipMastPosition confirmHit(Ship* fleet, Position hitPosition) {
	for (int i = 0; i < FLEET_SIZE; i++) {		
		int mast = findMastPositionIndex(fleet[i], hitPosition);

		if (mast != -1) {
			fleet[i].shipMasts[mast].hit = true;
			return(ShipMastPosition) {i, mast};
		}
	}

	return (ShipMastPosition){-1, -1};
}

// Funkcja sprawdzaj¹ca czy podany statek zaton¹³
bool shipSunken (Ship ship) {
	for (int i = 0; i < ship.type; i++) {
		if (!ship.shipMasts[i].hit) {
			return false;
		}
		
	}

	return true;
}

// Funkcja która obs³uguje wystrzelenie pocisku
// Zwraca informacjê czy któryœ ze statków zosta³ trafiony, zatopiony oraz koordynaty wystrza³u
HitFeedback fireShot(Ship* fleet, Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
	Position hitPosition = aim(targetHits, targetHitsCount, missedHits, missedHitsCount);
	ShipMastPosition mastPosition = confirmHit(fleet, hitPosition);

	if (mastPosition.ship == -1 || mastPosition.mast == -1) {
		return (HitFeedback) { false, false, hitPosition };
	}

	if (shipSunken(fleet[mastPosition.ship])) {
		return (HitFeedback) { true, true, hitPosition };
	}

	return (HitFeedback) { true, false, hitPosition };
}

// Funkcja wyœwietlaj¹ca u¿ytkownikowi informacjê o dokonanym przez niego strzale 
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

