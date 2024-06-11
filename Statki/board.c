#include "common.h"
#include <stdio.h>

void displayColumnLetters () {
    printf("   A B C D E F G H I J\n");
}

void displayRowNumber (index) {
    printf("%2d ", index + 1);
}

// Funkcja wyœwietlaj¹ca konkretne pole na planszy
void displayBoardField(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount, Position boardFieldPosition) {
    if(findPositionIndex(targetHits, targetHitsCount, boardFieldPosition) != -1){
        printf("%c ", 'x');
    }
    else if (findPositionIndex(missedHits, missedHitsCount, boardFieldPosition) != -1) {
        printf("%c ", 'o');
    }
    else {
        printf("%c ", '~');
    }
}

// Funkcja wyœwietlaj¹ca planszê gry
void displayBoard(Position* targetHits, int targetHitsCount, Position* missedHits, int missedHitsCount) {
    displayColumnLetters();
    for (int i = 0; i < BOARD_SIZE; i++) {
        displayRowNumber(i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            Position boardFieldPosition = {j, i};
            displayBoardField(targetHits, targetHitsCount, missedHits, missedHitsCount, (Position) {j,i});
        }
        printf("\n");
    }

    printf("\n");
}