#include <stdbool.h>
#include "common.h"
#include "gameplay.h"
#include <stdio.h>
#include "keyboard.h"
#include "board.h"
#include <stdlib.h>
#include <stdlib.h>

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

ShipMastPosition confirmHit(Ship* fleet, Position hitPosition) {
	for (int i = 0; i < ALL_SHIPS_COUNT; i++) {		
		int mast = findPositionIndex(fleet[i].shipMasts, fleet[i].type, hitPosition);

		if (mast != -1) {
			fleet[i].shipMasts[mast].hit = true;
			ShipMastPosition shipMastPosition = { i, mast };
			return shipMastPosition;
		}
	}

	ShipMastPosition empty = {-1, -1};
	return empty;
}

bool shipSunken (Ship ship) {
	for (int i = 0; i < ship.type; i++) {
		if (!ship.shipMasts[i].hit) {
			return false;
		}
		
	}

	return true;
}

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
	printf("Wygranko");
}