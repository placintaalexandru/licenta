/* Placinta Alexandru - 314CB */

#include "header.h"


int main( int argc, char *argv[] )
{
	FILE *intrare = fopen( argv[2], "r" ); /* deschid fisierulde input pentru citire, calea lui fiind data de argumentul de pe pozitia 2 */
	FILE *iesire = fopen( argv[3], "w");   /* creez un nou fisier de output, calea lui fiind data de rgumentul de pe pozitia 3 */
	TH *tab_hash;
	int M = atoi( argv[1] ); /* argumentul de pe pozitia 1 este M, pe care il convertesc la numar din sir de caractere cu functia atoi */

	tab_hash = IniTH( M, Functie_Hash );  /* aloc tabela hash cu functia de alocare de la alaborator, deoarece ni s- a permis folosirea ei in tema */
	Start( intrare, iesire, &tab_hash );  /* dau drumul la rulearea fucntiilor in ordinea specificata de fisierul de incput */
	StergeTabelaG( &tab_hash );   /* eleberez spatiul alocat pentru tabela hash pe tot parcursul programului */

	fclose( intrare );  /* inchid cele 2 stream-uri, citire si scriere */
	fclose( iesire );

	return 0;
}

/* Checker- ul local imi afiseaza, la fel ca si cel de pe https://vmchecker.cs.pub.ro/ui/#SDCB, valoarea de 105 puncte */ 