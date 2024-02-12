#include "Header.h"
#include "CLife.h"

CLife::CLife() {
	srand(time(NULL));	//Nutzt als Ausgangspunkt (seed) die Systemzeit, um immer unterschiedliche Ergebnisse zu erzielen
	int m;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m = rand() % 2;	//modulo 2, damit Wert immer 0 oder 1 annimmt
			mat[i][j] = m == 1 ? '*' : ' '; //bei 1 lebend, bei 0 tot
		}
	}
}

CLife::CLife(int a) {
	if (a < 1 || a > 100) {
		throw Parameter();
	}
	if (a % 1 != 0) {
		throw Parameter();
	}
	int r = (100 / a);
	int m;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m = rand() % r;	//Prozentsatz lebender bzw. toter Zellen wird angewendet
			mat[i][j] = m == 1 ? '*' : ' ';
		}
	}
}

CLife::CLife(char b) {
	FILE* fp = nullptr;
	//Je nach übergebenen Wert wird Datei 1, 2 oder 3 geöffnet und ausgelesen
	switch (b) {
	case 'a': {
		FILE* fp = fopen("datei1.txt", "rt");
		if (fp == NULL) {
			throw Datei();
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				mat[i][j] = (char)fgetc(fp);
			}
			fgetc(fp);
		}
		fclose(fp);

	}
			break;

	case 'b': {
		FILE* fp = fopen("datei2.txt", "rt");
		if (fp == NULL) {
			throw Datei();
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				mat[i][j] = (char)fgetc(fp);
			}
			fgetc(fp);
		}
		fclose(fp);
	}
			break;

	case 'c': {
		FILE* fp = fopen("datei3.txt", "rt");
		if (fp == NULL) {
			throw Datei();
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				mat[i][j] = (char)fgetc(fp);
			}
			fgetc(fp);
		}
		fclose(fp);
	}
			break;
	}
}

char CLife::matrix(int a, int b) { //Rückgabe Matrixelement
	char c = mat[a][b];
	return c;
}

void CLife::updateMatrix(int x, int y, char value) {
	mat[x][y] = value;
}

void CLife::display() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << mat[i][j];
		}
		cout << endl;
	}
}

void CLife::applyRules() {
	bool a;
	char mat2[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			a = alive(i, j);
			if (a) {	//wenn Zelle nach Regel lebendig, dann '*', ansonsten ' '
				mat2[i][j] = '*'; //mat2 notwendig, da wir sonst mat überschreiben und auf den neuen Wert die Regeln anwenden
			}
			else {
				mat2[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			mat[i][j] = mat2[i][j];	//kopieren von mat2 auf mat
		}
	}
}

bool CLife::alive(int x, int y) {
	int count = 0; //Zähler für Nachbarn
	int i;
	int j;
	for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < 10) {
				if (mat[i][j] == lebendig && !(i == x && j == y)) {
					count++; //wenn angrenzende lebende Zelle nicht die betrachtete Zelle ist, wird der Zähler erhöht
				}
			}
		}
	}
	if (count < 2 || count > 3) {
		return false; //weniger als 2 oder mehr als 3 Nachbarn = tot
	}
	else if (mat[i][j] == tot && count == 3) {
		return true; //wird wiederbelebt wenn die Zelle tot ist und genau 3 Nachbarn hat
	}
	else if (mat[i][j] == lebendig && 2 <= count <= 3) {
		return true; //lebt weiter wenn sie 2 bis 3 Nachbarn hat
	}
}

CLife::~CLife() {
	delete[] mat;
}