/* Placinta Alexandru - 314CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


#define MAX 500  /* dimensiune pe care o folosesc pentru a alocoa o zona de memorie in care citesc instructiunile din fisier */

typedef int (*TFHash)(void *, int);
typedef int (*TFCmp)(void *, void *);


typedef struct celulag
{ 
	void *info;                  /* adresa informatie */
	struct celulag *urm, *pre;   /* adresa urmatoarei celule */
} TCelulaG, *TLG, **ALG;             /* tipurile Celula, Lista si Adresa_Lista */


typedef struct
{
	size_t M, Celule_curente;    /* numarul de elemente din vectorul de pointeri si, pentru a economisi timp la rulare, am adaugat un camp care retine nuamrul de celule curente */
	TFHash fh;   /* functia hash */
	TLG *v;      /* vectorul de pointeri al carui elemente puncteaza catre primul element di fiecare lista sau catre NULL daca lista repsectiva e vida */
} TH;


typedef struct    /* definirea structurii in care sunt stocate Key, Value si Frequency */
{
	char *Key, *Value;
	int Frequency;
} TSite;


int Suma_elemente(char *sir)  /* calculeaza suma caracterelor ce fac parte din sirul sir */
{
	int i, suma = 0, lungime_sir = strlen(sir);   /* am initializat lungime_sir cu strlen(sir) pentru a nu mai calcula la fiecare iteratie strlen(sir) */

   	for (i = 0; i < lungime_sir; i++){ suma += sir[i]; } /* parcurg intregul sir de caractere si adun propriu-zis valoarea in codul ASCII a caracterului de pe pozitia i */
 	return suma;     /* returnez suma calculata mai sus */
}


int Functie_Hash(void *Key, int Nr_elemente)   /* functia primeste ca parametri un void pointer si numarul curent de elemente din vectorul de pointeri */
{
	char *cheie = (char *)Key;   /* accesez campul Key din facand cast de la void pinter la TSite pointer */
	int suma;

 	suma = Suma_elemente( cheie );    /* calculez suma caracterelor din care e compus Key */
	return ( suma % Nr_elemente );    /* returnez pozitia listei din care face parte Key, adica restul impartirii sumei de mai sus la numarul curent de elemente */
}


TH *IniTH(size_t M, TFHash fh)  /* functia de initializare a unei tabele hash, preluata din laborator, deoarece ni s-a permis acest lucru */
{
	TH*h = (TH*)calloc(sizeof(TH), 1);
	if (!h) 
	{	
		printf("eroare alocare hash\n");
		return NULL;
	}

	h->v=(TLG*)calloc(M, sizeof(TLG));
	if(!h->v)
	{
		printf("eroare alocare vector de pointeri TLG in hash\n");
		free(h);
		return NULL;
	}

	h->M = M;
	h->fh = fh;
	return h;
}


int Functie_Cmp(void *cel1, void *cel2)      /* realizeaza compararea a 2 elemente din lista si in caz de pozitiva inserez inaintea lui cel2 pe cel1 */
{
	TLG c1 = (TLG)cel1, c2 = (TLG)cel2;      /* fac cast la tipul TLG a celor 2 pointeri care puncteaza catre 2 celule */
	TSite *s1 = (TSite *)(c1->info), *s2 = (TSite *)(c2->info);      /* fac cast celor 2 pointeri la tipul TSite pointer, pentru a accesa campul Key si Frequency necesare ordonarii*/
	
	if ( s1->Frequency == s2->Frequency ){ return ( strcmp( s2->Key, s1->Key ) ); }  /* apelez in inserare cat timp e negativa functia; la s1 pun elementul de inserat */
	return ( s1->Frequency - s2->Frequency );	
}


int LungimeLG(ALG a)      /* numarul de elemente din lista */
{ 
	int lg = 0;           /* initializez lungimea listei cu 0 */
	TLG p = *a;           /* inceputl listei, celula de inceput */
	if ( p == NULL ){ return 0; } /* inseamna ca lista este vida */
	else{ lg++; }                 /* daca se intra pe else inseamna ca lista dublu inlantuita circulara contine cel putin un element */   

	for (p = p->urm; p != *a; p = p->urm) { lg++; } /* parcurg lista de la al 2 lea element cat timp celula la care ma aflu este diferita de prima celula */
	return lg;  /*returnez numarul de celule din lista */
}


