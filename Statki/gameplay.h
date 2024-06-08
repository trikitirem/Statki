#pragma once
#include "common.h"
#include <stdbool.h>

typedef struct {
	bool targetHit;
	bool sunken;
} HitFeedback;

HitFeedback fireShot(Position position);
void displayShotFeedbackMessage(HitFeedback hitFeedback);
void gameplayLoop(Ship* fleet);
Position aim(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount);
