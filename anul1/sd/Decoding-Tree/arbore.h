/* Placinta Alexandru - 314CB */
/* Contine functiile de baza pentru un arbore, precum si structurile folosite */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 7000
#define MIN 100
#define NCMP 3

typedef struct nod
{
	int nr_fii;
	unsigned char litera, caracter;
	struct nod **vector_fii, *parinte;
} TNod, *TArb;


TArb ConstrFr( void )
{
	TArb frunza;

	frunza = calloc( sizeof( TNod ), 1 );
	if ( !frunza ){ return NULL; }

	return frunza;
}


int NrNiv(TArb a)  /* calculeaza numarul de nivele dintr-un arbore */
{
	if ( !a ){ return 0; }            /* daca e vid nu fac nimic */
	else if ( !a->nr_fii ){ return 1; }     /* daca nu are fii inseamna ca e doar un nod, adica nivel 1 */
	else
	{
		int i, max = 0;       /* max va retine numarul maxim de nivele, numar care este un numar natural */

		for ( i = 0; i < a->nr_fii; i++ )
		{
			if ( max < NrNiv( a->vector_fii[i] ) ){ max = NrNiv( a->vector_fii[i] ); }  /* fac maximul de nivele dintre fiii nodului */
		}

		return 1 + max;       /* returnez 1 + max, deoarece iau in calcul si noudl curent, nod superior fiilor */
	}
}


int NrNoduri(TArb a)      /* calculeaza numarul de noduri dintr-un arbore */
{
	int i, nr_noduri = 0;

	if ( !a ){ return 0; }        /* daca e vid nu fac nimic */
	if ( !a->nr_fii ){ return 1; }     /* daca nu are fiu inseamna ca e un singur nod, adica returnez 1 */

	for ( i = 0; i < a->nr_fii; i++ ){ nr_noduri += NrNoduri( a->vector_fii[i] ); }   /* ma duc recursiv pe fiecare fiu */

	return 1 + nr_noduri;   /* returnez 1 + nr_noduri pt ca iau in calcul si nodul curent */
}


void Afi_aux(TArb a, int nivel_curent, int nivel_dorit, FILE *iesire)       /* afiseaza informatia nodurilor din arbore de pe nivelul dorit */
{
	int i;

	if ( !a ){ return; }
	if ( nivel_curent == nivel_dorit )            /* daca nivelul pe care sunt este cel cautat afisez nformatia din nod si ma opresc, nemaiavnd treaba cu nodurile de pe niveluri mai mari */
	{ 
		fprintf( iesire, "(" );
		if ( a->caracter ){ fprintf( iesire, "%c", a->caracter ); }
		fprintf( iesire, ":" );
		if ( a->litera ){ fprintf( iesire, "%c", a->litera ); }
		fprintf( iesire, ")" );
		return;
	}

	for ( i = 0; i < a->nr_fii; i++ ){ Afi_aux( a->vector_fii[i], nivel_curent + 1, nivel_dorit, iesire ); }   /* daca sunt pe un nivel mai mic, cobor pe fiecare din fiii acestui nod pana dau de nivelul dorit */
}


void AfiArb(TArb a, FILE *iesire)
{
	int i, nr_nivele;

	nr_nivele = NrNiv( a );                      /* am nevoie de numarul de nivele pentru a afisa in latime informatia */

	for ( i = 0; i < nr_nivele; i++ )           /* parcurg nivelele */
	{
		Afi_aux( a, 0, i, iesire );                     /* pentru fiecare nivel afisez nodurile din arbore de pe nivelele dorite "i" */
		fprintf( iesire, "\n" );	
	}
}


void DistrArb_aux(TArb *a, int nivel_curent, int nivel_dorit)       /* elibereaza memoria alocata pentru un arbore, pe nivele, incepand cu nivelele superioare spre nivelelel inferioare */
{
	int i;

	if ( !a ){ return; }
	if ( nivel_curent == nivel_dorit )            /* daca nivelul pe care sunt este cel cautat, eliberez informatia si opresc functia */
	{ 
		if ( ( *a )->vector_fii ){ free( ( *a )->vector_fii ); }
		free( *a );
		*a = NULL;
		return;
	}

	for ( i = 0; i < ( *a )->nr_fii; i++ ){ DistrArb_aux( &( ( *a )->vector_fii[i] ), nivel_curent + 1, nivel_dorit ); }   /* daca sunt pe un nivel mai mic, cobor pe fiecare din fiii acestui nod pana dau de nivelul dorit */
}


