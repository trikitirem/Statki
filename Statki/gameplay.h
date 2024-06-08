#pragma once
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

void gameplayLoop(Ship* fleet);