void AfisareCelulaG(TLG cel)          /* afiseaza continutul din camplu info din celula */
{
	TSite *informatie = (TSite *)(cel->info);  /* fac cast void pointer-ului info din celula la tipul TSite pointer pentru a accesa cele 3 campuri ce le voi afisa mai jos */ 

	printf("%s\n", informatie->Key);       /* afiseaza continutul campului info din toate celulele din lista */
	printf("%s\n", informatie->Value);
	printf("%d\n", informatie->Frequency);    
}      /* OBS: am folosit aceasta functie mai mult pentru debugging, pentru a vedea daca functiile set( daca se insereaza ok) si  get ( daca imi rupea celula din lista si o insera orodnat cum trebuie) */


void AfisareListaG(ALG l)   /* OBS: afiseaza toata lista; aceasta functie am folosit-o  la debugging, mai exact pentru a vedea daca dupa inserarea ordonata continutul listei se afisa in ordinea corecta */  
{
	TLG p;

	if ( ( *l ) != NULL )  /* daca lista este nevida */   
	{
		AfisareCelulaG( *l );
		for ( p = (*l)->urm; p != *l; p = p->urm){ AfisareCelulaG( p ); }
	}
}


void Afisare_tabela(TH *tab_hash)  /*afiseaza tabela cu pozita fiecarei liste si lista repsectiva */
{
	int i;
	TLG l;    /* are rol de inceput de lista de pe pozitia i, cum se va vedea 5 randuri mai jos */

	for (i = 0; i < tab_hash->M; i++)  /* parcurg vectorul de pointeri ce puncteaza catre inceputul fiecarei celule */
	{
		printf("Lista %d:\n", i);  /* afisez pozitia listei in tabela */
		l = tab_hash->v[i];        /* inceputul listei respective */                 
		AfisareListaG( &l );  /* afisez lista de la pozitia i spre care puncteaza pointerul din vectorul de pointeri */
	}    /* OBS: aceasta functie am folosit-o la debugging pentru a vedea cu exactitate continutul tabelei hash */
}


TLG AlocCelulaG(char *Key, char *Value)                /* aloca memorie pentru o celula din lista dublu inlantuita generica */
{
	TLG celula;   /* pointer ce va ouncta catre o zona de memorie in care vor fi alocate elementele unei celule */
	TSite *informatie;   

	celula = (TLG)malloc( sizeof( TCelulaG ) );   /* aloc spatiu pentru celula propriu-zisa */
	if ( !celula ){ return NULL; }				      /* verifica daca alocarea s-a efectuat cu succes, iar in caz intorc NULL */
	                                              

	celula->info = calloc( sizeof(TSite), 1 );      /* aloc saptiu pentru pointer-ul ce puncteaza catre zona de memorie ce contine informatia din celula */
	if ( !celula->info )                          /* verific daca alocarea s-a efectuat cu succes, iar in caz contrar eliberez spatiul pentru celula si intorc NULL */
	{
		free(celula);     /* daca alocarea esueaza eleberez spatiul pentru celula propriu-zisa */                      
		return NULL;      /* si intorc NULL */
	}

	celula->pre = celula;  /* fac ca campurile urm si pre sa puncteze tot la celula pentru cazul in care aceasta va fi singura celula din lista in care va fi inserata */
	celula->urm = celula;  

	informatie = (TSite *)(celula->info); 
	informatie->Key = strdup(Key);   /* aloc exact cat trebuie pentru campul Key si copiez informatia Key in campul info din celula alocata mai sus */
	informatie->Value = strdup(Value);   /* aloc exact cat trebuie pentru campul Value si copiez informatia Key in campul info din celula alocata mai sus */
	
	return celula;			     /* intorc celula prelucrata mai sus */	
}


void StergeCelulaG(ALG celula)           /* elibereaza spatiu alocat pentru o celula si o face sa puncteze catre NULL */
{
	TSite *informatie = (TSite *)( ( *celula )->info ); /* fac cast la tipul TSite pointer a void pointer-ului info pentru a putea accesa cele 2 campuri ce necesita eliberare, Key si Value*/ 
	
	free( informatie->Key );  /* eliberez memeoria alocata pentru Key */
	free( informatie->Value );/* eliberez memeoria alocata pentru Key */
	free( (*celula)->info );  /* eliberez zona de memeorie spre care puncta void pointer-ul info */
	free( *celula );		 /* eliberez spatiul de memorie alocat pentru celula propriu-zisa */

	( *celula ) = NULL;   /* fac ca pointer-ul initial sa punctele la NULL */
}     /* aceasta functia o folosesc la eliberarea spatiului total alocat pe toata durata programului */


