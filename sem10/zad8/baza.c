#include "baza.h"

void wypisz_rekurencyjnie(Student *el) {
    if (el != NULL) {
        printf("%s %s %s %s\n", el->imie, el->nazwisko, el->nr_albumu, el->email);        
        wypisz_rekurencyjnie( el->nast );
    }
}

Student * ostatni_student(Student *glowa) {
    Student *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Przedmiot * ostatni_przedmiot(Przedmiot *glowa) {
    Przedmiot *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Ocena * ostatnia_ocena(Ocena *glowa) {
    Ocena *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Student *glowa = NULL;
    Student *c;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;
        stud->poprz = NULL;

        if (glowa == NULL)
            glowa = stud;
        else {
            c = ostatni_student(glowa);
            c->nast = stud;
            stud->poprz = c;
        }

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
    Przedmiot *c;
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin); 
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;
        przed->poprz = NULL;

         if (glowa == NULL)
            glowa = przed;
        else {
            c = ostatni_przedmiot(glowa);
            c->nast = przed;
            przed->poprz = c;
        }

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
    Ocena *c;
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin); 
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *oc = (Ocena*) malloc(sizeof(Ocena));
        oc->nast = NULL;
        oc->poprz = NULL;

        if (glowa == NULL)
            glowa = oc;
        else {
            c = ostatnia_ocena(glowa);
            c->nast = oc;
            oc->poprz = c;
        }

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        oc->kod_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->kod_przedmiotu, s);

        s = strtok(NULL, ";");
        oc->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->nr_albumu, s);

        s = strtok(NULL, ";");
        oc->ocena = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->ocena, s);

        // s = strtok(NULL, ";");
        // oc->ocena = atof(s);

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
        fprintf(fin, "%s;%s;%s;%s\n", oc->kod_przedmiotu, oc->nr_albumu, oc->ocena, oc->komentarz);
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

void listuj_przedmioty(SBaza *baza) {
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) {
        printf("%s %s %s\n", przed->kod_przed, przed->nazwa_przed, przed->sem);
        przed = przed->nast;
    }
}

void listuj_oceny(SBaza *baza) {
    Ocena * oc = baza->lista_ocen;
    while (oc != NULL) {
        printf("%s %s %s %s\n",  oc->kod_przedmiotu, oc->nr_albumu, oc->ocena, oc->komentarz);
        oc = oc->nast;
    }
}

Student * zwroc_stud(Student *glowa, int i) {
    while (glowa != NULL && i-- > 0) // i jest zmniejszany postfixowo - czyli po porownaniu z 0
        glowa = glowa->nast;    
    
    return glowa;
}

Przedmiot * zwroc_przed(Przedmiot *glowa, int i) {
    while (glowa != NULL && i-- > 0) 
        glowa = glowa->nast;    
    
    return glowa;
}

Ocena * zwroc_oc(Ocena *glowa, int i) {
    while (glowa != NULL && i-- > 0)
        glowa = glowa->nast;    
    
    return glowa;
}

void listuj_studentow_od_konca(SBaza *b) {
    // Student *ogon = ostatni_student(b->lista_studentow);
    Student *c;
    /*
    while (c != null) {

        c = c->poprz;
    }
    */
    // for (c=ogon; c != NULL; c = c->poprz) {
    //     printf("%s %s %s %s\n", c->imie, c->nazwisko, c->nr_albumu, c->email);        
    // }

    int i;
    int n = ile_studentow(b);
    for (i=(n-1); i >= 0; i--) {
        c = zwroc_stud(b->lista_studentow, i);
        printf("%s %s %s %s\n", c->imie, c->nazwisko, c->nr_albumu, c->email);        
    }
}

void listuj_przedmioty_od_konca(SBaza *b) {
    
    Przedmiot *c;
   
    int i;
    int n = ile_przedmiotow(b);
    for (i=(n-1); i >= 0; i--) {
        c = zwroc_przed(b->lista_przedmiotow, i);
        printf("%s %s %s \n", c->kod_przed, c->nazwa_przed, c->sem);        
    }
}

void wypisz_rekurencyjnie_od_konca(Student *el) {
    if (el != NULL) {
        wypisz_rekurencyjnie( el->nast );
        printf("%s %s %s %s\n", el->imie, el->nazwisko, el->nr_albumu, el->email);        
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

SBaza * dodaj_stud_do_przed(SBaza *baza, char *kod_przedmiotu, char *nr_albumu, char *ocena, char *komentarz){
    Ocena *nowy = (Ocena*) malloc(sizeof(Ocena));
  	Ocena *aktualnie = NULL;
    
  	nowy->nast = NULL;
    
  	nowy->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod_przedmiotu) + 1));
    strcpy(nowy->kod_przedmiotu, kod_przedmiotu);

    nowy->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(nowy->nr_albumu, nr_albumu);

    nowy->ocena = (char*) malloc(sizeof(char) * (strlen(ocena) + 1));
    strcpy(nowy->ocena, ocena);

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

