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

// Funkcja sprawdzaj¹ca kolizje z innymi statkami
// Zasada dzia³ania:
// Aby aby sprawdzic czy pozycja i pole wokó³ niej nie s¹ okupowane dodawane s¹ do niej przesuniêcia.
// Przesuniêcia s¹ generowane w pêtlach.
// Je¿eli przesuniêcie w osi x bêdzie równe -1, to sprawdzamy pozycje z lewej strony od punktu s¹ okupowane, je¿eli 1 to z prawej
// Dla osi y dzia³a to tak samo. 
// W taki sposób mo¿emy sprawdziæ wszystkie pozycje wokó³ naszego pola i nasze pole
bool checkCollision(Position occupiedPosition, Position shipMastPosition);

// Funkcja sprawdzaj¹ca czy okreœlona pozycja na tablicy jest ju¿ okupowana i czy nie koliduje z innymi statkami
bool isPositionOccupied(Position position, Ship* fleet, int fleetSize, int boardSize);

// Funkcja sprawdzaj¹ca czy mo¿na na danym umieœciæ pierwszy maszt statku poziomego
bool canPlaceShipHorizontally(int x, int y, ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja sprawdzaj¹ca czy mo¿na na danym umieœciæ pierwszy maszt statku pionowego
bool canPlaceShipVertically(int x, int y, ShipType shipType, Ship* fleet, int fleetSize);

// Funkcja zwracaj¹ca wszystkie punkty w którym mo¿na umiejscowiæ statek
// Przy sprawdzaniu brane s¹ pod uwagê: d³ugoœæ statku, kierunek, rozmieszczenie innych statków
// Zwrócone punkty mog¹ pos³u¿yæ jako koordynata pierwszego masztu statku
PositionArray findAvailableShipPositions(ShipType shipType, Ship* fleet, int fleetSize, Direction direction);