void StergeListaG(ALG lista)    /* elibereaza toata memoria alocata pentru celulele unei liste */
{
	TLG p = ( *lista )->urm, aux;   /* incep parcurgearea de la a 2 celula si o eliberez cat timp e diferita de prima( conditia de orpire) */

	while ( p != ( *lista ) )
	{
		aux = p; /* retin intr-un auxiliar adresa celulei curente */
		p = p->urm;  /* trec la celula urmatoare */
		StergeCelulaG( &aux );  /* eliberez spatiul alocat pentru celula curenta */
	}

	StergeCelulaG( lista );  /* tratez separat stergerea primei celule din lista si fac lista vida */
}


void StergeTabelaG(TH **tab_hash)   /* elibereaza spatiul alocat pentru o tabela hash pe toata durata programului */
{
	int i;

	for ( i = 0; i < ( *tab_hash )->M; i++ )  /* parcurg fiecare pointer din vectorul de pointeri care puncteaza catre o prima celula dintr-o lista, sau NULL daca lista e vida */
	{ 
		if ( ( *tab_hash )->v[i] != NULL ){ StergeListaG( &( ( *tab_hash )->v[i] ) ); }  /* folosesc functia de stergere a unei liste pentru a sterge lista de pe pozitia i */
	}

	free( ( *tab_hash )->v ); /* eleberez memoria alocata pentru vectorul de pointer */
	free( *tab_hash );        /* eliberez zona de memorie care continea alocarea structurii tabelei hash */
	( *tab_hash ) = NULL;     /* fac pointer-ul ce puncta spre zona de memorie in care era alocata structura tabelei hash sa puncteze acum catre NULL */
}


TLG Verifica_existenta(char *Key, TH *tab_hash)  /* verifica daca in tabela tab_hash se afla vreo celula a carei informatie contine pe key si in caz in care exista intorc pointer catre celula aceea */
{
	int pozitie;
	TLG l, p; /* pointeri ce ii voi folosi la parcurgerea listei */
	TSite *informatie;

	pozitie = tab_hash->fh( (void *)Key, tab_hash->M );   /* gasesc pozitia in tabela hash */
	l = tab_hash->v[pozitie];    /* inceputul listei de pe pzoitia i */

	if (l == NULL){ return NULL; }  /* verific daca lista este vida, in acest caz e clar ca Key nu se gaseste, deci introc NULL */

	informatie = (TSite *)(l->info);            /* accesez campul info din prima celula din lista */
	if ( strcmp( Key, informatie->Key ) == 0 ){ return l; }  /* verific existenta in prima celula din lista si daca exista intorc adresa celulei pentru o eventuala folosire a acesteia */
	
	for ( p = l->urm; p != l; p = p->urm )      /* parcurg lista cat timp adrsa celulei curente est diferita de adresa primei celule din lista */
	{
		informatie = (TSite *)(p->info);    /* accesez campul info din celula curenta */
		if ( strcmp( Key, informatie->Key ) == 0 ){ return p; }  /* veirific daca informatia ccontinuta il contine pe Key si intorcadresa celului respective */
	}

	return NULL; /* daca in cazurile de mai sus nu s-a returnat nimic, este evident ca Keynu exista in lista, deci intorc NULL */		
}


