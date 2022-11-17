#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <netdb.h>
#include <fcntl.h>

#define MAX_CLIENTS	20
#define TPBUFFER 150000
#define HTTP "http://"
#define WWW "www."
#define HOST "Host"
#define POST "POST"
#define GET "GET"
#define HTTP10 "HTTP"
#define PREFIX "FILE_NO_"
#define NO_CACHE "Cache-Control: no-cache"
#define PRIVATE "Cache-Control: private"

/*
Functie care pe baza unui request extrage numele hostului
pentru ca mai apoi sa fie folosit ca argument functiei
gethostbyname pentru a obtine adresa IP a server-ului
Pentru implementare am considerat 5 cazuri, cand am urmatoarele:
"GET http://", "GET (http://)www.", "GET .. \r\nHOst: numeServer",
"GET (fara http://www.)numeServer" si "POST ...."
Cei de mai sus au fost delimitatori principali folositi de mine,
deoarece aparitia/disparitia lor imi pot indica o adresa de inceput
in calcularea adresei server-ului.
In functie de fiecare caz, retin o adresa de inceput, de unde voi copia
numele si o lungime a acestuia, cat voi copia incepand de la acea adresa.
Pentru a sti cand sa ma opresc iterez prin request pana cand caracterul de
la acea adresa va fi unul din urmataorele: ':', '\r', '\n', '\0' sau '/', in
functie de cazul in care ma aflu cu request-ul.
Pentru cazul cu "http://" acesta va disparea.

@param url - request-ul primit de proxy de la browser
@return poiner catre o zona de memorie unde este alocat
		hostname-ul care va fi folosit ca parametru pentru
		functia gethostbyname pentru a afla IP-ul server-ului
*/
char *getAdressName(char *url) {
	char *startPointer, *clone, *adressName;
	unsigned int adressLength;

	adressLength = 0;

	if ((startPointer = strstr(url, HOST)) != NULL) {
		startPointer += 6;
		clone = startPointer;

		for ( ; startPointer[0] != '\r' && startPointer[0] != '\n' && startPointer[0] != '\0'; startPointer++) {
			adressLength++;
		}
	} else if (((startPointer = strstr(url, WWW)) != NULL) && (startPointer == url + 4)) {
		clone = startPointer;

		for ( ; startPointer[0] != ' ' && startPointer[0] != ':' && startPointer[0] != '/'; startPointer++) {
			adressLength++;
		}
	} else if ((startPointer = strstr(url, HTTP)) != NULL) {
		startPointer += 7;
		clone = startPointer;

		for ( ; startPointer[0] != ' ' && startPointer[0] != ':' && startPointer[0] != '/'; startPointer++) {
			adressLength++;
		}
	} else if ((startPointer = strstr(url, POST)) != NULL) {
		startPointer = url + 5;

		for ( ; startPointer[0] != ' ' && startPointer[0] != ':' && startPointer[0] != '/'; startPointer++) {
			adressLength++;
		}
	} else {
		startPointer = url + 4;

		for (clone = startPointer; clone[0] != '/' && clone[0] != ':'; clone++) {
			adressLength++;
		}

		clone = startPointer;
	}

	adressName = calloc(adressLength + 1, sizeof(char));
	memcpy(adressName, clone, adressLength);
	return adressName;
}

/*
Functie care pe baza unui request creeaza numarul de port aferent,
deoarece unele request-ueimai pot avea asa zise porturi proprii
specificate.
Pentru a realiza acest lucru tot ceea ce fac este sa caut pe prima
linie, pana la prima perecehe \r\n, un subsir care incepe cu ':' si
are dupa el o cifra, iar apoi de la adresa acelei cifre culeg subsirul
pana cand caracterul de la adresa curenta este '/', atunci incepe
adresa resursei dorite.
Cautarea o realizez doar pe prima linie, deoarece in tema a fost
specificat ca nu se va da portul prin parametrul HOST, deci singurul
loc unde poate aparea este pe prima linie.
In aceasta parcurgere retin adresa de inceput de unde voi copia, si
construiesc lungimea IP-ului ca string, dupa care la final copiez
acel subsir intr-un buffer si aplic functia atoi.

@param url - requestul primit de proxy de la browser
@return portul in format numar intreg
*/
int getPort(char *url) {
	char *startPointer,	*endPointer, portAsString[10];
	bool hasCustomPort = false;
	unsigned int portAsStringLen;

	endPointer = strstr(url, HTTP10);
	portAsStringLen = 0;

	for (startPointer = url; startPointer < endPointer; startPointer++) {
		if ((startPointer[0] == ':') && (isdigit(startPointer[1]))) {
			hasCustomPort = true;
			startPointer++;
			endPointer = startPointer;
			break;
		}
	}

	if (!hasCustomPort) {
		return 80;
	}

	for (; startPointer[0] != '/' && startPointer[0] != ' '; startPointer++) {
		portAsStringLen++;
	}

	memset(portAsString, 0, 10);
	memcpy(portAsString, endPointer, portAsStringLen);

	return atoi(portAsString);
}

