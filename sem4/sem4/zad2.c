#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void macierz(FILE *fina, int wa, int ka, float taba[100][100])
{
	float la;

	if (fina == NULL)
	{
		printf("Plik nie może zostać otwarty\n");
	}
	else
	{
		printf("macierz A o rozmiarze (%dx%d):\n", wa, ka);
		for (int a = 0; a < wa; a++)
		{
			printf("[ ");
			for (int b = 0; b < ka; b++)
			{
				fscanf(fina, "%f", &la);
				taba[a][b] = la;
				printf("%.1f ", taba[a][b]);
			}
			printf("]\n");
		}
	}
}

void wektor(FILE *finx, int wx, int kx, float tabx[100][100])
{
	float lx, w;
	
	if (finx == NULL)
	{
		printf("Plik nie może zostać otwarty\n");
	}
	else
	{
		printf("wektor x o rozmiarze (%dx%d):\n", wx, kx);
		for (int a = 0; a < wx; a++)
		{
			printf("[ ");
			for (int b = 0; b < kx; b++)
			{
				fscanf(finx, "%f", &lx);
				tabx[a][b] = lx;
				printf("%.1f ", tabx[a][b]);
			}
			printf("]\n");
		}
	}
}

float wymnoz(FILE* fina, FILE* finx, float taba[100][100], float tabx[100][100], int wa, int ka, int wx, int kx)
{
	printf("Po wymnożeniu macierzy 'A' przez wektor 'x' otzymujemy macierz o wymiarach (%dx%d):\n", wa, kx);
	float suma;
	for (int a = 0; a < wa; a++)
	{
		printf("[ ");
		suma = 0;
		for (int b = 0; b < ka; b++)
		{			
			suma = suma + (taba[a][b] * tabx[b][0]);						
		}
		printf("%.1f", suma);
		printf(" ]\n");
		
	}
	return 0;
}

int main(int argc, char* argv[])
{
	FILE* fina;
	int wa, ka;
	float taba[100][100];
	fina = fopen(argv[1], "r");
	fscanf(fina, "%d%d", &wa, &ka);
	macierz(fina, wa, ka, taba);

	FILE* finx;
	int wx, kx;
	float tabx[100][100];
	finx = fopen(argv[2], "r");
	fscanf(finx, "%d%d", &wx, &kx);
	wektor(finx, wx, kx, tabx);

	wymnoz(finx, fina, taba, tabx, wa, ka, wx, kx);
	
	return 0;
}