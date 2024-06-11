#pragma once
#include "common.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
} Direction;

typedef struct {
    Position* positions;
    int size;
} PositionArray;


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

// Funkcja sprawdzaj�ca kolizje z innymi statkami
// Zasada dzia�ania:
// Aby aby sprawdzic czy pozycja i pole wok� niej nie s� okupowane dodawane s� do niej przesuni�cia.
// Przesuni�cia s� generowane w p�tlach.
// Je�eli przesuni�cie w osi x b�dzie r�wne -1, to sprawdzamy pozycje z lewej strony od punktu s� okupowane, je�eli 1 to z prawej
// Dla osi y dzia�a to tak samo. 
// W taki spos�b mo�emy sprawdzi� wszystkie pozycje wok� naszego pola i nasze pole
bool checkCollision(Position occupiedPosition, Position shipMastPosition);

// Funkcja sprawdzaj�ca czy okre�lona pozycja na tablicy jest ju� okupowana i czy nie koliduje z innymi statkami
bool isPositionOccupied(Position position, Ship* fleet, int fleetSize, int boardSize);

// Funkcja sprawdzaj�ca czy mo�na na danym umie�ci� pierwszy maszt statku poziomego
bool canPlaceShipHorizontally(int x, int y, ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja sprawdzaj�ca czy mo�na na danym umie�ci� pierwszy maszt statku pionowego
bool canPlaceShipVertically(int x, int y, ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja zwracaj�ca wszystkie punkty w kt�rym mo�na umiejscowi� statek
// Przy sprawdzaniu brane s� pod uwag�: d�ugo�� statku, kierunek, rozmieszczenie innych statk�w
// Zwr�cone punkty mog� pos�u�y� jako koordynata pierwszego masztu statku
PositionArray findAvailableShipPositions(ShipType shipType, Ship* fleet, int fleetSize, Direction direction);