void Inserare_ordonata(TLG element, ALG lista, TFCmp fcmp) /* realizeaza inserarea ordonata a unei celule intr-o lista deja ordonata pe baza functie fcmp */
{
	TLG inceput = (*lista), l;

	if ( inceput == NULL ){ *lista = element; }  /* daca lista e vida, inserez simplu celula, aceasta fiind noul inceput al lsitei */
	else if ( fcmp( (void *)element, (void *)inceput ) > 0 )    /* inseamna ca inserez la inceputul listei */
	{
		element->urm = inceput;
		element->pre = inceput->pre;
		(*lista)->pre->urm = element;
		(*lista)->pre = element;
		(*lista) = element;  /* modific adresa de inceput a primei celule */
	}  
	else
	{
		for ( l = inceput->urm; l != inceput && fcmp( (void *)element, (void *)l ) < 0; l = l->urm);   /* parcurg lista cat timp nu trebuie sa inserez */
		
		if ( l == inceput )      /* inseamna ca s-a parcurs toata lista si trebuia inserat de fapt la capatul listei */
		{
			element->urm = (*lista);    /* leg celula element la lista */
			element->pre = (*lista)->pre;
			(*lista)->pre->urm = element;
			(*lista)->pre = element; 
		}
		else  /* altfel, inseamna ca inserez pe "undeva" in lista, nestiind mai exact unde, dar nici la coada listei nici la inceputul listei */
		{
			element->pre = l->pre;  /* leg celula element la lista prin modificarea pinterilor urm si pre din celula element si din celula urmatoare si anterioara */
			element->urm = l;
			l->pre->urm = element;
			l->pre = element;
		} 
	} 
}


void Muta(TLG element, TH *tab_hash, TLG *aux, TFCmp fcmp)  /* in caz de ralocare a tabelei hash, aceasta functie va restabili noua pozitie a fiecarei celule si o va insera ordonat in noua tabela aux*/
{
	int pozitie;
	TLG lista;
	TSite *informatie = (TSite *)(element->info);

	pozitie = tab_hash->fh( (void *)(informatie->Key), tab_hash->M ); /* determin pozitia listei din care face parte celula ce contine pe Key */
	
	if ( aux[pozitie] == NULL )    /* daca noua lista de pe pozitia pozitie este vida, inserez fix pe prima pozitie si campurile urm si pre vor din prima celula vor puncta catre celula respectiva */
	{
		element->pre->urm = element->urm;  /* rup celula element din vechea lista si refac legaturile dintre celula anterioara si urmatoare a celulei element */
		element->urm->pre = element->pre;

		aux[pozitie] = element; /* daca lista noua este vida inserez cellula element ca si icneput de lista si campurile urm si pre dincelula vor puncta tot la ea */
		element->pre = element;
		element->urm = element;
	}
	else        /* altfel, inseamna ca lista nu este vida si trebuie sa efectuez inserarea ordonata */       
	{
		lista = aux[pozitie];      /* inceputul listei de pe pozitia i */
		Inserare_ordonata( element, &lista, fcmp ); /* efectuez inserarea ordonata */
		aux[pozitie] = lista; /* poate in unele cazuri, in urma inserari ordonate se modifica lista, asa ca fac pointerul de pe pozitia i din nou vector de pointeri sa puncteze catre inceputul de lista */
	}
}


void Realoca(TH *tab_hash) /* aceasta functie realizeaza realocarea tabelei hash in caz ca numarul de celule curente este mai mare decat 2 * M */
{
	TLG *aux, lista, p, element;
	int i;
	
	aux = ( TLG * )calloc( sizeof( TLG ), 2 * tab_hash->M );

	if ( aux != NULL )      /* alocarea a avut succes, deci voi incepe modificarile asupra vectorlui de pointeri din tabela hash si voi dubla numarul de pointeri din tabela */
	{
		tab_hash->M *= 2; /* dublez nuamrul de elemente */     

		for ( i = 0; i < ( tab_hash->M ) / 2; i++ )  /* parcurg vechea tabela hash si toate listel acesteia si mut fiecare celula in noua tabela */
		{
			if ( tab_hash->v[i] != NULL )  /* inseamna ca lista contine celule */
			{
				lista = tab_hash->v[i];  /* inceputul liste de pe pozitia i */
				p = lista->urm;    /* a 2 a celula din lista */
			
				while ( p != lista )   /* lista are cel putin 2 elemente si parcurg cat timp celula curenta este diferita de pri a celula */
				{
					element = p;
					p->pre->urm = p->urm;  /* rup celula de lista */
					p->urm->pre = p->pre;
					p = p->urm; /* trec la celula urmatoare */
					Muta(element, tab_hash, aux, Functie_Cmp); /* mut celula in noua lista */
				}

				Muta( lista, tab_hash, aux, Functie_Cmp );  /* tartez separat mutarea primei celule din lista */
			}
		}
	}
		 
	free( tab_hash->v ); /* eliberez spatiu alocat pentru vechea tabela hash */
	tab_hash->v = aux; /* reinitializez noua tebela */
}


