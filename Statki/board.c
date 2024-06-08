#include "common.h"
#include <stdio.h>

// Funkcja wyœwietlaj¹ca planszê
void displayBoard(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", '~');
        }
        printf("\n");
    }

    printf("\n");
}