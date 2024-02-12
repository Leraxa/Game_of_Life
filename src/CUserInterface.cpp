#include "CUserInterface.h"
#include "CLife.h"
#include "Header.h"

//Foreground colors :
//
//0 : Black
//1 : Blue
//2 : Green
//3 : Cyan
//4 : Red
//5 : Magenta
//6 : Yellow
//7 : Light gray
//8 : Dark gray
//9 : Light blue
//10 : Light green
//11 : Light cyan
//12 : Light red
//13 : Light magenta
//14 : Light yellow
//15 : White
// 
//Background colors :
//
//0 : Black
//16 : Blue
//32 : Green
//48 : Cyan
//64 : Red
//80 : Magenta
//96 : Yellow
//112 : Light gray

CUserInterface::CUserInterface() {
    displayGameStart();
}

void CUserInterface::displayGameStart() {
    int r = 50; //Zeilen
    int c = 50; //Spalten
    //abgebildete char in der Animation
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=[]{}|;:,.<>?/";
    int size = characters.size();

    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> columnPosition(c, -1);

    int i = 0;
    while (i < 1000) {
        clearScreen();
        //random werden Buchstaben aus dem Array gewählt und an der gewählten Stelle platziert
        for (int col = 0; col < c; ++col) {
            if (columnPosition[col] == -1 || columnPosition[col] >= r || (rand() % r == 0)) {
                columnPosition[col] = 0;
            }
            else {
                setConsoleColor(13);

                for (int row = 0; row < r; ++row) {
                    if (row == columnPosition[col]) {
                        cout << characters[rand() % size];
                    }
                    else {
                        cout << ' ';
                    }
                }

                setConsoleColor(15);
                columnPosition[col]++;
            }
            i++;
        }

        cout << endl;
        Sleep(20);
    }
    setConsoleColor(15);
    clearScreen();
    displayMainMenu();
}

void CUserInterface::displayTitle() {
    setConsoleColor(13);

    cout << R"(
    ___       ___       ___       ___            ___       ___            ___       ___       ___       ___   
   /\  \     /\  \     /\__\     /\  \          /\  \     /\  \          /\__\     /\  \     /\  \     /\  \  
  /::\  \   /::\  \   /::L_L_   /::\  \        /::\  \   /::\  \        /:/  /    _\:\  \   /::\  \   /::\  \ 
 /:/\:\__\ /::\:\__\ /:/L:\__\ /::\:\__\      /:/\:\__\ /::\:\__\      /:/__/    /\/::\__\ /::\:\__\ /::\:\__\
 \:\:\/__/ \/\::/  / \/_/:/  / \:\:\/  /      \:\/:/  / \/\:\/__/      \:\  \    \::/\/__/ \/\:\/__/ \:\:\/  /
  \::/  /    /:/  /    /:/  /   \:\/  /        \::/  /     \/__/        \:\__\    \:\__\      \/__/   \:\/  / 
   \/__/     \/__/     \/__/     \/__/          \/__/                    \/__/     \/__/               \/__/  
                                                                                                                                                                                                                                                               
)" << endl;
    setConsoleColor(15);
}

