#ifndef file_h
#define file_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct _macierz {
	int r;
	int c;
	float **tab;
} macierz;

void wczytaj(FILE* fin, macierz *m);

void wypisz(macierz m, macierz x);

void wypisz2(macierz a, macierz b, macierz x);

void zapisz(FILE* fin, macierz m, macierz x);

void zapisz2(FILE* fin, macierz a, macierz b, macierz x);

void zwolnij(macierz *m);

#endif