void DistrArb(TArb *a)                     /* elibereaza memeoria alocata pentru un arbore pornit de la frunze spre radacina */
{
	int i, nr_nivele;

	nr_nivele = NrNiv( *a );               /* calculzez numarul total de nivele */

	for ( i = nr_nivele - 1; i >= 0; i-- ){ DistrArb_aux( a, 0, i); }           /* distrug rand pe rand nodurile de pe nivlul "i" */
}


void Gaseste_aux(TArb a, char litera, TArb *gasit)       /* cauta in arbore nodul ce contine pe litera si modifica un pointer pentru a puncta catre acea zona de memorie */
{	
	int i;

	if ( !a ){ return; }                                               /* daca e vid nu fac nimic */
	if ( ( a->nr_fii == 0 ) && ( a->litera != litera ) ){ return; }    /* daca nu are fii si litera nu corespunde ma opresc */
	if ( a->litera == litera )                                         /* daca am gasit litera modific pointerul "gasit" */
	{
		*gasit = a;
		return;
	}

	for ( i = 0; i < a->nr_fii; i++ ){ Gaseste_aux( a->vector_fii[i], litera, gasit ); }  /* ma duc recursiv pe fiecare fiu */
}


TArb Gaseste(TArb a, char litera)        /* cauta in arbore nodul ce contine "litera" si returneaza un pointer catre acea zona de memorie */
{
	TArb gasit = NULL;

	Gaseste_aux( a, litera, &gasit );

	return gasit;
}


int add(TArb a, char *linie)
{
	char *litera, *codificare, *separatori = " \n";
	int i, j, lungime_cod;

	litera = strtok( linie, separatori );          /* iau separat litera din comanda */
	codificare = strtok( NULL, separatori );       /* iau separat codificare pentru litera de pe linie */
	lungime_cod = strlen( codificare );            /* fac atatea iteratii cat este lungimea codificarii */
	bool gasit;

	for ( i = 0; i < lungime_cod; i++ )            /* cobor in arbore cat timp nu ajung la capatul codificarii */
	{
		gasit = false;

		for ( j = 0; j < a->nr_fii; j++ )            /* parcurg vectorul de fii pentru a vedea daca caracterul de pe pozitia "i" este deja in arbore */
		{
			if ( a->vector_fii[j]->caracter == codificare[i] )       /* inseamna ca caracterul din codificare se gaseste intr-un fiu, deci cobor in fiu si intrerup cautarea din fii */
			{
				a = a->vector_fii[j];                 /* cobor in arbore pe fiul gasit */                  
				gasit = true;
				break; 
			}
		}

		if ( gasit == false )            /* daca am ajuns la captul vectorul de fii sau daca arborele nu avea niciun fiu realoc */
		{	
			j = a->nr_fii;
			a->nr_fii++;
			a->vector_fii = realloc( a->vector_fii, a->nr_fii * sizeof( TArb ) );      /* realoc cu inca un pointer vectorul de fii */
			if ( !a->vector_fii ){ return 0; }                                         /* verific daca s-a efectuat realocarea */
		
			a->vector_fii[j] = ConstrFr();                                             /* construiesc un nou fiu */
			if ( a->vector_fii[j] == NULL ){ return 0; }

			a->vector_fii[j]->caracter = codificare[i];
			a->vector_fii[j]->parinte = a;                                             /* retin parintele nodului in care cobor in arbore */
			a = a->vector_fii[j];                                                       /* cobor in arbore */
		}
	}

	a->litera = *litera;
	return 1;
}


void Realoca(TArb a, int pozitie)     /* realoca vectorul de fii dintr-un nod atunci cand acest vector trebuie micsorat */
{
	int i;
	TNod **vector_fii;

	vector_fii = calloc( sizeof( TArb ), a->nr_fii - 1 );     /* iau un vector auxiliar realocat cu 1 mai putin */
	if ( !vector_fii ){ return; }

	for ( i = 0; i < pozitie; i++ ){ vector_fii[i] = a->vector_fii[i]; }    		 /* mut efectiv tot mai putin fiul de pe "pozitie" */
	for ( i = pozitie + 1; i < a->nr_fii; i++ ){ vector_fii[i - 1] = a->vector_fii[i]; }

	free( a->vector_fii );        /* eliberez vechiul vector */
	a->vector_fii = vector_fii;   /* reinitializez vectorul */
	a->nr_fii--;                  /* decrementez numarul curent de fii */
} 