void set(char *Key, char *Value, TH *tab_hash)  /* aloca o celula ce contine pe Key si Value si intializeaza pe Frequency cu 0 */
{
	int pozitie;
	TLG exista, celula, l, aux;

	exista = Verifica_existenta(Key, tab_hash);  /* verific daca Key exista deja */
	
	if ( exista == NULL )       /* Key nu exista in tabela */     
	{
		celula = AlocCelulaG(Key, Value);  /* aloc o celula ce contine Key, Value, iar Frequency va fi initializat automat pe 0 */
		if ( celula != NULL )
		{
			if ( tab_hash->Celule_curente > 2 * tab_hash->M )        /* inseamna ca numarul de elemente din tabela depaseste 2 * M si voi realoca tabela de pointeri la 2 * M elemente */
			{ 
				Realoca( tab_hash );  /* realizez reloacarea tabelei hash */
			} 

			pozitie = tab_hash->fh( (void *)Key, tab_hash->M); /* numarul listei in care ar trebui inserata celula */
			l = tab_hash->v[pozitie];  /*inceputl listei de pe pozitia pozitie */

			if ( l == NULL ){ tab_hash->v[pozitie] = celula; } /* daca lista e vida inserez propriu-zis ccelula ca noul inceput al listei */
			else
			{
				if ( LungimeLG( &l ) >= tab_hash->M )   /* numarul de celule din lista este mai mare sau egal cu M, deci trebuie sa sterg ultima celula din lista */
				{
					( tab_hash->Celule_curente )--;  /* decrementez numarul de celule curente */

					if ( l->pre == l )   /* era o lista doar cu o celula */
					{
						tab_hash->v[pozitie] = NULL; /* fac ca lista sa devina vida */
						StergeCelulaG( &l ); /* sterg celula de inceput a listei */
					}
					else                    /* exista cel putin 2 elemente in lista respectiva */
					{
						aux = l->pre;      /* accesez utlima celula din lista prin campul pre al primei celule din lista */
						l->pre->pre->urm = l; /* refac legaturile intre celule, iar legaturile dintre celula aux si lista vor fi rupte in cand voi sterge celula din lista, 2 randuri mai jos */
						l->pre = aux->pre;
						StergeCelulaG( &aux ); /* sterg celula curenta din lista */
					}
				}
				
				if ( l == NULL ){ tab_hash->v[pozitie] = celula; }  /* exista posibiliatatea ca dupa stergere lista sa fie vida, asa ca voi aduga celula element a noul inceput al listei */
				else
				{	
					Inserare_ordonata(celula, &l, Functie_Cmp); /* eectuez inserarea ordonata, in cazul in care lista nu e vida, cum se poate observa si din cod */
					tab_hash->v[pozitie] = l; /* pointerul va puncta catre noul cap de lista, in caz ca se modifica */
				}
			}

			( tab_hash->Celule_curente )++; /* incrementez numarul de celule curente */
		}
	}
}


char *get(char *Key, TH *tab_hash, FILE *iesire) /* afiseaza valoarea Value a celulei ce il contine pe Key din tabela hash, il incrementeaza pe Frequency, rupe celula din lista si o reinsereaza ordonat */
{
	TLG l, inceput, n = NULL;
	TSite *informatie;
	int pozitie;  /* va reprezenta pozita in tabela a listei in care se gaseste celula, in caz ca aceasta exista in tabela hash */

	l = Verifica_existenta( (void *)Key, tab_hash ); /* verifica daca celula ce il contine pe Key exista sau nu in lista */ 

	if ( l == NULL )                    /* celula ce il contine pe Key nu exista, deci returnez NULL si scriu si in fisier tot NULL */
	{ 
		fprintf( iesire, "NULL\n" );
		return NULL; 
	}       
	else  /* altfel, inseamna ca celula exista deja in lista */
	{
		informatie = (TSite *)(l->info);  /* pentru a accesa campul Frequency de care am nevoie pentru a rupe celula si a o reinsera ordonat, fac cast void pointerului la tipul TSite pointer */
		( informatie->Frequency )++; /* incrementez pe Frequency */

		pozitie = tab_hash->fh( (void *)Key, tab_hash->M ); /* obtin pozita listei din care face parte celula cu ajutorul functiei hash a tabelel */
		inceput = tab_hash->v[pozitie];  /* inceputul listei de la pozitia pozitie */

		if ( ( inceput->urm != inceput ) && ( l != inceput ) )  /* daca sunt cel putin 2 elemente si celula de reinserat nu e prima din lista rup celula gasita din lista si o voi insera ordonat */
		{
			l->pre->urm = l->urm;  /* rup celula din lista, legaturile urm si pre ramanand neatinse si le voi modifica atnci cand voi insera ordonat l Inserare_ordonata(l, &inceput, Functie_Cmp) */			l->urm->pre = l->pre;

			Inserare_ordonata( l, &inceput, Functie_Cmp );
			tab_hash->v[pozitie] = inceput;  /* pointerul de pe pozitia pozitie din vectorul de pointeri va puncta catre noul inceput al liste, daca acesta a fost modificat */
		}
	}

	fprintf( iesire, "%s\n", informatie->Value ); /* printez in fisier pe Value din celula ce il contine pe Key */
	return ( informatie->Value ); /* si returnez si pe Value */
}


