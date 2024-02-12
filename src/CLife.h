#pragma once
class CLife
{
public:
	//3 überladene Konstruktoren
	CLife(); //Standartkonstruktor (Zufall)
	CLife(int a); //Konstruktor (% der lebenden Zellen)
	CLife(char b); //Konstruktor (lesen aus Datei)
	char matrix(int a, int b); //Ausgabe Wert der Matrix an bestimmter Stelle
	void updateMatrix(int x, int y, char value); //Update der Matrix an bestimmter Stelle
	void display(); //Standartausgabe der Matrix (fürs Testen genutzt)
	void applyRules(); //Anwendung der Regeln und entsprechende Änderung der Matrixwerte
	bool alive(int i, int j); //prüft, ob Zelle in der nächsten Generation lebendig oder tot ist

	class Parameter {}; //Exception ungültiger Wert für Prozentberechnung (1-100, keine Nachkommastelle)
	class Datei {}; //Exception öffnen einer Datei

	~CLife(); //Standartdestruktor
private:
	char mat[10][10]; //Matrix
	char tot = ' '; //Zeichen für tote Zelle (Testzwecke)
	char lebendig = '*'; //Zeichen für lebende Zelle (Testzwecke)
};