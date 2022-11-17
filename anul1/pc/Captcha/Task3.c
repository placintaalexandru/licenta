#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bmp_header.h"


typedef struct
{
	unsigned char B, G, R;
}pixel;


typedef struct //structra creata pentru a retine pozitia fata de coltulului din dreapta sus a unei cifre fata de coltul din stanga sus
{
	int x, y;
}pozitie;


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


void pixeli_nuli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie)
{
	int i, j;

	for (j=inceput_coloana; j>=inceput_coloana-4; j--)
         {
                for (i=inceput_linie; i<=inceput_linie+4; i++)
                {
                        if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) )
                        {
                                matrice_pixeli[i][j].B=255;
                                matrice_pixeli[i][j].G=255;
                                matrice_pixeli[i][j].R=255;
                        }
                }
         }
}


int nr_pixeli(pixel **matrice_pixeli, int inceput_coloana, int inceput_linie)
{
	int i, j, nr=0;

	 for (j=inceput_coloana; j>=inceput_coloana-4; j--)
         {
	 	for (i=inceput_linie; i<=inceput_linie+4; i++)
                {
                	if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) ){ nr++; }
                }
         }

return nr;
}


int numere_pozitii(pixel **matrice_pixeli, int nr_linii, int nr_coloane, int **numere_captcha, pozitie **vector_poz) //generez numerele din fisierul ".bmp" de intrare si pentru fiecare numar si pozitia sa
{
	int i, j, nr, count=0, *numere;

	numere=malloc((count+2)*sizeof(int));

	if (!numere){ exit(1); }

	for (j=nr_coloane-1; j>=4; j--)
	{
		for (i=0; i<nr_linii-4; i++)
		{
			if ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) )
			{
				nr=nr_pixeli(matrice_pixeli, j, i);

				(*vector_poz)[count].x=j;
				(*vector_poz)[count].y=i;
				(*vector_poz)=realloc((*vector_poz), (count+2)*sizeof(pozitie));

				if (nr==16)
				{
					numere[count]=0;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==5)
				{
					numere[count]=1;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==11)
				{
					numere[count]=4;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==9)
				{
					numere[count]=7;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==19)
				{
					numere[count]=8;
					count++;
					numere=realloc(numere, (count+2)*sizeof(int));
				}
				if (nr==17)
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
				if (nr==18)
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

				pixeli_nuli(matrice_pixeli, j, i);
			}
		}
	}

	(*numere_captcha)=realloc(*numere_captcha, (count)*sizeof(int));
	for (i=0; i<count; i++){ (*numere_captcha)[i]=numere[count-1-i]; }

	for (i=0; i<(count+1)/2; i++)
	{
		j=(*vector_poz)[i].x;
		(*vector_poz)[i].x=(*vector_poz)[count-1-i].x;
		(*vector_poz)[count-1-i].x=j;

		j=(*vector_poz)[i].y;
                (*vector_poz)[i].y=(*vector_poz)[count-1-i].y;
                (*vector_poz)[count-1-i].y=j;

	}

	free(numere);


return count;
}


void schimbare(pixel **matrice_pixeli, int linie_origine, int coloana_origine, int linie_destinatie, int coloana_destinatie) // mut o cifra de pe o pozitie pe alta in matricea de pixeli
{
	int i, j;

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			matrice_pixeli[linie_destinatie+i][coloana_destinatie-j].B=matrice_pixeli[linie_origine+i][coloana_origine-j].B;
			matrice_pixeli[linie_destinatie+i][coloana_destinatie-j].G=matrice_pixeli[linie_origine+i][coloana_origine-j].G;
			matrice_pixeli[linie_destinatie+i][coloana_destinatie-j].R=matrice_pixeli[linie_origine+i][coloana_origine-j].R;
			matrice_pixeli[linie_origine+i][coloana_origine-j].B=255;
			matrice_pixeli[linie_origine+i][coloana_origine-j].G=255;
			matrice_pixeli[linie_origine+i][coloana_origine-j].R=255;
		}
	}
}


