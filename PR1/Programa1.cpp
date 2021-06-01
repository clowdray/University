/*******************************************************
* Nom: programa1
* Que fa: Resoluci� de la serie de Fibonacci utilitzant
          recursivitat i iterativitat
* Autor: Miquel Gin� F�brega
********************************************************/
#include <stdlib.h>
#include <ctime>
//-----llibreries per el random
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <conio.h>

using namespace std;
const int vecSize = 10;
typedef int Vec [vecSize];

long fibonacciRec(int n) {
    /**
    * Qu� fa: Donat un enter "n" calcula el valor de fibonacci asociat a aquell terme
              mitjan�ant la recursivitat comen�ant des de el valor m�s gran fins al m�s
              petit.
    * Entrades: valor inicialitzat en la crida, enter "n"
    * Sortides: valor de fibonacci associat al terme "n"
    */
    if (n==0 || n==1){
        return n;
    }
    else {
        return fibonacciRec(n-1)+fibonacciRec(n-2);
    }
}

long fibonacciIte(int n) {
    /**
    * Qu� fa: Donat un enter "n" calcula el valor de fibonacci asociat a aquell terme
              mitjan�ant la iterativitat comen�ant des de "0" fins a n-1.
    * Entrades: valor inicialitzat en la crida, enter "n"
    * Sortides: valor de fibonacci associat al terme "n"
    */
    long n1 = 0;
    long n2 = 1;
    long aux;
    if (n==0 || n==1) {
        return n;
    }
    else {
        for(int i = 0; i<n-1; i++){
            aux = n1+n2;
            n1 = n2;
            n2 = aux;
        }
        return aux;
    }
}

int product(Vec v, int index, int b) {
    /**
    * Qu� fa: Donat un vector de elements pre inicialitzat, calcula el producte resultant
              de multiplicar els valors superiors a "b" que es trobin dins del vector.
    * Entrades: Vector inicialitzat "v", posici� en el vector "index", n�mero de tall "b"
    * Sortides: resultat del producte
    */
    int temp = v[index];

    if (index == 0){
        return temp;
    }
    else {
        if (temp > b) {
            int result = temp * product(v, index-1, b);
            return result;
        }
        else {
            return product(v, index-1, b);
        }
    }
}

void menu1(){
    /**
    * Qu� fa: Implementaci� del apartat 1 del men�, demana introdu�r valor de "n", crida de
              funci�, i mostra el resultat d'aquesta per pantalla.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    int n;
    cout << "Introdueix el terme final de fibonacci: ";
    cin >> n;
    long result = fibonacciRec(n);
    cout << "Fibonacci de "<<n<<" es: " << result << endl;
}

void menu2(){
    /**
    * Qu� fa: Implementaci� del apartat 2 del men�, demana introdu�r valor de "n", crida de
              funci�, i mostra el resultat d'aquesta per pantalla.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    int n;
    cout << "Introdueix el terme final de fibonacci: ";
    cin >> n;
    long result = fibonacciIte(n);
    cout << "Fibonacci de "<<n<<" es: " << result << endl;
}

void menu3(){
    /**
    * Qu� fa: Implementaci� del apartat 3 del men�, generaci� de numeros aleatoris i els
              introdueix en un vector, demana introdu�r valor de "b", crida de la funci�
              i mostra el resultat d'aquesta per pantalla.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    Vec v;
    int n;
    srand(time(NULL));
    for (int i=0;i<vecSize;i++){
        v[i] = rand() % vecSize + 1;
    }
    for (int i=0; i<vecSize ; i++) {
        cout << v[i] << " ";
    }

    cout << endl << "Introdueix el valor de tall: ";
    cin >> n;

    int result = product(v, vecSize-1, n);
    cout << "Producte de nombres superiors a "<<n<<" en el vector: " << result << endl;
}

int main() {
    /**
    * Qu� fa: Implementaci� del programa principal, mostra el men� d'opcions i crida a
              les funcions relacionades amb les opcions del men�. Es repeteix la execuci�
              i no acaba fins a introdu�r la opci� 4.
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
        cout << "1- Fibonacci (RECURSIU)" << endl;
        cout << "2- Fibonacci (ITERATIU)" << endl;
        cout << "3- Multiplicaci� vector (RECURSIU)" << endl;
        cout << "4- Sortir" << endl;
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
                menu3();
            break;
            case 4:
                sortir = true;
            break;
            default:
            cout << "Opci� no permitida";
        }
        cout << endl;

    } while (!sortir);
    return 0;
}