Student * najwiekszy_student(Student *el) {
    Student * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->nazwisko, max->nazwisko) > 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Przedmiot * najwiekszy_przedmiot_kod(Przedmiot *el) {
    Przedmiot * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->kod_przed, max->kod_przed) > 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Przedmiot * najwieksza_przedmiot_nazwa(Przedmiot *el) {
    Przedmiot * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->nazwa_przed, max->nazwa_przed) > 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Student * usun_stud(Student *glowa, Student *el) {
    Student *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;
                break;
            }
            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Przedmiot * usun_przed(Przedmiot *glowa, Przedmiot *el) {
    Przedmiot *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;
                break;
            }
            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Ocena * usun_oc(Ocena *glowa, Ocena *el) {
    Ocena *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;
                break;
            }
            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Student * sortuj_stud_przez_wybieranie(Student *glowa) {
    Student * nglowa = NULL;
    Student * m;
    Student * o; // = NULL;

    while (glowa != NULL) {
        m = najwiekszy_student(glowa);
        glowa = usun_stud(glowa, m);
        
        o = ostatni_student(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
        // o = m;
        // printf("Najwiekszy: %s\n", m->nazwisko);
        // wypisz_rekurencyjnie(glowa);
    }
    return nglowa;
}

Przedmiot * sortuj_przed_przez_wybieranie_kod(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o;

    while (glowa != NULL) {
        m = najwiekszy_przedmiot_kod(glowa);
        glowa = usun_przed(glowa, m);
        
        o = ostatni_przedmiot(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }
    return nglowa;
}

Przedmiot * sortuj_przed_przez_wybieranie_nazwa(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o;

    while (glowa != NULL) {
        m = najwieksza_przedmiot_nazwa(glowa);
        glowa = usun_przed(glowa, m);
        
        o = ostatni_przedmiot(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
    }
    return nglowa;
}

Ocena * filtruj_przedmiot(Ocena * glowa, char *kodzik, SBaza *baza) {
    Ocena *c = NULL;
    Ocena * n = NULL;
    
    for (int i = 0; i < ile_ocen(baza); i++){
        //printf("oki\n");
        if(strcmp(glowa->kod_przedmiotu, kodzik)==0){ //pomylilem nr albumu z kodem przedmiotu przy wpisywaniu
            Ocena * nowaglowa;
            nowaglowa=(Ocena*) malloc(sizeof(Ocena));
            nowaglowa->nast = NULL;
            nowaglowa->poprz = NULL;
            if(c==NULL)
                c=nowaglowa;
            else{
                n = ostatnia_ocena(c);
                ostatnia_ocena(c)->nast = nowaglowa;
                nowaglowa->poprz = n;
            }
            nowaglowa->kod_przedmiotu=glowa->kod_przedmiotu;
            nowaglowa->nr_albumu=glowa->nr_albumu;
            nowaglowa->ocena=glowa->ocena;
            nowaglowa->komentarz=glowa->komentarz;
            //printf("%s %s %s %s\n", nowaglowa->kod_przedmiotu, nowaglowa->nr_albumu, nowaglowa->ocena, glowa->komentarz);
        }
        glowa=glowa->nast;
    }
    //printf("git\n");
    return c;
}

Ocena * filtruj_przedmiot2(Ocena * glowa, char *albumik, SBaza *baza) {
    Ocena *c = NULL;
    Ocena * n = NULL;
    
    for (int i = 0; i < ile_ocen(baza); i++){
        //printf("oki\n");
        if(strcmp(glowa->nr_albumu, albumik)==0){ //pomylilem nr albumu z kodem przedmiotu przy wpisywaniu
            Ocena * nowaglowa;
            nowaglowa=(Ocena*) malloc(sizeof(Ocena));
            nowaglowa->nast = NULL;
            nowaglowa->poprz = NULL;
            if(c==NULL)
                c=nowaglowa;
            else{
                n = ostatnia_ocena(c);
                ostatnia_ocena(c)->nast = nowaglowa;
                nowaglowa->poprz = n;
            }
            nowaglowa->kod_przedmiotu=glowa->kod_przedmiotu;
            nowaglowa->nr_albumu=glowa->nr_albumu;
            nowaglowa->ocena=glowa->ocena;
            nowaglowa->komentarz=glowa->komentarz;
            //printf("%s %s %s %s\n", nowaglowa->kod_przedmiotu, nowaglowa->nr_albumu, nowaglowa->ocena, glowa->komentarz);
        }
        glowa=glowa->nast;
    }
    //printf("git\n");
    return c;
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