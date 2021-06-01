/*******************************************************
* Nom: mario_b
* Que fa: Cada cop que s'executa genera una matriu aletoria
          que es representa amb una matriu d'ajacència
* Autor: Miquel Giné Fàbrega
********************************************************/
#include <stdlib.h>
#include <ctime>
//-----llibreries per el random
#include <iostream>
#include <sstream>
#include <conio.h>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32

using namespace std;

//--------STRUCT-DECLARATION---------//
const int joc = 8;

struct illa {
    int numIlla;
    int numEnemics;
};

struct escenari {
    illa illes[joc];
    bool matriu[joc][joc];
};

struct Stack {
    int top;
    int p[joc*joc];
};

//--------METHODS-DECLARATION--------//
void init(escenari &e);
void newGraph(escenari &e);
void testValues1(escenari &e);
void bridgeGenerator(escenari &e);
void showGraph(escenari e);
void bunchOfPaths(escenari e, int ini, int fin, bool &trobat, Stack &s, bool &solucio);
bool existIsland(escenari e, int illa);
void newStack(Stack &s);
void afegir(Stack &s, int obj);
int treure(Stack &s);
int top(Stack s);
bool in(Stack s, int obj);
string flush(Stack s);
int enemics(Stack s, escenari e);
void pause();

//-------METHODS-IMPLEMENTATION------//
void init(escenari &e) {
    /**
    * Què fa: Inicializem el vector illes a 0 per evitar execucions sense dades
    * Entrades: varibale e de tipus escenari, completament buida
    * Sortides: inicialitzem la primera posició del num de la illa
    */
    for (int i=0;i<joc;i++) {
        e.illes[i].numIlla = 0;
    }
}

void testValues1(escenari &e) {
    /**
    * Què fa: generació hardcodejada per el test 1
    * Entrades: varibale e de tipus escenari
    * Sortides: #
    */
    e.illes[0].numIlla = 11;
    e.illes[1].numIlla = 12;
    e.illes[2].numIlla = 23;
    e.illes[3].numIlla = 24;
    e.illes[4].numIlla = 35;
    e.illes[5].numIlla = 36;
    e.illes[6].numIlla = 47;
    e.illes[7].numIlla = 60;

    e.illes[0].numEnemics = 1;
    e.illes[1].numEnemics = 4;
    e.illes[2].numEnemics = 5;
    e.illes[3].numEnemics = 6;
    e.illes[4].numEnemics = 4;
    e.illes[5].numEnemics = 6;
    e.illes[6].numEnemics = 8;
    e.illes[7].numEnemics = 9;

    bridgeGenerator(e);
}

void bridgeGenerator(escenari &e) {
    /**
    * Què fa: Genera els ponts del escenari seleccionat
    * Entrades: varibale e de tipus escenari
    * Sortides: #
    */
    int num;
    for (int i=0;i<joc;i++) {
        for (int j=0; j < joc; j++) {
            num = e.illes[i].numIlla + e.illes[j].numIlla;
            if (num %3 == 0 && i != j) {
                e.matriu[i][j] = 1;
            }
            else {
                e.matriu[i][j] = 0;
            }
        }
    }
}

void showGraph(escenari e) {
    /**
    * Què fa: Es mostren les illes amb el seu numero més el seu numero d'enemics, seguidament
              es mostra la matriu d'adjacecia amb els seus ponts
    * Entrades: varibale e de tipus escenari
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    if (e.illes[0].numIlla != 0){
        cout << "A continuació es mostra el número de l'illa i el numero d'enemics: \n" << endl;
        for (int i=0; i<joc; i++) {
            cout << "Illa: " << e.illes[i].numIlla << "\t Enemics: " << e.illes[i].numEnemics << endl;
        }
        cout << endl << "El graf que formen la unió de les illes representat en una matriu d'adjacència: " << endl;
        cout << "\t";
        for (int i=0; i<joc; i++) {
            cout << e.illes[i].numIlla << "  ";
        }
        cout << endl;
        for (int i=0; i<joc; i++) {
            cout << endl << e.illes[i].numIlla << "\t ";
            for (int j=0; j<joc; j++) {
                cout << e.matriu[i][j] << "   ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Graf no generat!!" << endl;
    }
}

void bunchOfPaths(escenari e, int ini, int fin, bool &trobat, Stack &s, bool &solucio) {
    /**
    * Què fa: Escriu tots els camins possibles i visualiza els camins amb el nombre d'enemics
              que s'ha trobat.
    * Entrades: el escenari actual, la illa actual, la illa final, saber si has
                arribat al final, pila on es guarda les illes ja visitades.
    * Sortides: #
    */

    Stack d;
    newStack(d);
    int trash;

    if (ini == fin) {
        trobat = true;
    }
    else {
        trobat = false;
        afegir(s, ini);
        int i=0;

        // En un bucle for de moltes iteracions el recorreria tot i no es necesari
        while (i<joc && e.illes[i].numIlla != ini){
            i++;
        }
        int k = i;

        i = 0;
        while (i<joc && !trobat){
            if (e.matriu[k][i] == 1) {
                if (e.illes[i].numIlla == fin){
                    trobat = true;
                    if (trobat){
                        solucio = true;
                    }
                    cout << endl << flush(s) << fin << endl;
                    cout << "En el trajecte el Mario s'ha trobat " << enemics(s, e) << " enemics" << endl;

                    trobat = false;
                }
                else if ( !in(s,e.illes[i].numIlla) ){
                    afegir(d, e.illes[i].numIlla);
                }
            }
            i++;
        }
        while (d.top > -1 && !trobat) {
            k = treure(d);
            bunchOfPaths(e, k, fin, trobat, s, solucio);
        }
        if (!trobat) {
            trash = treure(s);
            k = trash;
        }
    }
}

