/* PLACINTA ALEXANDRU, 324CB */

#ifndef structuri
#define structuri

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;


typedef struct
{
	string stareUrmatoare;
	char caracterScris;
	char deplasare;
} Tranzitie;


typedef struct celula
{
	struct celula *urm;
	Tranzitie *tranzitie;
	char caracterCitit;
} Celula, *Lista, **ALista;


typedef struct
{
	int nrStari;
	Lista *listeAdiacenta;
} Graf, *AGraf;

#endif