void CUserInterface::displayMainMenu() {
    clearScreen();
    displayTitle();
    setConsoleColor(15);
    int Set[] = { 7, 7, 7 ,7, 7 }; //Farben der Menü-Buttons ohne Auswahl
    int counter = 1; //zeigt, welcher Button angewählt ist
    char key; //managed Eingabetaste

    for (int i = 0;;) {

        //Überschrift
        gotoxy(4, 10);
        setConsoleColor(9);
        cout << "Bitte mit den Pfeiltasten navigieren und mit Enter best\xC3\xA4tigen.";

        //Menü Buttons
        gotoxy(4, 11);
        setConsoleColor(Set[0]);
        cout << "Zufallsgenerator";

        gotoxy(4, 12);
        setConsoleColor(Set[1]);
        cout << "Startzustand editieren";

        gotoxy(4, 13);
        setConsoleColor(Set[2]);
        cout << "Prozent lebender Zellen eingeben";

        gotoxy(4, 14);
        setConsoleColor(Set[3]);
        cout << "Startdatei ausw\xC3\xA4hlen";

        gotoxy(4, 15);
        setConsoleColor(Set[4]);
        cout << "Beenden" << endl << endl;

        key = getch();

        if (key == 72 && (counter >= 2 && counter <= 5)) { //key-handler
            counter--;
        }
        if (key == 80 && (counter >= 1 && counter <= 4)) {
            counter++;
        }
        if (key == '\r') { //bei Betätigen der Enter-Taste erfolgt gewählte Aktion
            if (counter == 1) {
                CLife zufall;
                displayAnimationType(zufall);
            }
            if (counter == 2) {
                displayEdit();
            }
            if (counter == 3) {
                int userInput;
                gotoxy(37, 13);
                cout << ">> Zahl zwischen 1 und 100 eingeben: ";
                cin >> userInput;
                try {
                    CLife life(userInput);
                    displayAnimationType(life);
                }
                catch (CLife::Parameter) {
                    gotoxy(37, 13);
                    cout << ">> Ung\xC3\xBCltige Eingabe, keine Nachkommastellen verwenden";
                    Sleep(2000);
                    displayMainMenu();
                }

            }
            if (counter == 4) {
                displayMenuDatei();
            }
            if (counter == 5) {
                setConsoleColor(15);
                exit(0);
            }
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        //Farbe bei Anwählen
        if (counter == 1) {
            Set[0] = 13;
        }
        if (counter == 2) {
            Set[1] = 13;
        }
        if (counter == 3) {
            Set[2] = 13;
        }
        if (counter == 4) {
            Set[3] = 13;
        }
        if (counter == 5) {
            Set[4] = 12;
        }
    }
    //System habe ich bei allen weiteren Menüs übernommen
}

void CUserInterface::displayMenuDatei() {
    clearScreen();
    displayTitle();
    int Set[] = { 7, 7, 7, 7 };
    int counter = 1;
    char key;
    try {
        CLife lifeA('a'); //erstellt alle Matritzen für die Vorschau und spätere Animation (Dateikonstruktor)
        CLife lifeB('b');
        CLife lifeC('c');


        for (int i = 0;;) {

            gotoxy(4, 10);
            setConsoleColor(9);
            cout << "Bitte Datei ausw\xC3\xA4hlen";

            gotoxy(26, 12);
            setConsoleColor(Set[0]);
            cout << "Datei 1";
            //gibt Inhalt der Matritze an bestimmter Stelle im Terminal aus
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    gotoxy(20 + (i * 2), 14 + j);
                    cout << lifeA.matrix(i, j);
                }
            }

            gotoxy(52, 12);
            setConsoleColor(Set[1]);
            cout << "Datei 2";
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    gotoxy(46 + (i * 2), 14 + j);
                    cout << lifeB.matrix(i, j);
                }
            }

            gotoxy(78, 12);
            setConsoleColor(Set[2]);
            cout << "Datei 3";
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    gotoxy(73 + (i * 2), 14 + j);
                    cout << lifeC.matrix(i, j);
                }
            }

            gotoxy(4, 24);
            setConsoleColor(Set[3]);
            cout << "zur\xC3\xBC" << "ck";

            key = getch();

            if (key == 75 && (counter >= 2 && counter <= 4)) {
                counter--;
            }
            if (key == 77 && (counter >= 1 && counter <= 3)) {
                counter++;
            }
            if (key == '\r') {
                if (counter == 1) {
                    displayAnimationType(lifeA);
                }
                if (counter == 2) {
                    displayAnimationType(lifeB);
                }
                if (counter == 3) {
                    displayAnimationType(lifeC);
                }
                if (counter == 4) {
                    displayMainMenu();
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1) {
                Set[0] = 13;
            }
            if (counter == 2) {
                Set[1] = 13;
            }
            if (counter == 3) {
                Set[2] = 13;
            }
            if (counter == 4) {
                Set[3] = 12;
            }
        }
    }
    catch (CLife::Datei()) {
        gotoxy(4, 10);
        setConsoleColor(15);
        cout << "Fehler beim öffnen der Dateien. Wechsel ins Hauptmen\xC3\xBC";
        Sleep(2000);
        displayMainMenu();
    }

}

