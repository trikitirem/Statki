#include <stdbool.h>
#include "common.h"
#include "gameplay.h"
#include <stdio.h>
#include "keyboard.h"
#include "board.h"
#include <stdlib.h>
#include <stdlib.h>

HitFeedback fireShot(Position position) {
	HitFeedback hitFeedback;
	
	hitFeedback.targetHit = true;
	hitFeedback.sunken = true;

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

Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
	while(true) {
		Position hitPosition = handlePositionInput();

		bool hitPositionInTargetHits = findPositionIndex(targetHits, targetHitsCount, hitPosition) != -1;
		bool hitPositionInMissedHits = findPositionIndex(missedHits, missedHitsCount, hitPosition) != -1;

		if (!hitPositionInTargetHits && !hitPositionInMissedHits) {
			return hitPosition;
		}

		printf("Juz wykonano strzal na ta pozycje\n");
	}
}

void gameplayLoop(Ship* fleet) {
	int targetHitsCount = 0;
	Position targetHits[ALL_SHIPS_MODULES];

	int missedHitsCount = 0;
	Position missedHits[BOARD_SIZE * BOARD_SIZE - ALL_SHIPS_MODULES];

	int sunkenCount = 0;

	while (sunkenCount < 3) {
		displayBoard(targetHits, targetHitsCount, missedHits, missedHitsCount);

		Position hitPosition = aim(targetHits, targetHitsCount, missedHits, missedHitsCount);

		HitFeedback hitFeedback = fireShot(hitPosition);

		system("cls");

		if (!hitFeedback.targetHit) {
			missedHits[missedHitsCount] = hitPosition;
			missedHitsCount++;
		}
		else {
			targetHits[targetHitsCount] = hitPosition;
			targetHitsCount++;

			if (hitFeedback.sunken) sunkenCount++;
		}
		displayShotFeedbackMessage(hitFeedback);
	}

	system("cls");
	printf("Wygranko");
}