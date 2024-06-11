#pragma once
#include "common.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
} Direction;

// Funkcja odczytuj�ca flot� z pliku
Ship* getFleet(char* fileName);

// Funkcja generuj�ca flot� statk�w
// Zasada dzia�ania:
// 1. Iterujemy po typach statk�w, w kolejno�ci od najwi�kszego do najmniejszego
//    (Zaczynaj�c od postawienia wi�kszych statk�w wyst�pi mniejsze ryzyko nie znalezienia miejsca na statek)
// 2. Dla ka�dego typu statku pobieramy ilo��, kt�r� dla niego nale�y wygenerowa�
// 3. Statek dodajemy do tablicy
Ship* generateFleet();

// Funkcja generuj�ca statek
// Zasada dzia�ania:
// 1. Losowany jest kierunek w jakim postawiony mo�e by� statek
// 2. Wyszukiwane s� pozycje w kt�rych statek mo�e by� umieszczony.
//    Przy okre�laniu tych pozycji brane s� pod uwag�: d�ugo�� statku, kierunek, rozmieszczenie innych statk�w
// 3. Spo�r�d wyszukanych pozycji losowana jest jedna z nich
// 4. Wylosowana pozycja staje si� koordynat� pierwszego masztu, kolejne maszty s� generowane poprzez przesuni�cie (offset) tej koordynaty w wylosowanym kierunku
// 5. Maszty zostaj� dodane do statku
Ship generateShip(ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja pomocnicza mapuj�ca typ statku na ilo�� statk�w do wygenerowania
int mapShipTypeToShipCount(ShipType shipType);

// Funkcja pomocnicza pozwalaj�ca umie�ci� maszt statku na planszy, na podstawie poprzedniego masztu.
// Do umiejscowienia brany jest pod uwag� kierunek u�o�enia statku
Position positionMast(Position previousMastPosition, Direction direction);

