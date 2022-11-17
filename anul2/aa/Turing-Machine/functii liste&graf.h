/* PLACINTA ALEXANDRU, 324CB */

#ifndef functii
#define functii

#include "structuri.h"


Tranzitie *creareTranzitie( string stareUrmatoare, char caracterScris, char deplasare )
{
	Tranzitie *tranzitie;

	tranzitie = new Tranzitie;
	if ( !tranzitie )
	{
		return NULL;
	}

	tranzitie->stareUrmatoare = stareUrmatoare;
	tranzitie->caracterScris = caracterScris;
	tranzitie->deplasare = deplasare;
	
	return tranzitie;
}


Celula *alocCelula( string stareUrmatoare, char caracterScris, char deplasare, char caracterCitit )    // aloca o celula cu toate datele unei tranzitii dintr-o stare in alta stare 
{
	Celula *celula;
	
	celula = new Celula;
	if ( !celula )
	{
		return NULL;
	} 

	celula->tranzitie = creareTranzitie( stareUrmatoare, caracterScris, deplasare );
	if ( !celula->tranzitie )
	{
		delete celula;
		return NULL;
	}
	
	celula->caracterCitit = caracterCitit;
	celula->urm = NULL;
	return celula;
}


void adaugaElementLista( ALista lista, Celula *celula )         // adauga un element la finalul listei, functie folosita pentru construirea grafului
{
	Lista iterator, anterior = NULL;
	
	if ( *lista == NULL )
	{
		*lista = celula;
	}
	else
	{
		for ( iterator = *lista; iterator != NULL; anterior = iterator, iterator = iterator->urm );
		anterior->urm = celula;
	}
}


void distrugeCelula( Celula **celula )
{
	delete ( ( *celula )->tranzitie );
	delete ( *celula );
	*celula = NULL;
}


void distrugereLista( ALista lista )
{
	Lista iterator, aux = NULL;

	for ( iterator = *lista; iterator != NULL; )
	{
		aux = iterator->urm;
		distrugeCelula( &iterator );
		iterator = aux;
	}

	*lista = NULL;
}


Graf *initGraf( int nrStari )        // initializeaza un graf cu 'n' noduri, unde 'n' este numarul de stari
{
	int i;
	Graf *graf;

	graf = new Graf;
	if ( !graf )
	{
		return NULL;
	}

	graf->nrStari = nrStari;                      
	graf->listeAdiacenta = new Lista[ nrStari ];               // construiesc un vectori de pointeri la listele de adiacenta aferente nodurilor
	if ( !graf->listeAdiacenta )
	{
		delete graf;
		return NULL;
	}

	for ( i = 0; i < nrStari; i++ )               // initializez pointerii cu NULL
	{
		graf->listeAdiacenta[ i ] = NULL;
	}

	return graf;
}


void distrugereGraf( AGraf *graf )
{
	int i;
	AGraf grafAux = *graf;

	for ( i = 0; i < grafAux->nrStari; i++ )
	{
		distrugereLista( grafAux->listeAdiacenta + i );		
	}

	delete[] grafAux->listeAdiacenta;
	delete grafAux;
	*graf = NULL;
}


Graf *umplereGraf( char const *numeFisierIntrare, string **stariFinale, int &nrStariFinale, string &stareInitiala )   // construieste graful masinii turing 
{
	int i, numar = 0, pozitie = 0, max = 0, index;
	char caracterScris, caracterCitit, deplasare;	
	string stareUrmatoare, stare;
	ifstream fisierIntrare;
	Graf *graf;
	Celula *celula;

	fisierIntrare.open( numeFisierIntrare );    // verifica daca fisierul s-a deschis
	if ( !fisierIntrare.is_open() )
	{
		return NULL;
	}

	fisierIntrare >> numar;   // citesc numarul de stari

	if ( max < numar )			// gasesc numarul maxim de stari pentru a sti exact cate liste de adiacenta sa construiesc
	{
		max = numar;
	}

	if ( numar )
	{

		for ( i = 0; i < numar; i++ )    //citesc si starile si aflu numarul aferent diecarei stari si modific numarul maxim de stari "max"
		{
			fisierIntrare >> stare;
			index = atoi( stare.c_str() + 1 );

			if ( max < index )
			{
				max = index;
			}
		}

		max++;
		graf = initGraf( max );
		if ( !graf )
		{
			return NULL;
		}

		fisierIntrare >> numar;   		// citesc numarul de stari finale
		nrStariFinale = numar;

		( *stariFinale ) = new string[ numar ];
		if ( !( *stariFinale ) )
		{
			distrugereGraf( &graf );
			return NULL;
		}
	
		for( i = 0; i < numar; i++ )
		{
			fisierIntrare >> stare;	
			( *stariFinale )[ i ] = stare;  // introduc starile finale in vectorul de stari finale
		} 

		fisierIntrare >> stareInitiala;       // citesc starea intiala
		fisierIntrare >> numar;							  // citesc numarul de tranzitii

		for ( i = 0; i < numar; i++ )
		{
			fisierIntrare >> stare;               // citesc starea din care pleaca tranzitia si caracterul care se citeste pentru a porni acea tranzitie
			fisierIntrare >> caracterCitit;

			fisierIntrare >> stareUrmatoare;     // citesc parametrii aferenti tranzitiei in ordinea indicata de numele variabilelor de mai jos
			fisierIntrare >> caracterScris;
			fisierIntrare >> deplasare;

			pozitie = atoi( stare.c_str() + 1 );    										  // generez pozitia listei de adiacenta din care face parte tranzitia
			celula = alocCelula( stareUrmatoare, caracterScris, deplasare, caracterCitit );   // aloc o celula de lista si introduc in lista acel element
			adaugaElementLista( &( graf->listeAdiacenta[ pozitie ] ), celula );			
		}
	}
	else
	{
		return NULL;
	}

	fisierIntrare.close();
	
	return graf;
}


string citireBanda( char const *numeFisierIntrareBanda )   // citeste banda din fisierul de intrare
{
	ifstream fisierIntrareBanda;
	string banda;

	fisierIntrareBanda.open( numeFisierIntrareBanda );
	if ( !fisierIntrareBanda.is_open() )
	{
		return "-1";
	}

	fisierIntrareBanda >> banda;
	fisierIntrareBanda.close();

	return banda;	
}


#endif