/*
Functie care pe baza unui request creeaza numele fisierului de cache.
Pentru crearea fisierului de cache am gandit urmatorul lucru, pentru a
putea distinge requsturile cu nume diferite, dar si request-urile cu
acelasi nume, dar care puteau avea porturi diferite: creez un fisier al
carui nume este format din prefixul "FILE_NO_" apoi suma caracterelor
din request, fie ca e relativ ( iau daor adresa paginii in considerare),
fie ca e absolut ( iau si hostname in calcul) si la aceasta suma adaug
valaorea caracterelor, iar la final adaug si "_" urmat de numarul
portului si ".cache", pentru a putea sa sterg toate fisierele cache
existente pana la acel moment la inceperea rularii proxy-ului

@param url - requestul pentru care creez numele fisierului
@return pointer catre o zona de memorie unde este alocat un sir
		de caractere ce contine numele fisierului
*/
char *createFileName(char *url) {
	char *startPointer, *clone, *requestName, *hostName, *fileName;
	unsigned int requestLen, mySum;
	int i, port;

	requestLen = 0;
	hostName = getAdressName(url);

	if (strstr(url, POST) != NULL) {
		startPointer = url + 5;
	} else if (strstr(url, GET) != NULL) {
		startPointer = url + 4;
	}

	clone = startPointer;
	port = getPort(url);

	for ( ; clone[0] != ' '; clone++) {
		requestLen++;
	}

	requestName = calloc(requestLen + 1, sizeof(char));
	memcpy(requestName, startPointer, requestLen);
	mySum = 0;

	for (i = 0; i < strlen(requestName); i++) {
		mySum += requestName[i];
	}

	for (i = 0; i < strlen(hostName); i++) {
		mySum += hostName[i];
	}

	fileName = calloc(1000, sizeof(char));
	memcpy(fileName, PREFIX, 8);
	snprintf(fileName + strlen(fileName), 1000 - strlen(fileName), "%u", mySum);
	strcat(fileName, "_");
	snprintf(fileName + strlen(fileName), 1000 - strlen(fileName), "%d", port);
	strcat(fileName, ".cache");
	free(hostName);
	return fileName;
}

