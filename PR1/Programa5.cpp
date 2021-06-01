/*******************************************************
* Nom: programa5
* Que fa: Donat dos cadenes de 6 posicions trobar les
          consonants repetides entre les cadenes, tenint
          en compte que està ordenat alfabeticament i que
          no hi han lletres repetides en la mateixa
          cadena.
* Autor: Miquel Giné Fàbrega
********************************************************/
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include<windows.h>
#endif // _WIN32
#include <stdlib.h>

using namespace std;

void contarConsonantsMillorat(char c1[], char c2[], string &c3, int posC1, int posC2){
    /**
    * Què fa: El funcionament es exactament el mateix que el del mòdul "contarConsonants" però
              s'ha ajuntat dues condicions d'if, ja que teniem 2 crides exactament iguals, que
              ara ja només es crida una sola vegada. També la concatenació es fa dins la mateixa crida, i no fora.
    * Entrades: Vector de caracters 1 i 2, cadena resultant, posició per recorre els 2 vectors.
    * Sortides: #
    */
    if (posC1 < 6){
        if((c1[posC1] != 'a' || c1[posC1] != 'e' || c1[posC1] != 'i' || c1[posC1] != 'o' || c1[posC1] != 'u') & (posC2 < 6)){
            if (c1[posC1] == c2[posC2]) {
                contarConsonantsMillorat(c1, c2, c3 += c1[posC1], posC1+1, posC2+1);
            }
            else {
                contarConsonantsMillorat(c1, c2, c3, posC1, posC2+1);
            }
        }
        else {
            contarConsonantsMillorat(c1, c2, c3, posC1+1, 0);
        }
    }
}

void contarConsonants(char c1[], char c2[], string &c3, int posC1, int posC2){
    /**
    * Què fa: Primerament mira si ja hem acabat de llegir la primera cadena, al haber acabat
              ja no es crida més recursivament, i per tant acaba. Al ser inferior, mira si el
              caracter es una vocal i seguidament la llargada de la segona cadena. Comprova si
              els caracters son iguals, i de ser iguals el guarda en un string concatenant el
              caracter.
              De no ser igual, salta a mirar el seguent caracter de la 2a cadena.
              Si arribem a la segona cadena i no es igual, saltem al seguent caracter de la
              primera cadena.
              El resultat l'arrossega en una varible que la passem per parametre.
    * Entrades: Vector de caracters 1 i 2, cadena resultant, posició per recorre els 2 vectors.
    * Sortides: #
    */
    if (posC1 < 6){
        if(c1[posC1] != 'a' || c1[posC1] != 'e' || c1[posC1] != 'i' || c1[posC1] != 'o' || c1[posC1] != 'u' ){
            if(posC2 < 6) {
                if (c1[posC1] == c2[posC2]){
                    c3 += c1[posC1];
                    contarConsonants(c1, c2, c3, posC1+1, posC2+1);
                }
                else {
                    contarConsonants(c1, c2, c3, posC1, posC2+1);
                }
            }
            else {
                contarConsonants(c1, c2, c3, posC1+1, 0);
            }
        }
        else {
            contarConsonants(c1, c2, c3, posC1+1, 0);
        }
    }
}

int main() {
    /**
    * Què fa: Demana dos cadenes de un maxim de 6 caracters, i els tracta, cridant a la funció
              recursiva "contarConsonants". Mostra la cadena resultant amb les consonants
              repetides. Demana si vols continuar o altrament tornar a fer el mateix.
    * Entrades: #
    * Sortides: #
    */
    #ifdef _WIN32
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    #endif // _WIN32
    bool sortir = false;
    char out;
    do {
        char c1[20]; // estan declarats com a 20 ja que el buffer d'entrada té algún bug on capta /000 i em modifica la cadena
        char c2[20]; // d'aquesta manera recull només les dades entrades i s'adapta a la llargada de la cadena entrada
        string c3 = "";

        cout << "Cadena 1: ";
        cin >> c1;
        cout << "Cadena 2: ";
        cin >> c2;

        contarConsonantsMillorat(c1, c2, c3, 0, 0);
        //contarConsonants(c1, c2, c3, 0, 0);
        cout << "Cadena resultant: " << c3 << endl;
        cout << "Vols continuar [S/N]: ";
        cin >> out;
        if (out == 'N' || out == 'n'){
            sortir = true;
        }
        else {
            system("cls");
        }
    } while(!sortir);

    return 0;
}