int delete(TArb a, char litera)   /* sterge toate nodurile necesare unei codificari si returneaza 1 pe succes si 0 altfel */
{
	TArb nod, anterior, aux;
	int i;

	anterior = nod = Gaseste( a, litera );      /* plec de la nodul ce contine litera pe care o caut */
	if ( !nod ){ return 0; }                                 /* daca nu gasesc nu fac nimic */

	if ( nod->nr_fii )                         /* daca are fii, pur si simplu nu pot sterge, deoarece as ruina codificarile literelor de desubtul acestui nod */
	{ 
		nod->litera = '\0';
		return 1; 
	}

	while ( ( nod->parinte->parinte != NULL ) && ( nod->parinte->nr_fii <= 1 ) && ( !nod->parinte->litera ) )   /* cat timp pot sa urc in arbore, dar lasand ultimul nod de sters liber */
	{
		anterior = nod;                                   /* retin mereu anteriorul pentru eliberare de memeorie */
		nod = nod->parinte;      						  /* urc in parinte */

		if ( anterior->vector_fii ){ free( anterior->vector_fii ); } /* daca vectorul de vii puncteaza catre o zona de memorie, il eliberez */
		free( anterior );											 /* eliberez memoria pentru nodul anterior propriu-zis */
	}		

	anterior = nod;                      /* am ajuns la ultimul nod de eliberat si la parintele acestuia */
	nod = nod->parinte;

	for ( i = 0 ; i < nod->nr_fii; i++ )          /* caut in nod fiul care trebuie sters in vectorul de fii pentru a sti ce fii sa introduc in vectorul realocat */
	{
		if ( nod->vector_fii[i] == anterior ){ break; } /* cand il gasesc ma opresc */
	}

	Realoca( nod, i );     /* realoc vectorul de fii, stergnd fiul de pe pozitia "i" */

	if ( anterior->vector_fii ){ free( anterior->vector_fii ); }     /* eliberez pe "anterior" ca mai sus */
	free( anterior );                                               /* eliberez memoria pentru ultimul nod ce trebuia sters */
}


char ConstrArb(TArb *a, FILE *intrare, FILE *iesire)            /* construieste arborele de codificari pe baza comenzilor primite din fisierul de intrare */
{
	int i, nr;
	char *buffer, *separatori = " \n", separator;

	buffer = calloc( sizeof( char ), MIN + 1 );
	if ( buffer == NULL ){ return '\0'; }

	*a = ConstrFr();                               /* construiesc o frunza goala, care este chiar radacina rborelui */
	if ( !( *a ) )
	{
		free( buffer );
		return '\0';
	}

	nr = atoi ( fgets( buffer, MIN, intrare ) );  /* citesc numarul de litere de adaugat si il conveertesc la tipul "int" */

	for ( i = 0; i < nr; i++ )                   /* citesc cele "nr" litere si codificarile lor si construiesc arborele */
	{
		fgets( buffer, MIN, intrare );
		add( *a, buffer );                   /* apelez functia add care imi introduce o litera in arbore pe baza codificarii acesteia */
	}

	fgets( buffer, MIN, intrare );              /* citesc separatorul folosit la decodificare, acesta fiin primul caracter de pe acea linie */
	separator = buffer[0];
	
	fgets( buffer, MIN, intrare ); 		   /* sar numarul de operatii, deoarece nu am nevoie de el, deoarece voi efectua operatii cat timp le mai pot citi din fisier */
	AfiArb( *a, iesire );

	while ( fgets( buffer, MIN, intrare ) )                 /* citesc pana la capatul fisierului operatiile de efectuat pe arbore */
	{
		if ( strncmp( buffer, "add", NCMP ) == 0 )      /* daca primele "NCMP = 3" caractere din comanda sunt "add" insemna ca trebuie sa adaug codificare noua si verific daca deja exista una cu ajutorul functiei "delete" */ 
		{ 
			delete( *a, buffer[4] ); 		/* prin functia "delete" verific si daca exista o codificare existenta a literei */
			add( *a, buffer + 4 ); 			/* comanda de interes este dupa sirul de caractere "add" */                      
		}
		else{ delete( *a, buffer[7] ); }     /* sterg litera */
		
		AfiArb( *a, iesire );			/* afisez arborele dupa fiecare operatie */
	}

	free( buffer );

	return separator;			/* returnez separatorul pe care il voi folosi la decodificare */
}


