/* PLACINTA ALEXANDRU, 324CB */

#include "structuri.h"
#include "functii liste&graf.h"
#define AGATA "Se agata!"
#define BLANK_CHARACTER '#'
using namespace std;


bool stareFinala( string stareCurenta, string *stariFinale, int nrStariFinale )    // starile finale sunt starile ale caror liste de adiacenta corespunzatoare sunt nule, asa ca voi verifica daca lista aferenta starii curente e nula
{
	int i;

	for ( i = 0; i < nrStariFinale; i++ )
	{
		if ( stareCurenta == stariFinale[ i ] )
		{
			return true;
		}
	}

	return false;
}


void functieDelta( string &banda, string &stareCurenta, string *stariFinale, int nrStariFinale, Graf *graf, unsigned int &pozitieCapCitire )
{
	Lista iterator;
	int nrStareCurenta;

	while ( !stareFinala( stareCurenta, stariFinale, nrStariFinale ) )  // efectuez operatii cat timp nu sunt in starea finala
	{
		nrStareCurenta = atoi( stareCurenta.c_str() + 1 );			// generez pozitia listei din care citesc tranzitia in functie de caracterul pe care il citesc de pe banda
		iterator = graf->listeAdiacenta[ nrStareCurenta ];
		
		if ( pozitieCapCitire == banda.size() - 1 )             // daca am ajuns la finalul benzii, maresc banda de scriere
		{
			banda.push_back( BLANK_CHARACTER );
		}

		for ( ; iterator != NULL && iterator->caracterCitit != banda[ pozitieCapCitire ]; iterator = iterator->urm );	//caut tranzitia in lista
		
		if ( iterator == NULL )    // daca am ajuns la finalul listei de adiacenta, inseamna ca din starea curenta nu citesc nicio codificare valida, deci masina se agata
		{
			banda = AGATA;
			return;
		}
		else
		{
			stareCurenta = iterator->tranzitie->stareUrmatoare;
			banda[ pozitieCapCitire ] = iterator->tranzitie->caracterScris;
	
			switch( iterator->tranzitie->deplasare )     				// modific pozitia capului de citire doar daca tranzitia cere o deplasare a acestuia
			{
				case 'R':

					pozitieCapCitire++;									// mut pozitia capului de citire la dreapta

					
					break;
				
				case 'L':

					pozitieCapCitire--;									// mut pozitia capului de citire la stanga
					break;
			}
		}
	}	
}


void start( char const *numeFisierIntrare, char const *numeFisierIesire, char const *numeFisierIntrareBanda )   // functia primeste numele fisierelor, cosntruieste graful aferent masinii si simuleaza operatiile
{
	int nrStariFinale;
	unsigned int pozitieCapCitire( 1 );
	Graf *graf;
	ofstream fisierIesire;
	ifstream fisierIntrareBanda;
	string *stariFinale, stareInitiala, banda;

	fisierIesire.open( numeFisierIesire );
	if ( !fisierIesire.is_open() )
	{
			return;
	}

	fisierIntrareBanda.open( numeFisierIntrareBanda );
	if ( !fisierIntrareBanda.is_open() )
	{
		fisierIesire.close();
		return;
	}
	
	graf = umplereGraf( numeFisierIntrare, &stariFinale, nrStariFinale, stareInitiala );
	banda = citireBanda( numeFisierIntrareBanda );
	functieDelta( banda, stareInitiala, stariFinale, nrStariFinale, graf, pozitieCapCitire );
	
	fisierIesire << banda;

	fisierIesire.close();
	fisierIntrareBanda.close();
	distrugereGraf( &graf );
	delete[] stariFinale;
}