void translatare(pixel **matrice_pixeli, pozitie *vector_poz, int *numere_captcha, int *numere_text, int count, int nr_elemente)
{
	int i, j, k;
	for (i=0; i<count-1; i++)
	{
		for (j=0; j<nr_elemente; j++)
		{
			if (numere_captcha[i]==numere_text[j]) //verific daca cifra din fisierul ".bmp" de intrare trebuia sa fie scoasa
			{
				for (k=i; k<count-1; k++){ schimbare(matrice_pixeli, vector_poz[k+1].y, vector_poz[k+1].x, vector_poz[k].y, vector_poz[k].x); } // mut fiecare cifra de pe o pozitie "i+1" in locul precedentei
				for (k=count-1; k>i; k--)  // am grija ca si pozitiile cifrelor sa fie actualizate, facand ca pozita ficarei cifre din intervalul [i; count-1] sa devina pozitia cifrei din fata sa
				{
					vector_poz[k].x=vector_poz[k-1].x;
					vector_poz[k].y=vector_poz[k-1].y;
				}
			}
		}
	}
	for (j=0; j<nr_elemente; j++)
	{
		if (numere_captcha[count-1]==numere_text[j]) //la final verifica daca si ultima cifra din fisierul ".bmp" de intrare trebuie stearsa
		{
			pixeli_nuli(matrice_pixeli, vector_poz[count-1].x, vector_poz[count-1].y); //trasnform pixelii aferenti ultimei cifre in pixeli albi
			break;
		}
	}
}


void Task3(pixel **matrice_pixeli, struct bmp_fileheader *fileheader, struct bmp_infoheader *infoheader, FILE *iesire_captcha, int *numere_captcha, int *numere_text, int count, int nr_elemente, pozitie *vector_poz)
{
	int i, j;
	char a=0;

	translatare(matrice_pixeli, vector_poz, numere_captcha, numere_text, count, nr_elemente);

	fwrite(fileheader, sizeof(struct bmp_fileheader), 1, iesire_captcha);
	fwrite(infoheader, sizeof(struct bmp_infoheader), 1, iesire_captcha);

	for (i=infoheader->height-1; i>=0; i--)
	{
		for (j=0; j<infoheader->width; j++){ fwrite(&matrice_pixeli[i][j], sizeof(pixel), 1, iesire_captcha); }

		j=0;
		while ( (3*infoheader->width+j)%4 )  //completez cu padding-ul adecvat
		{
			fwrite(&a, sizeof(a), 1, iesire_captcha);
			j++;
		}
	}
}


int main(void)
{
	FILE *intrare_text, *intrare_captcha, *iesire_captcha;
	char *nume_captcha, *nume="_task3.bmp";
	unsigned char B, G, R;
	int i, j, k, count, nr_elemente, *numere_text, *numere_captcha;
	struct bmp_fileheader fileheader;
	struct bmp_infoheader infoheader;
	pixel **matrice_pixeli, **copie; //am nevoie de o copie pentru a recunoaste cifrele din fisierul ".bmp" de intrare
	pozitie *vector_poz; //vectorul ce retine pozitiile


	intrare_text=fopen("input.txt", "r");
	verify_file(intrare_text);

	vector_poz=malloc(1*sizeof(pozitie));
	nume_captcha=malloc(30*sizeof(char));
	numere_text=malloc(2*sizeof(int));
	numere_captcha=malloc(1*sizeof(int));
	if ( (!nume_captcha) || (!numere_text) || (!numere_captcha) || (!vector_poz) ){ exit(1); }
	else
	{
		fscanf(intrare_text, "%s %hhu %hhu %hhu", nume_captcha, &B, &G, &R);

		nr_elemente=0;
		while ( fscanf(intrare_text, "%d", &i)==1 )
		{
			numere_text[nr_elemente]=i;
			nr_elemente++;
			numere_text=realloc(numere_text, (nr_elemente+2)*sizeof(int));
		}
	}

	intrare_captcha=fopen(nume_captcha, "r+b");
	verify_file(intrare_captcha);

	for (k=0; nume_captcha[k]!='.'; k++);
	strcpy(nume_captcha+k, nume);

	iesire_captcha=fopen(nume_captcha, "w+b");
	verify_file(iesire_captcha);

	fread(&fileheader, sizeof(fileheader), 1, intrare_captcha);
	fread(&infoheader, sizeof(infoheader), 1, intrare_captcha);

	fseek(intrare_captcha, fileheader.imageDataOffset, SEEK_SET);
	matrice_pixeli=matrice(intrare_captcha, infoheader.height, infoheader.width);

	fseek(intrare_captcha, fileheader.imageDataOffset, SEEK_SET);
	copie=matrice(intrare_captcha, infoheader.height, infoheader.width);

	count=numere_pozitii(copie, infoheader.height, infoheader.width, &numere_captcha, &vector_poz);

	Task3(matrice_pixeli, &fileheader, &infoheader, iesire_captcha, numere_captcha, numere_text, count, nr_elemente, vector_poz);

	for (i=0; i<infoheader.height; i++)
	{
		free(matrice_pixeli[i]);
		free(copie[i]);
	}

	free(copie);
	free(matrice_pixeli);
	free(vector_poz);
	free(nume_captcha);
	free(numere_captcha);
	free(numere_text);

	fclose(intrare_text);
	fclose(intrare_captcha);
	fclose(iesire_captcha);

return 0;
}
