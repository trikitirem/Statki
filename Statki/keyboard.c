#include "common.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

void displayInputErrorMessage() {
    printf("Nieprawilowe koordynaty!\n");
}

// Funkcja pobieraj¹ca koordynaty z klawiatury,
// konwertuje je na pozycjê, by ³atwo mo¿na by³o j¹ porównaæ z pozycj¹ statków
Position getPositionInput() {
    char colInput;
    int rowInput;

    while(true) {
        printf("Podaj wiersz i kolumne (np. A5): \n");

        fseek(stdin, 0, SEEK_END);
        if(scanf_s("%c%d", &colInput, (unsigned int)sizeof(colInput), &rowInput) < 2 || ferror(stdin)) {
            displayInputErrorMessage();
        }
        else {
            int columnIndex = convertLetterToCoordinate(colInput);
            int rowIndex = rowInput - 1; // liczone od 0 nie od 1
            
            if (isCoordinateCorrect(columnIndex) && isCoordinateCorrect(rowIndex)) {
                Position position = { columnIndex, rowIndex };
                return position;
            }
            else displayInputErrorMessage();
        }
    }
}