/*******************************************************
* Nom: programa4
* Que fa: Donat un punt (x,y) d'una graella buida{14,14}
          es dibuixa quadrats que envolten el punt marcat
          amb una separació de una casella. El nombre de
          quadrats ve marcat per el natural "k"
* Autor: Miquel Giné Fàbrega
********************************************************/
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <conio.h>

using namespace std;
const int VecX = 14;
const int VecY = 14;
typedef bool Vec [VecX][VecY];

void crearFigura(Vec &v, int x, int y, int k){
    /**
    * Què fa: Dibuixa la taula de tal manera que donat un punt de la taula crida
              recursivament per dibuixar les seves quatre cantonades. Sempre i quan
              aquesta es trobi dins del rang "k". Format de tal manera k quadrats amb
              un espai entre punt, i en cada quadrat un increment de 4 punts.
    * Entrades: Vector on es guarda els valors, punt x i y, numero de quadrats k
    * Sortides: #
    */
    if (k>=0) {
        if (x>0 && x<VecX && y>0 && y<VecY){

            v[x][y] = true;

            crearFigura(v, x-1, y-1, k-1);
            crearFigura(v, x+1, y-1, k-1);
            crearFigura(v, x-1, y+1, k-1);
            crearFigura(v, x+1, y+1, k-1);
        }
    }
}

void InicialitzaTaula(Vec &v){
    /**
    * Què fa: Introdueix en la taula un valor inicial per poder treballar en ella,
              en aquest cas al ser una taula booleana, la inicialitzo amb 0.
    * Entrades: Vector amb les dades
    * Sortides: #
    */
    for (int i=0; i<VecX; i++){
        for(int j=0; j<VecY; j++){
            v[i][j] = false;
        }
    }
}

void Visualitza(Vec v){
    /**
    * Què fa: Mostra el contingut de la taula tot formant les caselles
              per poder visualitzar millor el forma de la mateixa.
    * Entrades: el Vector que conté els valors
    * Sortides: #
    */
    for (int i=0; i<VecY; i++){
        for (int ii=0; ii<VecX; ii++){
            cout << "+---";
        }
        cout << "+" << endl;
        cout << "| ";
        for(int j=0; j<VecX; j++){
            if (v[i][j] == false){
                cout << " " << " | ";
            }
            else {
                cout << "T" << " | ";
            }
        }
        cout << endl;
    }
    for (int ii=0; ii<VecX; ii++){
        cout << "+---";
    }
    cout << "+" << endl;
}

int main() {
    /**
    * Què fa: Demana introduïr 2 punts cardinals de la taula per començar a dibuixar
              la figura. Així com el nombre de quadrats a formar.
              Crida al modul de crear la figura i el visualitza.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    Vec v;
    int a,b,k;
    InicialitzaTaula(v);

    cout << "Introdueix el punt inicial [x]: ";
    cin >> a;
    cout << "Introdueix el punt inicial [y]: ";
    cin >> b;
    cout << "Introdueix el nombre de quadrats: ";
    cin >> k;

    crearFigura(v, a, b, k);
    Visualitza(v);

    return 0;
}
