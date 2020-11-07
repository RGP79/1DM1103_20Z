#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct macierz {
	int r;
	int c;
	float tab[200][200];
};

void wczytaj(FILE* fin, struct macierz *m) {
	int i, j;
	fscanf(fin, "%d", &m->r);
	fscanf(fin, "%d", &m->c);

	for (i = 0; i < m->r; i++) {
		for (j = 0; j < m->c; j++) {
			fscanf(fin, "%f", &m->tab[i][j]);
		}
	}
}

struct macierz dodaj(struct macierz a, struct macierz b)
{
	struct macierz suma;
	int i, j;
	float s;
	if ((a.r != b.r) || (a.c != b.c)) {
		printf("Obie macierze muszą być tego samego rozmiaru!\n");
	}
	else {
		for (i = 0; i < a.r; i++) {
			for (j = 0; j < a.c; j++) {
				s = 0;
				s += a.tab[i][j] + b.tab[i][j];
				suma.tab[i][j] = s;
			}
		}		
	}
	return suma;
}

struct macierz mnozenie(struct macierz a, struct macierz b)
{
	struct macierz ilomac;
	for (int w = 0; w < a.r; w++)
	{
		for (int k = 0; k < b.c; k++)
		{
			float ilo = 0;
			for (int x = 0; x < a.c; x++)
			{
				ilo += (a.tab[w][x] * b.tab[x][k]);
			}
			ilomac.tab[w][k] = ilo;
		}
	}
	return ilomac;
}

void wypisz(struct macierz m, struct macierz x) {
	int i, j;
	printf("[ ");
	for (i = 0; i < m.r; i++) {
		for (j = 0; j < m.c; j++) {
			printf("%5.1f ", x.tab[i][j]);
		}
		if (i < (m.r - 1))
			printf("\n  ");
	}
	printf("]\n");
}

void wypisz2(struct macierz a, struct macierz b, struct macierz x) {
	int i, j;
	printf("[ ");
	for (i = 0; i < a.r; i++) {
		for (j = 0; j < b.c; j++) {
			printf("%5.1f ", x.tab[i][j]);
		}
		if (i < (a.r - 1))
			printf("\n  ");
	}
	printf("]\n");
}

void zapisz(FILE* fin, struct macierz m, struct macierz x) {
	int i, j;
	fprintf(fin, "[ ");
	for (i = 0; i < m.r; i++) {
		for (j = 0; j < m.c; j++) {
			fprintf(fin, "%5.1f ", x.tab[i][j]);
		}
		if (i < (m.r - 1))
			fprintf(fin, "\n  ");
	}
	fprintf(fin, "]\n");
	printf("plik wyeksportowano pomyślnie!\n");
}

void zapisz2(FILE* fin, struct macierz a, struct macierz b, struct macierz x) {
	int i, j;
	fprintf(fin, "[ ");
	for (i = 0; i < a.r; i++) {
		for (j = 0; j < b.c; j++) {
			fprintf(fin, "%5.1f ", x.tab[i][j]);
		}
		if (i < (a.r - 1))
			fprintf(fin, "\n  ");
	}
	fprintf(fin, "]\n");
	printf("plik wyeksportowano pomyślnie!\n");
}

struct macierz odejmij(struct macierz a, struct macierz b)
{
	struct macierz roznica;
	int i, j;
	float s;
	if ((a.r != b.r) || (a.c != b.c)) {
		printf("Obie macierze muszą być tego samego rozmiaru!\n");
	}
	else {
		for (i = 0; i < a.r; i++) {
			for (j = 0; j < a.c; j++) {
				s = 0;
				s += a.tab[i][j] - b.tab[i][j];
				roznica.tab[i][j] = s;
			}
		}
	}
	return roznica;
}

struct macierz pomnoz(struct macierz m, float a)
{
	struct macierz iloczyn;
	float s;
	for (int i = 0; i < m.r; i++) {
		for (int j = 0; j < m.c; j++) {
			s = 0;
			s += m.tab[i][j] * a;
			iloczyn.tab[i][j] = s;
		}
	}
	return iloczyn;
}

float norm(struct macierz m) {
	float s = 0;
	int i, j;

	for (i = 0; i < m.r; i++) {
		for (j = 0; j < m.c; j++) {
			s += m.tab[i][j] * m.tab[i][j];
		}
	}
	return sqrt(s);
}

int main(int argc, char* argv[]) {
	
	if (strcmp(argv[1], "sum") == 0) {
		if (argc == 4) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			struct macierz suma = dodaj(mac, mac2);
			wypisz(mac, suma);
		}
		else if (argc == 5) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			struct macierz suma = dodaj(mac, mac2);
			zapisz(fin3, mac, suma);
		}
	}
	else if (strcmp(argv[1], "prod") == 0) {
		if (argc == 4) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			struct macierz ilomac = mnozenie(mac, mac2);
			wypisz2(mac, mac2, ilomac);
		}
		else if (argc == 5) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			struct macierz ilomac = mnozenie(mac, mac2);
			zapisz2(fin3, mac, mac2, ilomac);
		}
	}
	else if (strcmp(argv[1], "subtract") == 0) {
		if (argc == 4) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			struct macierz roznica = odejmij(mac, mac2);
			wypisz(mac, roznica);
		}
		else if (argc == 5) {
			struct macierz mac;
			struct macierz mac2;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin2 = fopen(argv[3], "r");
			wczytaj(fin2, &mac2);
			fclose(fin2);

			FILE* fin3 = fopen(argv[4], "w");
			struct macierz roznica = odejmij(mac, mac2);
			zapisz(fin3, mac, roznica);
		}
	}
	else if (strcmp(argv[1], "multiply") == 0) {
		if (argc == 4) {
			struct macierz mac;
			float a = atof(argv[3]);

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			struct macierz iloczyn = pomnoz(mac, a);
			wypisz(mac, iloczyn);
		}
		else if (argc == 5) {
			struct macierz mac;
			float a = atof(argv[3]);

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin3 = fopen(argv[4], "w");
			struct macierz iloczyn = pomnoz(mac, a);
			zapisz(fin3, mac, iloczyn);
		}
	}
	else if (strcmp(argv[1], "norm") == 0) {
		if (argc == 3) {
			struct macierz mac;

			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			norm(mac);
			float s = norm(mac);
			printf("%f\n", s);
		}
		else if (argc == 4) {
			struct macierz mac;
			
			FILE* fin = fopen(argv[2], "r");
			wczytaj(fin, &mac);
			fclose(fin);

			FILE* fin3 = fopen(argv[3], "w");
			float s = norm(mac);
			fprintf(fin3, "%f\n", s);
			printf("plik wyeksportowano pomyślnie!\n");
		}
	}
	return 0;
}