void CUserInterface::displayAnimationType(CLife life) {
    clearScreen();
    displayTitle();
    setConsoleColor(15);
    int Set[] = { 7, 7, 7 };
    int counter = 1;
    char key;

    for (int i = 0;;) {

        gotoxy(4, 10);
        setConsoleColor(9);
        cout << "Bitte Animationsart ausw\xC3\xA4hlen";


        gotoxy(4, 11);
        setConsoleColor(Set[0]);
        cout << "Schrittweise";

        gotoxy(4, 12);
        setConsoleColor(Set[1]);
        cout << "Flie\xC3\x9F" << "end";

        gotoxy(4, 13);
        setConsoleColor(Set[2]);
        cout << "zur\xC3\xBC" << "ck";

        key = getch();

        if (key == 72 && (counter >= 2 && counter <= 4)) {
            counter--;
        }
        if (key == 80 && (counter >= 1 && counter <= 2)) {
            counter++;
        }
        if (key == '\r') {
            if (counter == 1) {
                bool animation = false; //bei schrittweiser Animation wird 'false' übergeben, um zwischen Animationstypen zu unterscheiden
                displayAnimation(animation, life);
            }
            if (counter == 2) {
                bool animation = true; //true für fließende Animation
                displayAnimation(animation, life);
            }
            if (counter == 3) {
                displayMainMenu(); //zurück Button -> MainMenu
            }
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;

        if (counter == 1) {
            Set[0] = 13;
        }
        if (counter == 2) {
            Set[1] = 13;
        }
        if (counter == 3) {
            Set[2] = 12;
        }
    }
}

void CUserInterface::displayAnimation(bool a, CLife life) {
    clearScreen();
    displayTitle();
    setConsoleColor(15);
    char h;
    bool testEmpty = true;
    bool flag = false;

    if (a) {
        for (int z = 0; z < 50; z++) { //50 Generationen werden ausgegeben
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    gotoxy(47 + (i * 2), 11 + j);
                    cout << life.matrix(i, j);
                    h = life.matrix(i, j);
                    if (h == '*') {
                        testEmpty = false;
                    }
                }
            }
            if (flag) {
                break;
            }
            if (testEmpty) {
                flag = true;
            }
            testEmpty = true;
            Sleep(200);
            life.applyRules();  //Anwendung der Regeln auf die Matrix
        }
        displayEnd();
    }
    else {
        gotoxy(35, 11);
        setConsoleColor(9);
        cout << "Dr\xC3\xBC" << "cke eine beliebige Taste zum fortfahren";
        setConsoleColor(15);
        for (int z = 0; z < 30; z++) { //30 Generationen werden ausgegeben (Schutz der Tastatur)
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    gotoxy(47 + (i * 2), 13 + j);
                    cout << life.matrix(i, j);
                    h = life.matrix(i, j);
                    if (h == '*') {
                        testEmpty = false;  //Testet auf leere Matrix, sollte keine Zelle mehr leben, bleibt testEmpty auf true
                    }
                }
            }
            if (flag) {
                break;
            }
            if (testEmpty) { //Wenn Matrix leer wird ein flag gesetzt, damit nur noch einmal die leere Matrix angezeigt wird
                flag = true;
            }
            testEmpty = true;
            getch();    //warten auf Tastendruck
            life.applyRules();
        }
        displayEnd();
    }
}

void CUserInterface::displayEdit() {
    clearScreen();
    displayTitle();
    setConsoleColor(15);
    CLife life;

    int r = 0; //ausgewählte Zeile
    int c = 0; //ausgewählte Spalte
    //Anfangswert mat[0][0]

    while (true) {
        clearScreen();
        displayTitle();

        int padding = 40;  //Abstand nach links, damit Matrix mittig erscheint (gotoxy machte hier große Probleme)

        setConsoleColor(9);
        cout << "                     Mit Pfeiltasten navigieren, Leertaste zum \xC3\xA4ndern, mit Enter best\xC3\xA4tigen" << endl << endl;
        setConsoleColor(15);

        for (int i = 0; i < 10; i++) {

            for (int k = 0; k < padding; k++) { //Abstand nach links
                cout << " ";
            }

            for (int j = 0; j < 10; j++) {
                if (i == r && j == c) {
                    setConsoleColor(12);
                    cout << "[" << life.matrix(i, j) << "]"; //ausgewähltes Matrixelement wird umgeben von '[]' und in lightred angezeigt
                    setConsoleColor(15);
                }
                else {
                    cout << " " << life.matrix(i, j) << " "; //Ausgabe nicht ausgewählter Matrixelemente
                }
            }
            cout << endl;
        }

        char key = getch();
        switch (key) {  //Einhabehandler
        case 72: //Pfeiltaste nach oben
            if (r > 0) {
                r--;
            }
            break;
        case 80: //Pfeiltaste nach unten
            if (r < 9) {
                r++;
            }
            break;
        case 75: //Pfeiltaste nach links
            if (c > 0) {
                c--;
            }
            break;
        case 77: //Pfeiltaste nach rechts
            if (c < 9) {
                c++;
            }
            break;
        case ' ': { //Whitespace
            char currentValue = life.matrix(r, c);
            char newValue;
            if (currentValue == ' ') {  //Verändert Wert des Matrixelements je nachdem, ob Zelle aktuell tot oder lebendig ist
                newValue = '*';
            }
            else {
                newValue = ' ';
            }
            life.updateMatrix(r, c, newValue);
            break;
        }
        case '\r':  //Entertaste
            setConsoleColor(9);
            cout << endl;
            cout << "Konfiguration speichern? Enter zum best\xC3\xA4tigen, Leertaste f\xC3\xBCr Animation";
            char key2 = getch();
            switch (key2) {
            case '\r': { //erneut Enter gedrückt (Datei speichern)
                setConsoleColor(15);
                cout << "  >> Bitte Dateinamen eingeben: ";
                string filename;
                cin >> filename;

                try {
                    ofstream fp(filename + ".txt"); //erstellen der Datei
                    if (fp.is_open() == NULL) {
                        throw Name();
                    }
                    else {
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 10; j++) {
                                fp << life.matrix(i, j);
                            }
                            fp << endl;
                        }
                        fp.close();
                        cout << "Datei erfolgreich gespeichert";
                        Sleep(1000); //kurzes Anzeigen der Meldung, bevor fortgefahren wird
                    }
                }
                catch (CUserInterface::Name) {
                    cout << "Ung\xC3\xBCltige Eingabe. Es wird ohne speichern fortgefahren";
                    Sleep(1000); //kurzes Anzeigen der Meldung, bevor fortgefahren wird
                }

                break;
            }
            case ' ': { //bei Leertaste fortfahren ohne speichern
                break;
            }
            }
            displayAnimationType(life);
            break;
        }
    }
}

