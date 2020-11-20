#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dziekanat.h"
#include "studenci.h"

int main(int argc, char** argv) {
    student dane[100];
    int ile;
    ile = wczytaj(dane, argv[1]);

    if(strcmp(argv[2], "wypisz") == 0){
        wypisz(dane, ile);
    }
    if(strcmp(argv[2], "najlepszy_student") == 0){ 
        najlepszy_student(dane, ile);
    }
    if(strcmp(argv[2], "najlepszy_przedmiot") == 0){ 
       najlepszy_przedmiot(dane, ile);
    }
    if(strcmp(argv[2], "najgorszy_przedmiot") == 0){ 
        najgorszy_przedmiot(dane, ile);
    }

    return 0;
}