/*
Functie care pe baza unui request si a unui socket,
creeaza o conexiune TCP cu server-ul pentru care este
request-ul respectiv si intoarce rezultatul in urma
conexiunii
Pentru implementare am completat campurile variabilei
"serverAdress" prin folosirea numelui hostului din request,
dar si a portului
La final intorc rezultatul intors de primitiva connect
aplicat pe socket-ul primit ca parametru si variabila
"serverAdress".

@param url - requestul primit de proxy de la browser
@param socket - socket-ul pe care se realizeaza conexiunea TCP
@return rezultatul primitivei connect, pozitiv daca reuseste si
		negativ altfel
*/
int myConnect(char *url, int socket) {
	char *hostName;
	int port;
	struct hostent *he;
	struct in_addr anIpAdress;
	struct sockaddr_in serverAddress;

	hostName = getAdressName(url);
	port = getPort(url);
	he = gethostbyname(hostName);

	if (he == NULL) {
		printf("Host Ent NULL\n");
		free(hostName);
		return -2;
	}

	memcpy(&anIpAdress, he->h_addr_list[0], sizeof(anIpAdress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr = anIpAdress;
	free(hostName);

	return connect(socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

/*
Functie care determina daca un fisier cu numele
precizat exista.
Pentru implementarea functie am folosit functia stat din
biblioteca <sys/stst.h> care preia informatii despre un fisier
si le introduce in structura de tip stat

@param fileName - numele fisierului depsre care doresc sa aflu
		daca exista
@return variabila booleana ce contine valoarea de adevar legata
		de existenta fisierului cu acel nume
*/
bool hasCache(char *fileName) {
	struct stat buffer;

	return (stat(fileName, &buffer) == 0);
}

/*
Functie care realizeaza un request pe care il primeste
prin socket-ul primit ca parametru, iar pentru fiecare
request realizeaza raspunsul fie prin interogarea cache-ului,
fie prin interogarea server-ului.
Pentru implementare am cautat mai intai sa vad daca
cererea mea se afla in cache prin a intreba daca fisierul
aferent request-ului exista deja, caz in care nu creez niciun
socket cu server-ul ci doar citesc din fisier pana la epuizarea
acestuia, iar la fiecare citire scriu pe socket pentru a trimite
browser-ului.
Daca fisierul aferent request-ului nu este creat, atunci daca
trebuie sa cache-uiesc acel request, deoarece unele request-uri
nu trebuiesc cache-uite, spre exemplu cele cu "POST", creez
fisierul aferent request-ului cu numele descris in documentatia
functiei "createFileName".
Dupa ce am realizat conexiunea dintre proxy si serve, trimit
request-ul primit de proxy de la browser server-ului, iar apoi
cat timp primesc raspuns, trimit inapoi la browser si scriu, daca
trebuie, si in fisierul de cache aferent request-ului.

@param fromSocket - socekt-ul de pe care primeste proxy-ul
					request-ul de la browser
@param url - requestu-ul primit de proxy de la browser
@param octetiPrimiti - numarul de octeti primit de proxy de la browser
*/
void makeRequest(int fromSocket, char *url, int octetiPrimiti) {
	int socketToForward, n;
	char *cacheName, *buffer;
	int cache;
	bool toCache = true;
	
	buffer = calloc(TPBUFFER, sizeof(char));
	cacheName = createFileName(url);
	if (hasCache(cacheName)) {
		cache = open(cacheName, O_RDONLY);
		memset(buffer, 0, TPBUFFER);

		while ((n = read(cache, buffer, TPBUFFER)) > 0) {
			send(fromSocket, buffer, n, 0);
			memset(buffer, 0, TPBUFFER);
		}

		close(cache);
		free(cacheName);
		free(buffer);
		return;
	}

	
	if ((strstr(url, NO_CACHE)) || (strstr(url, PRIVATE)) || (strstr(url, POST))) {
		toCache = false;
	} else {
		cache = open(cacheName, O_CREAT | O_WRONLY, 0644);
	}

	socketToForward = socket(AF_INET, SOCK_STREAM, 0);
	if (myConnect(url, socketToForward) < 0) {
		printf("Eroare de conectare\n");
		close(cache);
		close(socketToForward);
		free(cacheName);
		return;
	}
	
	send(socketToForward, url, octetiPrimiti, 0);
	memset(buffer, 0, TPBUFFER);

	while ((n = recv(socketToForward, buffer, TPBUFFER, 0)) > 0) {
		if (toCache) {
			write(cache, buffer, n);
		}
		
		send(fromSocket, buffer, n, 0);
		memset(buffer, 0, TPBUFFER);
	}

	if (toCache) {
		close(cache);
	}
	
	close(socketToForward);
	free(cacheName);
	free(buffer);
}

int main(int argc, char *argv[]) {
	system("exec rm -r *.cache");

	int publicSocket, privateSocket, portno, fdmax;
	socklen_t clilen;
	char buffer[TPBUFFER];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, j, ok = 1;
	fd_set read_fds;
	fd_set tmp_fds;

	if (argc < 2) {
		printf("Usage : %s port\n", argv[0]);
		return -1;
	}

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);
	 
	publicSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (publicSocket < 0) {
	 	printf("Eroare socket TCP\n");
	 	return -1;
	} 

	portno = atoi(argv[1]);
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	 
	setsockopt(publicSocket, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok));
	if (bind(publicSocket, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) {
	 	printf("Eroare bind socket TCP\n");
	 	close(publicSocket);
	 	return -1;
	}
	 
	listen(publicSocket, MAX_CLIENTS);
	FD_SET(publicSocket, &read_fds);
	fdmax = publicSocket;
	
	while (1) {
		tmp_fds = read_fds; 
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) {
			printf("Eroare select\n");

			for (j = 0; j <= fdmax; j++) {
				if (FD_ISSET(j, &tmp_fds)) {
					close(j);
				}
			}
			
			close(publicSocket);
			return -1;
		}
		
		for(i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == publicSocket) {
					clilen = sizeof(cli_addr);

					if ((privateSocket = accept(publicSocket, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
						printf("Eroare acceptare socket privat");

						for (j = 0; j <= fdmax; j++) {
							if (FD_ISSET(j, &tmp_fds)) {
								close(j);
							}
						}

						close(publicSocket);
						return -1;
					}
					else {
						FD_SET(privateSocket, &read_fds);
						fdmax = privateSocket > fdmax ? privateSocket : fdmax;
					}
				} else {
					memset(buffer, 0, TPBUFFER);

					if ((n = recv(i, buffer, TPBUFFER, 0)) <= 0) {
						close(i); 
						FD_CLR(i, &read_fds);
					} else {
						makeRequest(i, buffer, n);
						memset(buffer, 0, TPBUFFER);
						close(i);
						FD_CLR(i, &read_fds);				
					}
				}
			}
		}
	}

	close(publicSocket);
	return 0; 
}