bool existIsland(escenari e, int illa) {
    /**
    * Què fa: Mira si existeix la illa introduida
    * Entrades: Pila a tractar, illa a buscar
    * Sortides: true en el cas de que existeixi false en cas contrari
    */
    bool exist = false;
    int i=0;
    while (!exist && i<joc){
        if (e.illes[i].numIlla == illa)
            exist = true;
        i++;
    }
    return exist;
}

void newStack(Stack &s) {
    /**
    * Què fa: Inicialització de la nova pila
    * Entrades: Pila a tractar
    * Sortides: #
    */
    s.top = -1;
}

void afegir(Stack &s, int obj) {
    /**
    * Què fa: afegeix un element a la pila
    * Entrades: La pila a tractar, el objecte a inserir
    * Sortides: El element del cap
    */
    s.top = s.top+1;
    s.p[s.top] = obj;
}

int treure(Stack &s) {
    /**
    * Què fa: Treu el ultim element de la pila (el cap) i el retorna
    * Entrades: La pila a tractar
    * Sortides: El element del cap
    */
    int out = s.p[s.top];
    s.top = s.top-1;
    return out;
}

int top(Stack s) {
    /**
    * Què fa: Retorna el element que hi ha al cap de la pila
    * Entrades: La pila a tractar
    * Sortides: El element del cap
    */
    return s.p[s.top];
}

bool in(Stack s, int obj) {
    /**
    * Què fa: busca si existeix el element en la pila
    * Entrades: La pila a tractar, el objecte a buscar
    * Sortides: true en el cas de existir, fals altrament
    */
    int i = 0;
    bool trobat = false;
    while (i<s.top+1 && !trobat) {
        if (s.p[i] == obj) {
            trobat = true;
        }
        i++;
    }
    return trobat;
}

string flush(Stack s) {
    /**
    * Què fa: Treu totes les dades del stack en ordre d'entrada
    * Entrades: El estack a tractar
    * Sortides: #
    */
    int i = 0;
    string output = "";
    while (i<s.top+1) {
        ostringstream foo;
        foo << s.p[i];
        output += foo.str() + " ";
        i++;
    }
    return output;
}

int enemics(Stack s, escenari e) {
    /**
    * Què fa: Treu totes les dades del stack en ordre d'entrada
    * Entrades: El estack a tractar
    * Sortides: #
    */
    int i = 0;
    int contador=-1;
    if (s.top >= 0) {
        contador=0;
    }
    while (i<s.top+1) {
        bool ok = false;
        int j = 0;
        while (!ok){
            if (s.p[i] == e.illes[j].numIlla){
                contador += e.illes[j].numEnemics;
                ok = true;
            }
            else {
                j++;
            }
        }
        i++;
    }
    int output = contador;
    return output;
}

void pause() {
    /**
    * Què fa: Interrupció en el sistema a la espera de premer una tecla
    * Entrades: #
    * Sortides: #
    */
    system("pause");
}

//-------------MAIN-CODE-------------//
int main()
{
    /**
    * Què fa: Implementació del programa principal, mostra el menú d'opcions i crida a
              les funcions relacionades amb les opcions del menú. Es repeteix la execució
              i no acaba fins a introduïr la opció 3.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    int opcio;
    escenari e;
    bool trobat = false;
    bool solucio = false;
    int ini;
    int fin;

    Stack a;
    newStack(a);
    afegir(a,10); //nombre de enemics superior al maxim
    Stack s;
    newStack(s);

    init(e);

    bool sortir = false;
    do{
        cout << "[1] Generar escenari nou" << endl;
        cout << "[2] Buscar un camí" << endl;
        cout << "[3] Finalitzar el programa" << endl;
        cin >> opcio;

        cout << endl;
        switch(opcio){
            case 1:
                testValues1(e);
				showGraph(e);
            break;
            case 2:
				if (e.illes[0].numIlla < 11 || e.illes[0].numIlla > 99){
					cout << "No s'ha generat cap escenari" << endl;
				}
				else {
					ini = 11;
					fin = 24;
					bunchOfPaths(e, ini, fin, trobat, s, solucio);
					if (!solucio) {
						cout << endl << "No existeix camí possible" << endl;
						cout << "En el trajecte el Mario s'ha trobat 0 enemics" << endl;
					}
				}
            break;
            case 3:
                cout << "Bye Bye !!" << endl;
                sortir = true;
            break;
            default:
                cout << "Opció no permitida";
        }
        cout << endl;
        if (!sortir) {
            pause();
        }

    } while (!sortir);
    return 0;
}
