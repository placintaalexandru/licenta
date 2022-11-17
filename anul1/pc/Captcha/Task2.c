#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "bmp_header.h"


typedef struct
{
	unsigned char B, G, R;
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

	for (i=nr_linii-1; i>=0; i--)
	{
		for (j=0; j<nr_coloane; j++){ fread(&matrice_pixeli[i][j], sizeof(pixel), 1, intrare_captcha); }

		j=0;
		while ( (3*nr_coloane+j)%4 )
		{
			fseek(intrare_captcha, 1, SEEK_CUR);
			j++;
		}  //sar octetii de padding, citind astfeldoar matricea de pixeli
	}

return matrice_pixeli;
}


void pixeli_nuli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie)  //fac pixeli albi din pixeli colorati
{
	int i, j;

	for (j=inceput_coloana; j>=inceput_coloana-4; j--)
         {
                for (i=inceput_linie; i<=inceput_linie+4; i++)
                {
                        if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) )  //verifica da pixelul curent este diferit de pixelul alb
                        {
                                matrice_pixeli[i][j].B=255;
                                matrice_pixeli[i][j].G=255;
                                matrice_pixeli[i][j].R=255;
                        }
                }
         }
}


int nr_pixeli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie) //verifica numarul de pixeli colorati dintr-o submatrice de "5x5"
{
	int i, j, nr=0;

	 for (j=inceput_coloana; j>=inceput_coloana-4; j--)
         {
	 	for (i=inceput_linie; i<=inceput_linie+4; i++)
                {
                	if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) ){ nr++; } //verifica daca pixelul curent este colorat si incrementez valoarea lui nr
                }
         }

return nr;
}


void Task2(pixel **matrice_pixeli, int nr_linii, int nr_coloane, FILE *iesire_text)
{
	int i, j, nr, count=0, *numere;

	numere=malloc((count+2)*sizeof(int));

	if (!numere){ exit(1); }

	for (j=nr_coloane-1; j>=4; j--)
	{
		for (i=0; i<nr_linii-4; i++)
		{
			if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) ) //verifica daca pixelul curent e diferit de cel alb pentru a incepe identificare
			{
				nr=nr_pixeli(matrice_pixeli, j, i); //numar efectiv pixelii din submatricea de "5x5" ca are coltul dindreapta sus coordonatele mele acctuale dinmatricea de pixeli

				if (nr==16) //conditia sigura pentru ca un numarul din sumbatricea de "5x5" sa fie 0
				{
					numere[count]=0;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==5)  //conditia sigura pentru ca un numarul din sumbatricea de "5x5" sa fie 1
				{
					numere[count]=1;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==11)  //conditia sigura pentru ca un numarul din sumbatricea de "5x5" sa fie 4
				{
					numere[count]=4;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==9)  //conditia sigura pentru ca un numarul din sumbatricea de "5x5" sa fie 7
				{
					numere[count]=7;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==19)  //conditia sigura pentru ca un numarul din sumbatricea de "5x5" sa fie 8
				{
					numere[count]=8;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==17)  //conditie care impune analiza a 3 cazuri, deorace 3, 5 si 2 au acelasi numar de pixeli si va trebui analizata pozitia 2 pixeli semnificativi
				{
					if ( (matrice_pixeli[i+1][j].B!=255) || (matrice_pixeli[i+1][j].G!=255) || (matrice_pixeli[i+1][j].R!=255) )
					{
						if ( (matrice_pixeli[i+3][j].B!=255) || (matrice_pixeli[i+3][j].G!=255) || (matrice_pixeli[i+3][j].R!=255) )
						{
							numere[count]=3;
							count++;
							numere=realloc(numere, (count+2)*sizeof(int));
						}
						else
						{
							numere[count]=2;
							count++;
							numere=realloc(numere, (count+2)*sizeof(int));
						}
					}
					else
					{
						numere[count]=5;
						count++;
						numere=realloc(numere, (count+2)*sizeof(int));
					}
				}
				if (nr==18) ////conditia care imoune analiza 2 cazuri, deoarece 6 si 9 au acelasi numar de pixeli si va trebui analizata pozitia unui pixel semnificativ
				{
					if ( (matrice_pixeli[i+1][j].B!=255) || (matrice_pixeli[i+1][j].G!=255) || (matrice_pixeli[i+1][j].R!=255) )
					{
						numere[count]=9;
						count++;
						numere=realloc(numere, (count+2)*sizeof(int));
					}
					else
					{
						numere[count]=6;
						count++;
						numere=realloc(numere, (count+2)*sizeof(int));
					}
				}

				pixeli_nuli(matrice_pixeli, j, i); //dupa ce am recunoscut numarul il sterg din fisierul ".bmp" de inrare pentru a nu mai da peste vreun pixel din el

			}
		}
	}

	for (i=count-1; i>=0; i--){ fprintf(iesire_text, "%d", numere[i]); }  //scriu numerele gasite in fisrul ".txt" de iesire in ordine inversa,deoaarece eu parcurg matricea de pixeli din coltul dreapta sus
	free(numere); //eliberez memoria folosita pentru stocarea numerelor
}


int main(void)
{
	FILE *intrare_text, *iesire_text, *intrare_captcha;
	char *nume_captcha, *nume="_task2.txt";
	unsigned char B, G, R;
	int i, j, k;
	struct bmp_fileheader fileheader;
	struct bmp_infoheader infoheader;
	pixel **matrice_pixeli;

	intrare_text=fopen("input.txt", "r");
	verify_file(intrare_text);

	nume_captcha=malloc(30*sizeof(char));
	if (!nume_captcha){ exit(1); }
	else{ fscanf(intrare_text, "%s", nume_captcha); }

	intrare_captcha=fopen(nume_captcha, "r+b");
	verify_file(intrare_captcha);

	for (k=0; nume_captcha[k]!='.'; k++);
	strcpy(nume_captcha+k, nume);

	iesire_text=fopen(nume_captcha, "w");
	verify_file(iesire_text);

	fread(&fileheader, sizeof(fileheader), 1, intrare_captcha);
	fread(&infoheader, sizeof(infoheader), 1, intrare_captcha);
	fseek(intrare_captcha, fileheader.imageDataOffset, SEEK_SET);

	matrice_pixeli=matrice(intrare_captcha, infoheader.height, infoheader.width);

	Task2(matrice_pixeli, infoheader.height, infoheader.width, iesire_text);

	for (i=0; i<infoheader.height; i++){ free(matrice_pixeli[i]); }
	free(matrice_pixeli);

	free(nume_captcha);

	fclose(intrare_text);
	fclose(intrare_captcha);
	fclose(iesire_text);

return 0;
}
