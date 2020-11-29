#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "file.h"

macierz dodaj(macierz a, macierz b)
{
	int i, j;
	float s;

	macierz *suma;
	suma = (macierz*) malloc(sizeof(macierz));

	suma->r = a.r;
	suma->c = a.c;

	 suma->tab = (float**) malloc(sizeof(float*) * suma->r);
     for (i=0;i<suma->r;i++)
         suma->tab[i] = (float*) malloc(sizeof(float) * suma->c);

	if ((a.r != b.r) || (a.c != b.c)) {
		printf("Obie macierze muszą być tego samego rozmiaru!\n");
	}
	else {
		for (i = 0; i < suma->r; i++) {
			for (j = 0; j < suma->c; j++) {
				s = 0;
				s += a.tab[i][j] + b.tab[i][j];
				suma->tab[i][j] = s;
			}
		}		
	}
	return *suma;
}

macierz odejmij(macierz a, macierz b)
{
	int i, j;
	float s;
	macierz *roznica;
	
	roznica = (macierz*) malloc(sizeof(macierz));

	roznica->r = a.r;
	roznica->c = a.c;

	 roznica->tab = (float**) malloc(sizeof(float*) * roznica->r);
     for (i=0;i<roznica->r;i++)
         roznica->tab[i] = (float*) malloc(sizeof(float) * roznica->c);

	if ((a.r != b.r) || (a.c != b.c)) {
		printf("Obie macierze muszą być tego samego rozmiaru!\n");
	}
	else {
		for (i = 0; i < roznica->r; i++) {
			for (j = 0; j < roznica->c; j++) {
				s = 0;
				s += a.tab[i][j] - b.tab[i][j];
				roznica->tab[i][j] = s;
			}
		}
	}
	return *roznica;
}

macierz pomnoz(macierz m, float a)
{
	float s;
	macierz *iloczyn;

	iloczyn = (macierz*) malloc(sizeof(macierz));

	iloczyn->r = m.r;
	iloczyn->c = m.c;

	iloczyn->tab = (float**) malloc(sizeof(float*) * iloczyn->r);
    for (int i=0;i<iloczyn->r;i++)
         iloczyn->tab[i] = (float*) malloc(sizeof(float) * iloczyn->c);
	
	for (int i = 0; i < iloczyn->r; i++) {
		for (int j = 0; j < iloczyn->c; j++) {
			s = 0;
			s += m.tab[i][j] * a;
			iloczyn->tab[i][j] = s;
		}
	}
	return *iloczyn;
}

macierz mnozenie(macierz a, macierz b)
{
	macierz *ilomac;
	ilomac = (macierz*) malloc(sizeof(macierz));

	ilomac->r = a.r;
	ilomac->c = b.c;

	ilomac->tab = (float**) malloc(sizeof(float*) * ilomac->r);
    for (int i=0;i<ilomac->r;i++)
         ilomac->tab[i] = (float*) malloc(sizeof(float) * ilomac->c);

	for (int w = 0; w < a.r; w++){
		for (int k = 0; k < b.c; k++){

			float ilo = 0;
			for (int x = 0; x < a.c; x++){
				ilo += (a.tab[w][x] * b.tab[x][k]);
			}

			ilomac->tab[w][k] = ilo;
		}
	}
	return *ilomac;
}

float norm(macierz m) {
	float s = 0;
	int i, j;

	for (i = 0; i < m.r; i++) {
		for (j = 0; j < m.c; j++) {
			s += m.tab[i][j] * m.tab[i][j];
		}
	}
	return sqrt(s);
}