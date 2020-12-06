#include "baza.h"

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;

    Student *last_student = NULL;
    Student *glowa = NULL;

    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

Przedmiot * wczytaj_przedmioty(FILE *fin){
    char bufor[255];
    int n, i;
    char *s;

    Przedmiot *last_przedmiot = NULL;
    Przedmiot *glowa = NULL;

    fgets(bufor, 254, fin); 
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;

        if (last_przedmiot == NULL)
            glowa = przed;
        else
            last_przedmiot->nast = przed;
        last_przedmiot = przed;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przed->kod_przed = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->kod_przed, s);

        s = strtok(NULL, ";");
        przed->nazwa_przed = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->nazwa_przed, s);

        s = strtok(NULL, "\n");
        przed->sem = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->sem, s);
    }

    return glowa;
}

Ocena * wczytaj_oceny(FILE *fin){
    char bufor[255];
    int n, i;
    char *s;

    Ocena *last_ocena = NULL;
    Ocena *glowa = NULL;

    fgets(bufor, 254, fin); 
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *oc = (Ocena*) malloc(sizeof(Ocena));
        oc->nast = NULL;

        if (last_ocena == NULL)
            glowa = oc;
        else
            last_ocena->nast = oc;
        last_ocena = oc;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        oc->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->nr_albumu, s);

        s = strtok(NULL, ";");
        oc->kod_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->kod_przedmiotu, s);

        s = strtok(NULL, ";");
        oc->ocena = atof(s);

        s = strtok(NULL, "\n");
        oc->komentarz = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->komentarz, s);
    }

    return glowa;
}

SBaza * wczytaj_baze(char *nazwa_pliku) {
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza) );
    baza->lista_studentow = wczytaj_studentow(fin);
    baza->lista_przedmiotow = wczytaj_przedmioty(fin);
    baza->lista_ocen = wczytaj_oceny(fin);

    fclose(fin);
    return baza;
}

SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza) {

    FILE *fin = fopen(nazwa_pliku, "w+");
  	Student * stud = baza->lista_studentow;
    Przedmiot *przed = baza->lista_przedmiotow;
    Ocena * oc = baza->lista_ocen;
	int i;

    fprintf(fin, "%d\n", ile_studentow(baza));
    for(i=0; i<ile_studentow(baza); i++){
        fprintf(fin, "%s;%s;%s;%s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
    
    fprintf(fin, "%d\n", ile_przedmiotow(baza));   
  	for(i=0; i<ile_przedmiotow(baza); i++){
        fprintf(fin, "%s;%s;%s\n", przed->kod_przed, przed->nazwa_przed, przed->sem);
        przed = przed ->nast;
    }

    fprintf(fin, "%d\n", ile_ocen(baza));  	
  	for(i=0; i<ile_ocen(baza); i++){
        fprintf(fin, "%s;%s;%1.1f;%s\n", oc->nr_albumu, oc->kod_przedmiotu, oc->ocena, oc->komentarz);
        oc = oc->nast;
    }
    fclose(fin);
    
    return NULL;
}

int ile_studentow(SBaza *baza) {
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}

int ile_przedmiotow(SBaza *baza) {
    int n = 0;
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) {
        n++;
        przed = przed->nast;
    }
    return n;
}

int ile_ocen(SBaza *baza) {
    int n = 0;
    Ocena * oc = baza->lista_ocen;
    while (oc != NULL) {
        n++;
        oc = oc->nast;
    }
    return n;
}

void listuj_studentow(SBaza *baza) {
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

SBaza * dodaj_studenta (SBaza *baza, char *imie, char *nazwisko, char *nr_albumu, char *email){
    Student *nowy = (Student*) malloc(sizeof(Student));
  	Student *aktualnie = NULL;

  	nowy->nast = NULL;
    
  	nowy->imie = (char*) malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(nowy->imie, imie);

    nowy->nazwisko = (char*) malloc(sizeof(char) * (strlen(nazwisko) + 1));
    strcpy(nowy->nazwisko, nazwisko);

    nowy->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(nowy->nr_albumu, nr_albumu);

    nowy->email = (char*) malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(nowy->email, email);

    aktualnie=baza->lista_studentow;
    
    if(ile_studentow(baza) == 0){
      baza->lista_studentow = nowy;
    }
    else{
      for(int i=1; i<ile_studentow(baza); i++){
        aktualnie = aktualnie->nast;
      }
      aktualnie->nast = nowy;
    }
        
    return NULL;
}

void dodaj_przedmiot(SBaza *baza, char *kod_przed, char *nazwa_przed, char *sem){
    Przedmiot *nowy = (Przedmiot*) malloc(sizeof(Przedmiot));
  	Przedmiot *aktualnie = NULL;

  	nowy->nast = NULL;

  	nowy->kod_przed = (char*) malloc(sizeof(char) * (strlen(kod_przed) + 1));
    strcpy(nowy->kod_przed, kod_przed);

    nowy->nazwa_przed = (char *)malloc(sizeof(char) * (strlen(nazwa_przed) + 1));
    strcpy(nowy->nazwa_przed, nazwa_przed);

    nowy->sem = (char*) malloc(sizeof(char) * (strlen(sem) + 1));
    strcpy(nowy->sem, sem);

    aktualnie = baza->lista_przedmiotow;
    
    if(ile_przedmiotow(baza) == 0){
      baza->lista_przedmiotow = nowy;
    }
    else{
      for(int i=1; i<ile_przedmiotow(baza); i++){
        aktualnie = aktualnie->nast;
      }
      aktualnie->nast = nowy;
    }    
}

SBaza * dodaj_stud_do_przed(SBaza *baza, char *kod_przedmiotu, char *nr_albumu, float ocena, char *komentarz){
    Ocena *nowy = (Ocena*) malloc(sizeof(Ocena));
  	Ocena *aktualnie = NULL;
    
  	nowy->nast = NULL;
    
  	nowy->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod_przedmiotu) + 1));
    strcpy(nowy->kod_przedmiotu, kod_przedmiotu);

    nowy->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(nowy->nr_albumu, nr_albumu);

    nowy->ocena=ocena;

    nowy->komentarz = (char*) malloc(sizeof(char) * (strlen(komentarz) + 1));
    strcpy(nowy->komentarz, komentarz);

    aktualnie=baza->lista_ocen;
    
    if(ile_ocen(baza) == 0){
      baza->lista_ocen = nowy;
    }
    else{
      for(int i=1; i<ile_ocen(baza); i++){
        aktualnie = aktualnie->nast;
      }
      aktualnie->nast = nowy;
    }
        
    return NULL;
}

void zwolnij_student(Student *s) {
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *s) {
    free(s->kod_przed);
    free(s->nazwa_przed);
    free(s->sem);
    free(s);
}

void zwolnij_ocene(Ocena *s) {
    free(s->nr_albumu);
    free(s->kod_przedmiotu);
    free(s->komentarz);
    free(s);
}

void zwolnij_liste_studentow(Student *s) {
    Student *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *s) {
    Przedmiot *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_przedmiot(s);
        s = n;
    }
}
void zwolnij_liste_ocen(Ocena *s) {
    Ocena *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_ocene(s);
        s = n;
    }
}

void zwolnij(SBaza *baza) {
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
}