void CUserInterface::displayEnd() {
    clearScreen();
    setConsoleColor(13);

    cout << R"(
  ________  ________  ___  _______   ___               _______   ________   ________  _______      
 |\   ____\|\   __  \|\  \|\  ___ \ |\  \             |\  ___ \ |\   ___  \|\   ___ \|\  ___ \     
 \ \  \___|\ \  \|\  \ \  \ \   __/|\ \  \            \ \   __/|\ \  \\ \  \ \  \_|\ \ \   __/|    
  \ \_____  \ \   ____\ \  \ \  \_|/_\ \  \            \ \  \_|/_\ \  \\ \  \ \  \ \\ \ \  \_|/__  
   \|____|\  \ \  \___|\ \  \ \  \_|\ \ \  \____        \ \  \_|\ \ \  \\ \  \ \  \_\\ \ \  \_|\ \ 
     ____\_\  \ \__\    \ \__\ \_______\ \_______\       \ \_______\ \__\\ \__\ \_______\ \_______\
    |\_________\|__|     \|__|\|_______|\|_______|        \|_______|\|__| \|__|\|_______|\|_______|
    \|_________|                                                                                   
                                                                                                  
                                                                                                  
                                                                                                                                                                                                                                                       
)" << endl;
    setConsoleColor(15);
    int Set[] = { 7, 7, 0 };
    int counter = 1;
    char key;

    for (int i = 0;;) {

        gotoxy(4, 10);
        setConsoleColor(9);
        cout << "Das wars! Ich hoffe du hattest Spa\xC3\x9F :-)";


        gotoxy(4, 11);
        setConsoleColor(Set[0]);
        cout << "Hauptmen\xC3\xBC";

        gotoxy(4, 12);
        setConsoleColor(Set[1]);
        cout << "Beenden";

        gotoxy(4, 13);
        setConsoleColor(Set[2]);
        cout << "EasterEgg";

        key = getch();

        if (key == 72 && (counter >= 2 && counter <= 3)) {
            counter--;
        }
        if (key == 80 && (counter >= 1 && counter <= 2)) {
            counter++;
        }
        if (key == '\r') {
            if (counter == 1) {
                displayMainMenu();
            }
            if (counter == 2) {
                setConsoleColor(15);
                exit(0);
            }
            if (counter == 3) {
                easterEgg();
            }
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 0;


        if (counter == 1) {
            Set[0] = 13;
        }
        if (counter == 2) {
            Set[1] = 12;
        }
        if (counter == 3) {
            Set[2] = 10;
        }
    }
}

void CUserInterface::easterEgg() {
    clearScreen();
    setConsoleColor(9);

    cout << R"(
            .
           ":"
         ___:____     |"\/"|
       ,'        `.    \  /
       |  O        \___/  |
     ~^~^~^~^~^~^~^~^~^~^~^~^~

  _____ ____  _____ _____  __        _____ _     _  __   __
 |  ___|  _ \| ____| ____| \ \      / /_ _| |   | | \ \ / /
 | |_  | |_) |  _| |  _|    \ \ /\ / / | || |   | |  \ V / 
 |  _| |  _ <| |___| |___    \ V  V /  | || |___| |___| |  
 |_|   |_| \_\_____|_____|    \_/\_/  |___|_____|_____|_|  
                                                           

)" << endl;
    setConsoleColor(15);
    Sleep(2000);
    displayMainMenu();

}

void CUserInterface::clearScreen() {
    system("cls"); //räumt das Terminal auf
}

void CUserInterface::setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);   //ändert die Farbe des angezeigten Textes
}

void CUserInterface::gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); //bewegt den Cursor an bestimmte Position
}

CUserInterface::~CUserInterface() {

}