void Remove(char *Key, TH *tab_hash)  /* realizeaza stergerea celulei ce il contine pe Key din tabela si reface legaturiel din lista respectiva */
{
	int pozitie;  /* va reprezenta pozita listei din tabela, in caz ca celula ce il contine pe Key exista */
	TLG inceput, l;

	l = Verifica_existenta( Key, tab_hash ); /* verific daca celula ce il contine pe Key exista, iar daca da intorc adresa zone de memorie a celulei respective */

	if ( l != NULL )
	{
		pozitie = tab_hash->fh( (void *)Key, tab_hash->M ); /* pozita listei din care face parte celula */
		inceput = tab_hash->v[pozitie];  /* ineputul listei respective */
		( tab_hash->Celule_curente )--;  /* decrementez numarul de celule urente, deoarece acum efectuez operatia de stergere a unei celule din tabela hash */

		if ( inceput->urm == inceput )  /* inseamna ca celula este singura in lista, deci void sterge celula si voi face ca lista sa fie vida */
		{
			StergeCelulaG( &inceput ); /* eliberez spatiul alocat pentru celula */
			tab_hash->v[pozitie] = NULL; /* fac ca pointer-ul din vectorul de pointeri din tabela care puncta catre inceputul listei de pe pozitia pozitie sa puncteze acum catre NULL */
		}
		else if( ( inceput == l ) && ( inceput->urm != inceput ) ) /* daca celula de sters trebuie stersa, dar lista contine cel putin 2 celule */
		{
			tab_hash->v[pozitie] = inceput->urm;  /* schimb inceputl listei */
			inceput->pre->urm = inceput->urm;     /* refac legaturile */
			StergeCelulaG ( &inceput );    /* eliberez spatiul alocat pentru celula care trebuie stearsa */
		}
		else /*altfel inseamna ca trebuie sa sterg o celula din interiorul listei */
		{
			l->pre->urm = l->urm;  /* rup celula de sters din lista */
			l->urm->pre = l->pre;
			StergeCelulaG ( &l );  /* eliberez spatiul acolcat pentru celula de sters */
		}
	}
}


void print(TH *tab_hash, FILE *iesire) /* afiseaza toate valorile Value din tabela hash */
{
	int i;
	TLG l, p;
	TSite *informatie;   /* va puncta catre zona de memorie in care sunt cele 3 campuri spre care puncta void pointer-ul din celula */

	for ( i = 0; i < tab_hash->M; i++ )  /* parcurg vectroul de pointeri din tabela hash */
	{
		l = tab_hash->v[i];  /* inceputul listei de pe pozitia i */

		if ( l != NULL )  /* eu afisez doar daca lista nu este vida, conform enuntului temei */
		{
			informatie = (TSite *)(l->info);  /* pentru a putea accesa campul Value trebuie sa fac cast la tipul TSite pointer a void pointer-ului */
			fprintf( iesire, "%d: ", i );  /* afisez valoarea Value dupa formatul cerut de tema */
			fprintf( iesire, "(%s)", informatie->Value ); /* tratez separat afisarea Value din prima celula a listei */

			for ( p = l->urm; p != l; p = p->urm ) /* parcurg lista incepand de la a 2a celula din lista cat timp aceasta e diferita de prima celula din lista */
			{
				informatie = (TSite *)p->info;
				fprintf( iesire, " (%s)", informatie->Value );  /* printez in fisier pe Value */
			}

			fprintf( iesire, "\n" ); /* trec la o linie noua */
		}
	}
}


