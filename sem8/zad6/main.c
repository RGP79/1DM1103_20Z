#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "calc.h"
#include "file.h"

int main(int argc, char* argv[]) {
	
macierz mac;
macierz mac2;
macierz suma;
macierz roznica;
macierz iloczyn;
macierz ilomac;
	if (strcmp(argv[1], "sum") == 0) {
		if (argc == 4) {

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			suma = dodaj(mac, mac2);
			wypisz(mac, suma);			     		
		}
		else if (argc == 5) {
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			suma = dodaj(mac, mac2);
			zapisz(fin3, mac, suma);			
		}
	}
	else if (strcmp(argv[1], "prod") == 0) {
		if (argc == 4) {
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			ilomac = mnozenie(mac, mac2);
			wypisz2(mac, mac2, ilomac);
		}
		else if (argc == 5) {
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			ilomac = mnozenie(mac, mac2);
			zapisz2(fin3, mac, mac2, ilomac);
		}
	}
	else if (strcmp(argv[1], "subtract") == 0) {
		if (argc == 4) {
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			roznica = odejmij(mac, mac2);
			wypisz(mac, roznica);
		}
		else if (argc == 5) {
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			macierz roznica = odejmij(mac, mac2);
			zapisz(fin3, mac, roznica);
		}
	}
	else if (strcmp(argv[1], "multiply") == 0) {
		if (argc == 4) {
			macierz mac;
			float a = atof(argv[3]);

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			iloczyn = pomnoz(mac, a);
			wypisz(mac, iloczyn);
		}
		else if (argc == 5) {
			macierz mac;
			float a = atof(argv[3]);

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin3 = fopen(argv[4], "w");
			iloczyn = pomnoz(mac, a);
			zapisz(fin3, mac, iloczyn);
		}
	}
	else if (strcmp(argv[1], "norm") == 0) {
		if (argc == 3) {
			macierz mac;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			norm(mac);
			float s = norm(mac);
			printf("%f\n", s);
		}
		else if (argc == 4) {
			macierz mac;
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin3 = fopen(argv[3], "w");
			float s = norm(mac);
			fprintf(fin3, "%f\n", s);
			printf("plik wyeksportowano pomyślnie!\n");
		}
	}
	zwolnij(&mac);
	zwolnij(&mac2);
	zwolnij(&suma);
	zwolnij(&roznica);
	zwolnij(&iloczyn);
	zwolnij(&ilomac);
	return 0;
}