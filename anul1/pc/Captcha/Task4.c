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


pixel ***vector_mat_pixeli()   //creez un vector ce retine matricele de pixeli, de o culoare de mine aleasa, ale cifrelor de la 0 la 9
{
	int i, j, k;
	pixel ***vect_mat_pixeli;

	vect_mat_pixeli=malloc(10*sizeof(pixel **));

	if (!vect_mat_pixeli){ exit(1); }
	else
	{
		for (i=0; i<10; i++)
		{
			vect_mat_pixeli[i]=malloc(5*sizeof(pixel *));
			if (!vect_mat_pixeli[i])
			{
				for (j=0; j<=i; j++){ free(vect_mat_pixeli[i]); }
				free(vect_mat_pixeli);
			}
			else
			{
				for (j=0; j<5; j++)
				{
					vect_mat_pixeli[i][j]=malloc(5*sizeof(pixel));
					if (!vect_mat_pixeli[i][j])
					{
						for (k=0; k<=j; k++){ free(vect_mat_pixeli[i][k]); }
						for (k=0; k<=i; k++){ free(vect_mat_pixeli[k]); }
						free(vect_mat_pixeli);
						exit(1);
					}
				}
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==4) || (j==0) || (j==4) )
			{
				vect_mat_pixeli[0][i][j].B=100;
				vect_mat_pixeli[0][i][j].G=100;
				vect_mat_pixeli[0][i][j].R=100;
			}

			else
			{
				vect_mat_pixeli[0][i][j].B=255;
                                vect_mat_pixeli[0][i][j].G=255;
                                vect_mat_pixeli[0][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if (j==4)
			{
				vect_mat_pixeli[1][i][j].B=100;
                                vect_mat_pixeli[1][i][j].G=100;
                                vect_mat_pixeli[1][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[1][i][j].B=255;
                                vect_mat_pixeli[1][i][j].G=255;
                                vect_mat_pixeli[1][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || ( (i==1) && (j==4) ) || ( (i==3) && (j==0) ) )
			{
				vect_mat_pixeli[2][i][j].B=100;
                                vect_mat_pixeli[2][i][j].G=100;
                                vect_mat_pixeli[2][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[2][i][j].B=255;
                                vect_mat_pixeli[2][i][j].G=255;
                                vect_mat_pixeli[2][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || ( (i==1) && (j==4) ) || ( (i==3) && (j==4) ) )
			{
				vect_mat_pixeli[3][i][j].B=100;
                                vect_mat_pixeli[3][i][j].G=100;
                                vect_mat_pixeli[3][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[3][i][j].B=255;
                                vect_mat_pixeli[3][i][j].G=255;
                                vect_mat_pixeli[3][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==2) || (j==4) || ( (j==0) && ( (i==0) || (i==1) ) ) )
			{
				vect_mat_pixeli[4][i][j].B=100;
                                vect_mat_pixeli[4][i][j].G=100;
                                vect_mat_pixeli[4][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[4][i][j].B=255;
                                vect_mat_pixeli[4][i][j].G=255;
                                vect_mat_pixeli[4][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || ( (i==1) && (j==0) ) || ( (i==3) && (j==4) ) )
			{
				vect_mat_pixeli[5][i][j].B=100;
                                vect_mat_pixeli[5][i][j].G=100;
                                vect_mat_pixeli[5][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[5][i][j].B=255;
                                vect_mat_pixeli[5][i][j].G=255;
                                vect_mat_pixeli[5][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || (j==0) || ( (i==3) && (j==4) ) )
			{
				vect_mat_pixeli[6][i][j].B=100;
                                vect_mat_pixeli[6][i][j].G=100;
                                vect_mat_pixeli[6][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[6][i][j].B=255;
                                vect_mat_pixeli[6][i][j].G=255;
                                vect_mat_pixeli[6][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (j==4) )
			{
				vect_mat_pixeli[7][i][j].B=100;
                                vect_mat_pixeli[7][i][j].G=100;
                                vect_mat_pixeli[7][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[7][i][j].B=255;
                                vect_mat_pixeli[7][i][j].G=255;
                                vect_mat_pixeli[7][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || (j==0) || (j==4) )
			{
				vect_mat_pixeli[8][i][j].B=100;
                                vect_mat_pixeli[8][i][j].G=100;
                                vect_mat_pixeli[8][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[8][i][j].B=255;
                                vect_mat_pixeli[8][i][j].G=255;
                                vect_mat_pixeli[8][i][j].R=255;
			}
		}
	}

	for (i=0; i<5; i++)
	{
		for (j=0; j<5; j++)
		{
			if ( (i==0) || (i==2) || (i==4) || (j==4) || ( (i==1) && (j==0) ) )
			{
				vect_mat_pixeli[9][i][j].B=100;
                                vect_mat_pixeli[9][i][j].G=100;
                                vect_mat_pixeli[9][i][j].R=100;
			}
			else
			{
				vect_mat_pixeli[9][i][j].B=255;
                                vect_mat_pixeli[9][i][j].G=255;
                                vect_mat_pixeli[9][i][j].R=255;
			}
		}
	}

return vect_mat_pixeli;
}


int cmp(pixel ***vect_mat_pixeli, pixel **matrice_pixeli, int linie, int coloana) //compar submatricea "5x5" al carei colt din dreapta sus are pozitia fata de coltul din stanga sus al matricei (linie, coloana)
{
	int i, j, k, nr, v[10], minim=100;

	for (i=0; i<10; i++)
	{
		nr=0;

		for (k=0; k<5; k++)
		{
			for (j=4; j>=0; j--) //gasesc numarul de pixeli diferiti
			{
				if ( ( (vect_mat_pixeli[i][k][j].B!=255) || (vect_mat_pixeli[i][k][j].G!=255) || (vect_mat_pixeli[i][k][j].R!=255) ) && ( (matrice_pixeli[linie+k][coloana+j-4].B==255) && (matrice_pixeli[linie+k][coloana+j-4].G==255) && (matrice_pixeli[linie+k][coloana+j-4].R==255) ) ){ nr++;}
				if ( ( (vect_mat_pixeli[i][k][j].B==255) && (vect_mat_pixeli[i][k][j].G==255) && (vect_mat_pixeli[i][k][j].R==255) ) && ( (matrice_pixeli[linie+k][coloana+j-4].B!=255) || (matrice_pixeli[linie+k][coloana+j-4].G!=255) || (matrice_pixeli[linie+k][coloana+j-4].R!=255) ) ){ nr++;}
			}
		}

		v[i]=nr; //numarul "i" reprezentat prin matricea de pixeli "5x5" difera de submatricea curenta de pixeli prin "nr" pixeli
	}


	for (i=0; i<10; i++)
	{
		if (minim>v[i]){ minim=v[i]; } //gasesc ce numar difera printr-un numar minim de pixeli
	}

	if ( (minim==1) || (minim==0) )  //numarul minim trebuie sa fie 0 sau 1, deoarece problema specifica ca se adauga/extrage doar un singur pixel
	{
		for (i=0; i<10; i++)
		{
			if (minim==v[i]){ return i; }  //returnez cifra care poate sa fie reprezentata de submatricea curenta "5x5"
		}
	}
	else{ return -1; }
}


void bonus(pixel ***vect_mat_pixeli, pixel **matrice_pixeli, struct bmp_infoheader *infoheader, FILE *iesire_text)
{
	int i, j, i1, a, nr, sw_linie, sw_coloana, count=0, v[100];

	for (j=infoheader->width-1; j>=4; j--)
	{
		for (i=0; i<infoheader->height-4; i++)
		{
			if ( ( (matrice_pixeli[i][j].B!=255) || (matrice_pixeli[i][j].G!=255) || (matrice_pixeli[i][j].R!=255) ) || ( ( (matrice_pixeli[i+1][j].B!=255) || (matrice_pixeli[i+1][j].G!=255) || (matrice_pixeli[i+1][j].R!=255) ) && ( (matrice_pixeli[i][j-1].B!=255) || (matrice_pixeli[i][j-1].G!=255) || (matrice_pixeli[i][j-1].R!=255) ) ) )
			{
				a=cmp(vect_mat_pixeli, matrice_pixeli, i, j);
				if (a>=0)
				{
					v[count++]=a;
					pixeli_nuli(matrice_pixeli, j, i);
				}
			}
			else
			{
				sw_linie=0;
				sw_coloana=0;

				nr=0;
				for (i1=0; i1<5; i1++)
				{
					if ( (matrice_pixeli[i+i1][j].B!=255) || (matrice_pixeli[i+i1][j].G!=255) || (matrice_pixeli[i+i1][j].R!=255) ){ nr++; }
					if (i+5<infoheader->height)
					{
						if ( ( (matrice_pixeli[i+5][j].B==255) && (matrice_pixeli[i+5][j].G==255) && (matrice_pixeli[i+5][j].R==255) ) && (nr>=3) ){ sw_linie=1; }
					}
					else
					{
						if (nr>=3){ sw_linie=1; }
					}
				}

				nr=0;
				for (i1=1; i1<5; i1++)
				{
					if ( (matrice_pixeli[i][j-i1].B!=255) || (matrice_pixeli[i][j-i1].G!=255) || (matrice_pixeli[i][j-i1].R!=255) ){ nr++; }
					if (j-5>=0)
					{
						if ( ( (matrice_pixeli[i][j-5].B==255) && (matrice_pixeli[i][j-5].G==255) && (matrice_pixeli[i][j-5].R==255) ) && (nr>=0) ){ sw_coloana=1; }
					}
					else
					{
						if (nr>=0){ sw_coloana=1; }
					}
				}

				if ( (sw_linie==1) && (sw_coloana==1) )
				{
					a=cmp(vect_mat_pixeli, matrice_pixeli, i, j);
					if (a>=0)
					{
						v[count++]=a;
						pixeli_nuli(matrice_pixeli, j, i);
					}
				}
			}
		}
	}

	for (i=count-1; i>=0; i--){ fprintf(iesire_text, "%d", v[i]); }
}


int main(void)
{
	FILE *intrare_text, *iesire_text, *intrare_captcha;
	char *nume_captchab, *nume="_bonus.txt";
	int i, j, k;
	struct bmp_fileheader fileheader;
	struct bmp_infoheader infoheader;
	pixel ***vect_mat_pixeli, **matrice_pixeli;

	intrare_text=fopen("input.txt", "r");
	verify_file(intrare_text);

	nume_captchab=malloc(30*sizeof(char));
	if (!nume_captchab){ exit(1); }
	else{ fscanf(intrare_text, "%s", nume_captchab); }

	while (fscanf(intrare_text, "%d", &i)==1);

	fscanf(intrare_text, "%s", nume_captchab);

	intrare_captcha=fopen(nume_captchab, "r+b");
	verify_file(intrare_captcha);

	for (k=0; nume_captchab[k]!='.'; k++);
	strcpy(nume_captchab+k, nume);

	iesire_text=fopen(nume_captchab, "w");
	verify_file(iesire_text);

	fread(&fileheader, sizeof(fileheader), 1, intrare_captcha);
	fread(&infoheader, sizeof(infoheader), 1, intrare_captcha);
	fseek(intrare_captcha, fileheader.imageDataOffset, SEEK_SET);

	matrice_pixeli=matrice(intrare_captcha, infoheader.height, infoheader.width);

	vect_mat_pixeli=vector_mat_pixeli();



	bonus(vect_mat_pixeli, matrice_pixeli, &infoheader, iesire_text);

	for (i=0; i<10; i++)
	{
		for (k=0; k<5; k++){ free(vect_mat_pixeli[i][k]); }
		free(vect_mat_pixeli[i]);
	}
	free(vect_mat_pixeli);

	for (i=0; i<infoheader.height; i++){ free(matrice_pixeli[i]); }
	free(matrice_pixeli);

	free(nume_captchab);

	fclose(intrare_text);
	fclose(intrare_captcha);
	fclose(iesire_text);

return 0;
}
