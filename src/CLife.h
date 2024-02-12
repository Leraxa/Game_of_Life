#pragma once
class CLife
{
public:
	//3 �berladene Konstruktoren
	CLife(); //Standartkonstruktor (Zufall)
	CLife(int a); //Konstruktor (% der lebenden Zellen)
	CLife(char b); //Konstruktor (lesen aus Datei)
	char matrix(int a, int b); //Ausgabe Wert der Matrix an bestimmter Stelle
	void updateMatrix(int x, int y, char value); //Update der Matrix an bestimmter Stelle
	void display(); //Standartausgabe der Matrix (f�rs Testen genutzt)
	void applyRules(); //Anwendung der Regeln und entsprechende �nderung der Matrixwerte
	bool alive(int i, int j); //pr�ft, ob Zelle in der n�chsten Generation lebendig oder tot ist

	class Parameter {}; //Exception ung�ltiger Wert f�r Prozentberechnung (1-100, keine Nachkommastelle)
	class Datei {}; //Exception �ffnen einer Datei

	~CLife(); //Standartdestruktor
private:
	char mat[10][10]; //Matrix
	char tot = ' '; //Zeichen f�r tote Zelle (Testzwecke)
	char lebendig = '*'; //Zeichen f�r lebende Zelle (Testzwecke)
};