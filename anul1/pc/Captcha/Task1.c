#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bmp_header.h"


typedef struct
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
}pixel;


void verify_file(FILE *fisier)
{
	if (!fisier)
	{
		printf("%s", strerror(errno));
		exit(1);
	}
}


pixel **matrice(FILE *intrare_captcha, int nr_linii, int nr_coloane)
{
	int i, j;
	pixel **matrice_pixeli;

	matrice_pixeli=malloc(nr_linii*sizeof(pixel *));
	if (!matrice){ exit(1); }
	else
	{
		for (i=0; i<nr_linii; i++)
		{
			matrice_pixeli[i]=malloc(nr_coloane*sizeof(pixel));
			if (!matrice)
			{
				for (j=0; j<=i; j++){ free(matrice_pixeli[j]);}
				exit(1);
			}
		}
	}

	for (i=0; i<nr_linii; i++)
	{
		for (j=0; j<nr_coloane; j++){ fread(&matrice_pixeli[i][j], sizeof(pixel), 1, intrare_captcha); }

		j=0;
		while ( (3*nr_coloane+j)%4 ){fseek(intrare_captcha, 1, SEEK_CUR); j++; }  //sar octetii de padding, citind astfeldoar matricea de pixeli
	}

return matrice_pixeli;
}


void Task1(pixel **matrice, struct bmp_fileheader *fileheader, struct bmp_infoheader *infoheader, unsigned char B, unsigned char G, unsigned char R, FILE *iesire_captcha)
{
	int i, j;
	char a=0;  // aceasta variabila reprezinta un octet din padding-ul ce va fi pus pe fiecare linie

	fwrite (fileheader, sizeof(struct bmp_fileheader), 1, iesire_captcha);  //scriu fileheader-ul noului captcha
	fwrite (infoheader, sizeof(struct bmp_infoheader), 1, iesire_captcha);  //scriu infoheader-ul noului captcha

	for (i=0; i<infoheader->height; i++)
	{
		for (j=0; j<infoheader->width; j++)
		{
			if ( (matrice[i][j].B!=255) || (matrice[i][j].G!=255) || (matrice[i][j].R!=255) ) //verifica daca pixelul curent este diferit de pixelul alb
			{
				matrice[i][j].B=B;
				matrice[i][j].G=G;
				matrice[i][j].R=R;
			}
		}
	}

	for (i=0; i<infoheader->height; i++)
	{
		for (j=0; j<infoheader->width; j++){ fwrite(&matrice[i][j], sizeof(pixel), 1, iesire_captcha); } //scriu in noul fisier captcha cifrele colorate

		j=0;
		while ((3*infoheader->width+j)%4){ fwrite(&a, sizeof(char), 1, iesire_captcha);j++; } //completez cu padding-ul adecvat pe fiecare linie
	}
}


int main(void)
{
	FILE *intrare_text, *intrare_captcha, *iesire_captcha;
	char *nume_captcha, *nume="_task1.bmp";
	unsigned char B, G, R;  // componentele noi culori ale elementelor din fisierul ".bmp" de iesire
	int i, j, k;
	struct bmp_fileheader fileheader;
	struct bmp_infoheader infoheader;
	pixel **matrice_pixeli;

	intrare_text=fopen("input.txt", "r");
	verify_file(intrare_text); //verifica daca s-a efectuat deschiderea cu succes a fisierului "input.txt"

	nume_captcha=malloc(30*sizeof(char));  //aloc spatiu pentru numele fisierului ".bmp"
	if (!nume_captcha){ exit(1); }
	else{ fscanf(intrare_text, "%s %hhu %hhu %hhu", nume_captcha, &B, &G, &R); }  //citesc numele fisierului ".bmp" de intrare, dar si componenetele noii culori in format BGR

	intrare_captcha=fopen(nume_captcha, "r+b");
	verify_file(intrare_captcha);  //veirifca daca s-a deschis fisierul ".bmp" de intrare

	for (k=0; nume_captcha[k]!='.'; k++);
	strcpy(nume_captcha+k, nume);   //generez numele fisierului ".bmp" de iesire

	iesire_captcha=fopen(nume_captcha, "w+b");  //deschid fisierlu ".bmp" de iesire pentru scriere in  modul binar
	verify_file(iesire_captcha);

	fread(&fileheader, sizeof(fileheader), 1, intrare_captcha);  //citesc fileheader-ul fisierului ".bmp" de intrare
	fread(&infoheader, sizeof(infoheader), 1, intrare_captcha);	 //citesc infoheader-ul fisierului ".bmp" de intrare
	fseek(intrare_captcha, fileheader.imageDataOffset, SEEK_SET);  //pozitionez indicatorul de pozitie al fisierului ".bmp" de intrare la inceputului matricei de pixeli

	matrice_pixeli=matrice(intrare_captcha, infoheader.height, infoheader.width);  //generez matricea de pixeli

	Task1(matrice_pixeli, &fileheader, &infoheader, B, G, R, iesire_captcha);  //efectuez operatia aferanta Task-ului 1

	for (i=0; i<infoheader.height; i++){ free(matrice_pixeli[i]); }
	free(matrice_pixeli);

	free(nume_captcha);

	fclose(intrare_text);
	fclose(intrare_captcha);
	fclose(iesire_captcha);

return 0;
}
