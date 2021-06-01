/*******************************************************
* Nom: programa2
* Que fa: Donar el valor resultant del sumatori de
          potencies de 0 fins al n�mero desitjat.
* Autor: Miquel Gin� F�brega
********************************************************/
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <conio.h>
#include <math.h>

using namespace std;

int recPotencia(int n){
    /**
    * Qu� fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma recursiva
              en el cas de entrar el valor 0 retorna 0. Tamb� mostra el procediment del
              sumatori per pantalla.
    * Entrades: valor inicialitzat en la crida, enter "n"
    * Sortides: resultat del sumatori resultant de les potencies.
    */
    int result;
    if (n>0){
        if (n==1){
            cout << pow(n, 2);
        }
        else
            cout << pow(n, 2) << " + ";
        return result = recPotencia(n-1)+pow(n, 2);
    }
    else {
        return 0;
    }
}

int itePotencia(int n){
    /**
    * Qu� fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma iterativa
              en el cas de entrar el valor 0 retorna 0. Tamb� mostra el procediment del
              sumatori per pantalla.
    * Entrades: valor inicialitzat en la crida, enter "n"
    * Sortides: resultat del sumatori resultant de les potencies.
    */
    int result = 0;
    while (n>0){
        if (n==1){
            cout << pow(n, 2);
        }
        else
            cout << pow(n, 2) << " + ";
        result += pow(n, 2);
        n--;
    }
    return result;
}

int immPotencia(int n, int result){
    /**
    * Qu� fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma recursiva
              en el cas de entrar el valor 0 retorna 0. Tamb� mostra el procediment del
              sumatori per pantalla. En aquest cas el resultat es guarda com a parametre
              i es pasa el resultat de forma recursiva.
    * Entrades: valor inicialitzat en la crida, enter "n", result (valor inicial 0)
    * Sortides: resultat del sumatori resultant de les potencies.
    */
    if (n>0){
        if (n==1){
            cout << pow(n, 2);
        }
        else
            cout << pow(n, 2) << " + ";
        return immPotencia(n-1, result + pow(n, 2));
    }
    else {
        return result;
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
    cout << "Introdueix el nombre delements a sumar: ";
    cin >> n;

    int result;
    result = recPotencia(n);
    cout << " = " << result << endl;
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
    cout << "Introdueix el nombre delements a sumar: ";
    cin >> n;

    int result;
    result = itePotencia(n);
    cout << " = " << result << endl;
}

void menu3(){
    /**
    * Qu� fa: Implementaci� del apartat 3 del men�, demana introdu�r valor de "n", crida de
              funci�, i mostra el resultat d'aquesta per pantalla.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32

    int n;
    cout << "Introdueix el nombre delements a sumar: ";
    cin >> n;

    int result = 0;
    result = immPotencia(n, result);
    cout << " = " << result << endl;
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
        cout << "1- Potencia (RECURSIU)" << endl;
        cout << "2- Potencia (ITERATIU)" << endl;
        cout << "3- PotenciaImmersiva (RECURSIU)" << endl;
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
