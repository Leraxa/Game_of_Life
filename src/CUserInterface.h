#include "CLife.h"

class CUserInterface
{
public:
	CUserInterface(); //Standartkonstruktor, startet die UI
	~CUserInterface(); //Standartdestruktor

	class Name {}; //Exception ung�ltiger Dateiname

private:
	void displayGameStart(); //Startanimation
	void displayTitle(); //Titel
	void displayMainMenu(); //Hauptmen�
	void displayAnimationType(CLife life); //Men� zur Selektierung schrittweise Animation oder flie�end
	void displayAnimation(bool a, CLife life); //Animation, �bernimmt bool um zwischen Animationsart zu unterscheiden
	void displayMenuDatei(); //Men� zur Auswahl einer Startdatei
	void displayEdit(); //Men� zum bearbeiten eines zuf�lligen Startzustandes
	void displayEnd(); //Endscreen
	void easterEgg(); // :-)
	void clearScreen(); //r�umt die Konsole auf
	void setConsoleColor(int color); //�ndert die Textfarbe
	void gotoxy(int x, int y); //bewegt Cursor zur x-y-Koordinate
};

