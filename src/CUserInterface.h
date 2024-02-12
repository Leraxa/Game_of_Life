#include "CLife.h"

class CUserInterface
{
public:
	CUserInterface(); //Standartkonstruktor, startet die UI
	~CUserInterface(); //Standartdestruktor

	class Name {}; //Exception ungültiger Dateiname

private:
	void displayGameStart(); //Startanimation
	void displayTitle(); //Titel
	void displayMainMenu(); //Hauptmenü
	void displayAnimationType(CLife life); //Menü zur Selektierung schrittweise Animation oder fließend
	void displayAnimation(bool a, CLife life); //Animation, übernimmt bool um zwischen Animationsart zu unterscheiden
	void displayMenuDatei(); //Menü zur Auswahl einer Startdatei
	void displayEdit(); //Menü zum bearbeiten eines zufälligen Startzustandes
	void displayEnd(); //Endscreen
	void easterEgg(); // :-)
	void clearScreen(); //räumt die Konsole auf
	void setConsoleColor(int color); //ändert die Textfarbe
	void gotoxy(int x, int y); //bewegt Cursor zur x-y-Koordinate
};

