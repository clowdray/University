/*******************************************************
* Nom: programa2
* Que fa: Donar el valor resultant del sumatori de
          potencies de 0 fins al número desitjat.
* Autor: Miquel Giné Fàbrega
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
    * Què fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma recursiva
              en el cas de entrar el valor 0 retorna 0. També mostra el procediment del
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
    * Què fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma iterativa
              en el cas de entrar el valor 0 retorna 0. També mostra el procediment del
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
    * Què fa: Donat un valor "n" calcula el sumatori de 0 fins a n, de forma recursiva
              en el cas de entrar el valor 0 retorna 0. També mostra el procediment del
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
    * Què fa: Implementació del apartat 1 del menú, demana introduïr valor de "n", crida de
              funció, i mostra el resultat d'aquesta per pantalla.
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
    * Què fa: Implementació del apartat 2 del menú, demana introduïr valor de "n", crida de
              funció, i mostra el resultat d'aquesta per pantalla.
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
    * Què fa: Implementació del apartat 3 del menú, demana introduïr valor de "n", crida de
              funció, i mostra el resultat d'aquesta per pantalla.
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
    * Què fa: Implementació del programa principal, mostra el menú d'opcions i crida a
              les funcions relacionades amb les opcions del menú. Es repeteix la execució
              i no acaba fins a introduïr la opció 4.
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
                menu3();
            break;
            case 4:
                sortir = true;
            break;
            default:
            cout << "Opció no permitida";
        }
        cout << endl;

    } while (!sortir);
    return 0;
}
