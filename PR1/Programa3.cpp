/*******************************************************
* Nom: programa3
* Que fa: Calcular el nombre combinatori amb el mètode
          de pascal i de forma factorial.
* Autor: Miquel Giné Fàbrega
********************************************************/
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <conio.h>

using namespace std;

int cmbPascal(int n, int m) {
    /**
    * Què fa: A partir de la formula [n-1,m-1]+[n-1,m] i amb la conseguent afirmació
              [n,n] = 1 i [n,0] = 1 procedim a fer la funció recursiva.
    * Entrades: valor inicialitzat en la crida, enter "n" i "m"
    * Sortides: valor de coeficient binomial associat al terme [n,m]
    */
    if (n==m || m==0){
        return 1;
    }
    else {
        return cmbPascal(n-1,m-1)+cmbPascal(n-1,m);
    }
}

int factorial(int n){
    /**
    * Què fa: Calcul del factorial de "n" on comencem de n fins a 0
    * Entrades: valor inicialitzat en la crida, enter "n"
    * Sortides: valor de factorial de "n"
    */
    if(n < 0){
        return 0;
    }
    else if(n > 1) {
        return n*factorial(n-1);
    }
    else {
        return 1;
    }
}

int cmbFactorial(int n, int m){
    /**
    * Què fa: A partir de la formula [ n! / (m! * ( n-m )! ) ] calculem els factorials
              i resolem la forumula. ## Es pot simplificar el calcul per a nombres més
              grans si simplifiquem els factorials ##
    * Entrades: valor inicialitzat en la crida, enter "n" i "m"
    * Sortides: valor de coeficient binomial associat al terme [n,m]
    */
    int nn = factorial(n);
    int mm = factorial(m);
    int nm = factorial(n-m);
    return (nn/(mm*nm));
}

void menu1(){
    /**
    * Què fa: Implementació del apartat 1 del menú, demana "n" i "m", crida a la funció
              on calcula el coeficient binomial a partir de T. Pascal i mostra el
              resultat.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    cout << "/ n \\" << endl;
    cout << "|   |" << endl;
    cout << "\\ m /" << endl;

    int n, m;
    cout << "Introdueix valor de n: ";
    cin >> n;
    cout << "Introdueix valor de m: ";
    cin >> m;

    int result = cmbPascal(n,m);
    cout << "El nombre combinatori de [" << n << "," << m <<"] és: " << result << endl;
}

void menu2(){
    /**
    * Què fa: Implementació del apartat 2 del menú, demana "n" i "m", crida a la funció
              on calcula el coeficient binomial a partir de factorialitzar i mostra el
              resultat.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    cout << "/ n \\" << endl;
    cout << "|   |" << endl;
    cout << "\\ m /" << endl;

    int n, m;
    cout << "Introdueix valor de n: ";
    cin >> n;
    cout << "Introdueix valor de m: ";
    cin >> m;

    int result = cmbFactorial(n,m);
    cout << "El nombre combinatori de [" << n << "," << m <<"] és: " << result << endl;
}

int main() {
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
    bool sortir = false;
    do{
        cout << "1- CombinatoriPascal (RECURSIU)" << endl;
        cout << "2- CombinatoriFactorial (RECURSIU)" << endl;
        cout << "3- Sortir" << endl;
        cout << "Trieu una opció: ";
        cin >> opcio;

        cout << endl;
        switch(opcio){
            case 1:
                menu1();
            break;
            case 2:
                menu2();
            break;
            case 3:
                sortir = true;
            break;
            default:
            cout << "Opció no permitida";
        }
        cout << endl;

    } while (!sortir);
    return 0;
}
