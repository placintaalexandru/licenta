#include "lib.h"
#define PRFIX "recv_"

/*
Creeaza numele unu pachet prefixand primul parametru cu al 2 lea

@param numeFisierInitial - un pointer catre o zona de memorie
							unde este alocat un sir de caractere
							reprezentand numele initial al fisierului
@param prefix - pointer la o zina de memorie unde este alocat un sir de caractere
							ce se va pune inaintea numelui initial la fisierului
*/
char *creeazaNumeRecv(char *numeFisierInitial, char *prefix) {
	char *numeFisier;
	numeFisier = calloc(strlen(numeFisierInitial) + strlen(prefix) + 1, sizeof(char));
	if (numeFisier == NULL) {
		return NULL;
	}

	strcpy(numeFisier, prefix);
	strcat(numeFisier, numeFisierInitial);
	return numeFisier;
}

/*
Deschide un fisier pentru scriere al carui nume este dat
ca parametru si intoarce file descriptorul acestuia, fileId

@param numeFisier - pointer la o zona de memorie
					unde este alocat un sir de caractere ce
					reprezinta numele fisierului
@return file descriptorului fisierului ce s-a deschis
*/
int creeazaFisierOutput(char *numeFisier) {
	int fileId;
	char *numeFisierOutput;

	numeFisierOutput = creeazaNumeRecv(numeFisier, PRFIX);
	fileId = open(numeFisierOutput, O_WRONLY | O_CREAT, 0644);
	free(numeFisierOutput);

	return fileId;
}

/*
Deschide un fisier pentru scriere pornind de la numele
acestuia si intoarce file descriptorul fisierului ce s-a deschis

@param numeFisier - numele fisierului ce se deschide pentru citire
@return - file descriptorul fisierului ce s-a deschis
*/
int deschideFisierSursa(char *numeFisier) {
	int fileId;
	
	fileId =  open(numeFisier, O_RDONLY);
	return fileId;
}

/*
Elibereaza memoria alocata pentru pointer-ul de pointeri si
cea folosita pentru alocarea structurilor

@param pachete - pointer-ul de pointeri ce puncteaza la zonele
					de memorie unde sunt alocate structurile
@param numarPachete - numarul de structuri alocate
*/
void elibereaza(MiniKermitPacket **pachete, int numarPachete) {
	for (int i = 0; i < numarPachete; i++) {
		free(pachete[i]);
	}

	free(pachete);
}