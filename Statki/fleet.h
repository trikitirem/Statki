#pragma once
#include "common.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
} Direction;

// Funkcja odczytuj¹ca flotê z pliku
Ship* getFleet(char* fileName);

// Funkcja generuj¹ca flotê statków
// Zasada dzia³ania:
// 1. Iterujemy po typach statków, w kolejnoœci od najwiêkszego do najmniejszego
//    (Zaczynaj¹c od postawienia wiêkszych statków wyst¹pi mniejsze ryzyko nie znalezienia miejsca na statek)
// 2. Dla ka¿dego typu statku pobieramy iloœæ, któr¹ dla niego nale¿y wygenerowaæ
// 3. Statek dodajemy do tablicy
Ship* generateFleet();

// Funkcja generuj¹ca statek
// Zasada dzia³ania:
// 1. Losowany jest kierunek w jakim postawiony mo¿e byæ statek
// 2. Wyszukiwane s¹ pozycje w których statek mo¿e byæ umieszczony.
//    Przy okreœlaniu tych pozycji brane s¹ pod uwagê: d³ugoœæ statku, kierunek, rozmieszczenie innych statków
// 3. Spoœród wyszukanych pozycji losowana jest jedna z nich
// 4. Wylosowana pozycja staje siê koordynat¹ pierwszego masztu, kolejne maszty s¹ generowane poprzez przesuniêcie (offset) tej koordynaty w wylosowanym kierunku
// 5. Maszty zostaj¹ dodane do statku
Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja pomocnicza mapuj¹ca typ statku na iloœæ statków do wygenerowania
int mapShipTypeToShipCount(ShipType shipType);

// Funkcja pomocnicza pozwalaj¹ca umieœciæ maszt statku na planszy, na podstawie poprzedniego masztu.
// Do umiejscowienia brany jest pod uwagê kierunek u³o¿enia statku
Position positionMast(Position previousMastPosition, Direction direction);

