#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studenci.h"

void najlepszy_student(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    float srednie[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++) {
        sumy_wazonych_ocen[i] = 0;
        sumy_ects[i] = 0;
    }

    for (i = 0; i < ile_rekordow; i++) {
        pozycja = znajdz(dane[i].nr_albumu, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }

    for (i = 0; i < ile_studentow; i++)
        printf("Student [%d]: %s - %f:%d - %f \n", i + 1, nr_albumow[i],
            sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]);

    for (i = 0; i < ile_studentow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d]: %s - %f \n",
        najlepsza_pozycja + 1, nr_albumow[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

}

void najlepszy_przedmiot(student dane[100], int ile_rekordow) {
    
    char kod_przed[100][10];
    char nazwa_przed[100][10];
    int ile_przed, i, pozycja, ile_dodawan[100] = { 0 }, najlepsza_pozycja;
    float srednia[100] = { 0 }, najlepsza = 0.0f;

    ile_przed = znajdz_przed(kod_przed, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++) {
        pozycja = znajdz(dane[i].kod_przed, kod_przed, ile_przed);
        //printf("pozycja to %d, dla %d fora\n", pozycja, i+1);
        strcpy(nazwa_przed[pozycja], dane[i].nazwa_przed);
        ile_dodawan[pozycja]++;
        srednia[pozycja] += dane[i].ocena;
    }

    for (i = 0; i < ile_przed; i++) {
        srednia[i] = srednia[i] / ile_dodawan[i];
       // printf("%f\n", srednia[i]);
    }

    for (i = 0; i < ile_przed; i++) {
        if (najlepsza < srednia[i]) {
            najlepsza = srednia[i];
            najlepsza_pozycja = i;
        }
        //printf("najlepsza: %f, dla i: %d\n", najlepsza, i);
        //printf("najlepsza_pozycja: %d, dla i: %d\n", najlepsza_pozycja, i);
    }

    printf("Nalepsza srednia: %s - %s: %.1f\n", kod_przed[najlepsza_pozycja], nazwa_przed[najlepsza_pozycja], srednia[najlepsza_pozycja]);   
}

void najgorszy_przedmiot(student dane[100], int ile_rekordow){

    char kod_przed[100][10];
    char nazwa_przed[100][10];
    int ile_przed, i, pozycja, ile_dodawan[100] = { 0 }, najgorsza_pozycja;
    float srednia[100] = { 0 }, najgorsza = 6.0f;

 ile_przed = znajdz_przed(kod_przed, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++) {
        pozycja = znajdz(dane[i].kod_przed, kod_przed, ile_przed);
        //printf("pozycja to %d, dla %d fora\n", pozycja, i+1);
        strcpy(nazwa_przed[pozycja], dane[i].nazwa_przed);
        ile_dodawan[pozycja]++;
        srednia[pozycja] += dane[i].ocena;
    }

    for (i = 0; i < ile_przed; i++) {
        srednia[i] = srednia[i] / ile_dodawan[i];
       // printf("%f\n", srednia[i]);
    }

 for (i = 0; i < ile_przed; i++) {
        if (najgorsza > srednia[i]) {
            najgorsza = srednia[i];
            najgorsza_pozycja = i;
        }
        //printf("najgorsza: %f, dla i: %d\n", najgorsza, i);
        //printf("najgorsza_pozycja: %d, dla i: %d\n", najgorsza_pozycja, i);
    }

    printf("Najgorsza srednia: %s - %s: %.1f\n", kod_przed[najgorsza_pozycja], nazwa_przed[najgorsza_pozycja], srednia[najgorsza_pozycja]);
}
