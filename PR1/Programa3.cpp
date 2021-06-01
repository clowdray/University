/*******************************************************
* Nom: programa3
* Que fa: Calcular el nombre combinatori amb el m�tode
          de pascal i de forma factorial.
* Autor: Miquel Gin� F�brega
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
    * Qu� fa: A partir de la formula [n-1,m-1]+[n-1,m] i amb la conseguent afirmaci�
              [n,n] = 1 i [n,0] = 1 procedim a fer la funci� recursiva.
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
    * Qu� fa: Calcul del factorial de "n" on comencem de n fins a 0
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
    * Qu� fa: A partir de la formula [ n! / (m! * ( n-m )! ) ] calculem els factorials
              i resolem la forumula. ## Es pot simplificar el calcul per a nombres m�s
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
    * Qu� fa: Implementaci� del apartat 1 del men�, demana "n" i "m", crida a la funci�
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
    cout << "El nombre combinatori de [" << n << "," << m <<"] �s: " << result << endl;
}

void menu2(){
    /**
    * Qu� fa: Implementaci� del apartat 2 del men�, demana "n" i "m", crida a la funci�
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
    cout << "El nombre combinatori de [" << n << "," << m <<"] �s: " << result << endl;
}

int main() {
    /**
    * Qu� fa: Implementaci� del programa principal, mostra el men� d'opcions i crida a
              les funcions relacionades amb les opcions del men�. Es repeteix la execuci�
              i no acaba fins a introdu�r la opci� 3.
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
        cout << "Trieu una opci�: ";
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
            cout << "Opci� no permitida";
        }
        cout << endl;

    } while (!sortir);
    return 0;
}
