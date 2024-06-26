#include "common.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

void displayInputErrorMessage() {
    printf("Nieprawilowe koordynaty!\n");
}

// Funkcja pobieraj�ca koordynaty z klawiatury,
// konwertuje je na pozycj�, by �atwo mo�na by�o j� por�wna� z pozycj� statk�w
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

// Funkcja kt�ra sprawdza czy u�ytkownik chce kontynuowa� gre
bool getUserConfirmation() {
    printf("Kontynuowac gre? (t/n)");
    char choice;

    while(true) {
        fseek(stdin, 0, SEEK_END);
        if (scanf_s("%c", &choice, (unsigned int)sizeof(choice)) < 1 || ferror(stdin)) {
            printf("Wystapil blad przy wczytywaniu wejscia z klawiatury!\n");
        }
        else if(toupper(choice) == 'T') {
            return true;
        }
        else if (toupper(choice) == 'N') {
            return false;
        }
        else {
            printf("Wpisz t lub n\n");
        }
    }
}