char DecodificareLitera(TArb a, char *cod)     /* decodifica o litera pe baza unui cod dat ca parametru in arbore */
{
	int i, j, lungime_cod;

	lungime_cod = strlen( cod );

	for ( i = 0; i < lungime_cod; i++ )       /* parcurg sirul de caractere */
	{
		for ( j = 0; j < a->nr_fii; j++ )          /* parcurg vectorul de fii */
		{ 
			if ( a->vector_fii[j]->caracter == cod[i] )     /* daca am gasit fiul in care sa cobor, ma duc pe acesta si ma opresc */
			{
				a = a->vector_fii[j];	               /* cobor in arbore pe fiul gasit */
				break; 
			}
		}
	}

	return a->litera; 			/* returnez litera gasita */
}


void Decodificare(TArb a, char separator, FILE *intrare, FILE *iesire)    /* decodifica un text din fisierul de intrare si il rescrie in format clar in fisierul de iesire */
{
	char *buffer, *separatori, *cod, litera, *aux;
	
	buffer = calloc( sizeof( char ), MAX + 1 );                   /* aloca o zona de memorie in care voi citi */
	if ( !buffer ){ return; }

	separatori = calloc( sizeof( char ), 3 );
	if ( !separatori )
	{
		free( buffer ); 
		return; 
	}

	separatori[0] = separator;
	separatori[1] = '\n';
	
	while ( fgets( buffer, MAX, intrare ) )        /* cat timp pot citi din fisier */
	{
		cod = strtok( buffer, separatori );         /* iau cod cu cod, in text clar insemnand litera cu litera */

		while ( cod != NULL )                      /* cat timp nu ajung la capatul liniei ce contine text codificat */
		{
			if ( cod[0] == ' ' )		/* daca codul incepe cu " ", afisez spatiul in fisierul de iesire si decodific codul fara primul caracter */
			{ 
				fprintf( iesire, " " );
				litera = DecodificareLitera( a, cod + 1 );		/* decodific litera si o afisez */
				fprintf( iesire, "%c", litera );
			}
			else                                                           /* daca nu e spatiu il decodific */
			{
				litera = DecodificareLitera( a, cod );			/* decodific litera si o afisez */
				fprintf( iesire, "%c", litera );
		  	}

		  	cod = strtok( NULL, separatori );                          /* trec la umatoarea bucata din cod */
		}

		fprintf( iesire, "\n" );
	}

	free( separatori );
	free( buffer );                               
}


void Start(char *intrare_cod, char *intrare_text, char *iesire_arbore, char *iesire_text)
{
	FILE *intc, *intt, *ia, *iest;
	TArb arbore;
	char separator;

	if ( ( !intrare_cod ) || ( !intrare_text ) || ( !iesire_arbore ) || ( !iesire_text ) ){ return; }
	
	intc = fopen( intrare_cod, "r" );
	if ( !intc ){ return; }

	intt = fopen( intrare_text, "r" );
	if ( !intt )
	{
		fclose( intc );
		return;
	}

	ia = fopen( iesire_arbore, "w" );
	if ( !ia )
	{
		fclose( intc );
		fclose( intt );
		return;
	}

	iest = fopen( iesire_text, "w" );
	if ( !iest )
	{
		fclose( intc );
		fclose( intt );
		fclose( ia );
		return;
	}
	
	separator = ConstrArb( &arbore, intc, ia );		/* aflu separatorul si construiesc arborele */
	Decodificare( arbore, separator, intt, iest );		/* decodific textul codificat */
	
	DistrArb( &arbore );					/* eliberez toata memoria alocata pentru citiri si arbore */
	fclose( intc );
	fclose( intt );
	fclose( ia );
	fclose( iest );
}