void print_list(int index, TH *tab_hash, FILE *iesire)  /* afiseaza toate valorile Value din lista de pe pozitia index */
{
	TLG l = tab_hash->v[index], p; 
	TSite *informatie;

	if ( l == NULL ){ fprintf( iesire, "%d: VIDA\n", index ); }  /* verific daca lista e vida */
	else /* altfel, lista este necida */
	{
		informatie = (TSite *)(l->info); /* trebuie sa accesez informatia Value si pentru aceasta trebuie sa fac cast */
		fprintf( iesire, "%d: (%s)", index, informatie->Value ); /* tratez separat afisarea lui Value din prima celula a listei */

		for ( p = l->urm; p != l; p = p->urm )  /* parcurg lista si afisez fiecare valoare Value din fiecare lista */
		{
			informatie = (TSite *)(p->info);
			fprintf( iesire, " (%s)", informatie->Value );
		}

		fprintf( iesire, "\n" ); /* trec la linia urmatoare */
	}
	
}


void Start(FILE *intrare, FILE *iesire, TH **h)   /* efectueaza rezolvarea temei, punand impreuna toate functiile implementate mai sus */
{
	TH *tab_hash = ( *h );
	char *buffer, *comanda, *separatori = " \n";

	buffer = calloc( sizeof( char ), MAX ); /* aloc memorie pentru a stoca instructiunea ce o voi citi */

	while ( fgets( buffer, MAX, intrare) != 0 ) /* efectuez operatii in tabela ccat timp pot citi instructiuni din fisierul de input, adica din intrare */
	{
		comanda = strtok( buffer, separatori ); /* comanda reprezinta primul cuvant de pe linia pe care o citesc in buffer */

		if ( strcmp( comanda, "set" ) == 0 )  /* daca comanda este set atunci mai contine icna 2 cuvinte pe care le culeg folosind strtok de NULL se vectorul de separtori, adica separatori */
		{
			char *Key, *Value;

			Key = strtok( NULL, separatori );
			Value = strtok( NULL, separatori );
			set(Key, Value, tab_hash); /* efectuez operatia */
		}

		if( strcmp( comanda, "get" ) == 0 )  /* daca comanda este get, atunci ea este urmata de un cuvant ce il contine pe Key, pe care ilk culeg ca in cazul lui set */
		{
			char *Key;

			Key = strtok( NULL, separatori );
			get(Key, tab_hash, iesire);  /* efectuez operatia */
		}

		if ( strcmp( comanda, "remove" ) == 0 )  /* daca comanda este remove, atunci ea este urmata de un cuvant ce il contine pe Key, pe care ilk culeg ca in cazul lui set */
		{
			char *Key;

			Key = strtok( NULL, separatori );
			Remove( Key, tab_hash ); /* efectuez operatia */
		}

		if ( strcmp( comanda, "print" ) == 0 ){ print( tab_hash, iesire ); } /* daca comanda ete print atunci ea nu e urmata de nimic si efectuez operatia ceruta */

		if ( strcmp ( comanda, "print_list" ) == 0 )   /* daca comanda este print_list, atunci ea e urmata de un cuvant format doar din nuemere */
		{
			char *converite_in_numar;
			int index;

			converite_in_numar = strtok( NULL, separatori ); /* culeg cuvantul ca si in cazul lui set, cu strtok de NULL si vectorul de separatori, separatori */

			index = atoi( converite_in_numar ); /* folosesc functia atoi pentru a converti din sir de caractere in numar pentru a avea acces la indexul propriu-zis */
			if ( ( index < tab_hash->M ) && ( index >= 0 ) ){ print_list( index, tab_hash, iesire ); }	 /* efectuez operatia */	
		}
	}

	free( buffer ); /* eliberez memoria alocata pentru sirul de caractere ce contine insttructiunea */
} 

/* Checker- ul local imi afiseaza, la fel ca si cel de pe https://vmchecker.cs.pub.ro/ui/#SDCB, valoarea de 105 puncte */