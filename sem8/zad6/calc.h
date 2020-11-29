#ifndef calc_h
#define calc_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "file.h"

macierz dodaj(macierz a, macierz b);

macierz odejmij(macierz a, macierz b);

macierz pomnoz(macierz m, float a);

macierz mnozenie(macierz a, macierz b);

float norm(macierz m);

#endif