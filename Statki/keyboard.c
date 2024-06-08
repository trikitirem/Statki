#include "common.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

int convertLetterToColumnIndex(char letter) {
    return (int)toupper(letter) - 65;
}

bool isIndexCorrect(int index) {
    if (index >= 0 && index < 10)
        return true;

    return false;
}

void displayInputErrorMessage() {
    printf("Nieprawilowe koordynaty!\n");
}

Position handlePositionInput() {
    char rowInput, colInput;
    
    while(true) {
        printf("Podaj wiersz i kolumne (np. A5): \n");

        fseek(stdin, 0, SEEK_END);
        if(scanf_s("%c%c", &colInput, (unsigned int)sizeof(colInput), &rowInput, (unsigned int)sizeof(rowInput)) < 2 || ferror(stdin)) {
            displayInputErrorMessage();
        }
        else {
            int columnIndex = convertLetterToColumnIndex(colInput);
            int rowIndex = atoi(&rowInput) - 1; // liczone od 0 nie od 1
            
            if (isIndexCorrect(columnIndex) && isIndexCorrect(rowIndex)) {
                Position position = { columnIndex, rowIndex };
                return position;
            }
            else {
                displayInputErrorMessage();
            }
        }
    }
}