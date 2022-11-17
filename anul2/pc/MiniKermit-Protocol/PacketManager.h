#include "lib.h"

/*
Aplica CRC-ul pe campurile pachetului, in afara de MARK
Pentru acest lucru, liniarizez structura, copiind totul intr-un (void *)
ce reprezinta campurile din structura liniarizate, iar pe structura
liniarizata aplic CRC-ul
La final eliberez zona de memorie alocata aferenta acelui pointer auxiliar

@param kermiPacket - un pointer catre o zona de memorie unde
						este alocata o zona de memorie pentru un pachet
@param lungimeData - numarul de octeti din campul data al pachetului
@return - codul CRC aferent pachetului
*/
unsigned short getCRC(MiniKermitPacket *kermitPacket, int lungimeData) {
	void *secventa;
	unsigned short crc;

	secventa = calloc(4 + lungimeData, sizeof(char));
	if (secventa == NULL) {
		return -1;
	}

	memcpy(secventa, &(kermitPacket->soh), 1);
	memcpy(secventa + 1, &(kermitPacket->len), 1);
	memcpy(secventa + 2, &(kermitPacket->seq), 1);
	memcpy(secventa + 3, &(kermitPacket->type), 1);
	memcpy(secventa + 4, kermitPacket->data, lungimeData);

	crc = crc16_ccitt(secventa, 4 + lungimeData);
	free(secventa);
	return crc;
}

/*
Creeaza un pachet Kermit, in functie de tipul ales ca parametru
Aloc spatiu pentru un pachet, iar apoi completez campurile
pe care toate pachetele le au in comun

@param type - tipul pachetului care se creeaza
@return - un pointer catre zona de memorie unde 
			a fost alocat pachetul
*/
MiniKermitPacket *creeazaKermitPacket(char type) {
	MiniKermitPacket *kermitPacket;

	kermitPacket = calloc(1, sizeof(MiniKermitPacket));
	if (kermitPacket == NULL) {
		return NULL;
	}

	kermitPacket->soh = SOH;
	kermitPacket->type = type;
	kermitPacket->len = 5;
	kermitPacket->mark = EOL;
	return kermitPacket;
}

/*
Modifica un pachet pentru a nu mai aloca alt spatiu, pornin de
la un pointer ce retine zona de memorie unde este alocat spatiu pentru
o structura de tip MiniKermitPacket
Mai intai curat zona de date din pachet folosind memset cu valaorea 0,
pentru a evita "resturi" din alte trimiteri, apoi actualizez
corespunzator campurile structurii

@param kermitPacket - pointer-ul ce contine zona de memorie
						unde este alocat pachetul ce se va modifica
@param data - pointer catre zona de memorie ce contine datele ce se vor
				a fi trimise
@param data - numarul de octeti cititi, folosesc acest camp pentru ca in cazul datelor binare
				nu se poate aplica strlen
@param numarSecventa - numarul de secventa aferent pachetului

*/
void modificaPacketD(MiniKermitPacket *kermitPacket, char *data, unsigned int lungimeData, char numarSecventa) {
	unsigned short crc;

	memset(kermitPacket->data, 0, MAXL);
	kermitPacket->len = 5 + lungimeData;
	kermitPacket->seq = numarSecventa;
	if (lungimeData) {
		memcpy(kermitPacket->data, data, lungimeData);
	}
	
	crc = getCRC(kermitPacket, lungimeData);
	kermitPacket->check = crc;
}

/*
Introduce datele dintr-un pachet in payload-ul mesajului,
actualizand campul len din mesaj si copiind informatia din data
doar daca pachetul are lungimea strict mai mare decat 5, deoarece
lungimea uni pachet este 5 + numarul de octeti din campul data
Mai intai curat payload-ul de eventualele "ramasite" datorate altor
trimiteri, iar apoi copiez camp cu camp, deoarece prin structura mai pot
aparea octeti de padding, intentia fiind aceea de a-i evita

@param mesaj - adresa unei variabile de tip msg, folosita pentru a trimite mesaje
@param kermitPacket - un pointer la o structura de tip MiniKermitPacket care contine
						datele ce se doresc a fi transmise
*/
void punePacketDateInMesaj(msg *mesaj, MiniKermitPacket *kermitPacket) {
	memset(mesaj->payload, 0, MAX_CAPACITY);
	memcpy(mesaj->payload, &(kermitPacket->soh), 1);
	memcpy(mesaj->payload + 1, &(kermitPacket->len), 1);
	memcpy(mesaj->payload + 2, &(kermitPacket->seq), 1);
	memcpy(mesaj->payload + 3, &(kermitPacket->type), 1);

	if (kermitPacket->len - 5 > 0) {
		memcpy(mesaj->payload + 4, kermitPacket->data, kermitPacket->len - 5);
	}
	
	memcpy(mesaj->payload + kermitPacket->len - 1, &(kermitPacket->check), 2);
	memcpy(mesaj->payload + kermitPacket->len + 1, &(kermitPacket->mark), 1);
	mesaj->len = kermitPacket->len + 2;
}

/*
Realizeaza itroducerea octetilor din payload in campurile unui pachet
Introducerea se realizeaza in functie de lungimea payloadului
Pentru acest lucru mai intai curat zona de date din campul pachetului pentru
a scapa de "ramasite"

@param packet - pointer la o zona de memorie unde este alocata o structura de
				tip pachet
@param mesaj - adresa unuei variabile de tip mesaj, mesajul receptionat
*/
void puneMesajInPacket(MiniKermitPacket *packet, msg *mesaj) {

	memcpy(&(packet->soh), mesaj->payload, 1);
	packet->len = mesaj->len - 2;
	memcpy(&(packet->seq), mesaj->payload + 2, 1);
	memcpy(&(packet->type), mesaj->payload + 3, 1);
	memset(packet->data, 0, MAXL);

	if (mesaj->len - 7 > 0) {
		memcpy(packet->data, mesaj->payload + 4, mesaj->len - 7);
	}
	
	memcpy(&(packet->check), mesaj->payload + mesaj->len - 3, 2);
	memcpy(&(packet->mark), mesaj->payload + mesaj->len - 1, 1);
}

/*
Initializeaza data de tip S ce contine parametrii emitatorului

@param dataS - adresa une ivariabile de tip PackeSData ce reprezinta variabila
				ce se vrea a fi modificata prin introducerea parametrilor emitatorului

@param maxPacketLength - dimensiunea maxima a campului data dintr-un apchet de date
							pe care receptorul il primeste de la emitator
@param secodnsToWait - durata pe care emitatorul i-o transmite receptorului ca trebuie sa
						o astepte pana la primirea ultimului pachet, altfel se produce timeout
*/
void completeazaDataS(PacketSData *dataS, unsigned char maxPacketLength, int secondsToWait) {
	dataS->maxl = maxPacketLength;
	dataS->time = secondsToWait;
	dataS->npad = 0x00;
	dataS->padc = 0x00;
	dataS->eol = EOL;
	dataS->qctl = 0x00;
	dataS->qbin = 0x00;
	dataS->chkt = 0x00;
	dataS->rept = 0x00;
	dataS->capa = 0x00;
	dataS->r = 0x00;
}

/*
Realizeaza punerea structurii de date de tip Data corespunzatoare pachetului
de tip S in pachetul primit ca parametru copiind camp cu camp

@param kermitPacket - pointer catre o zona de memorie unde este alocata o
						strucutura de tip MiniKermitPacket, in acea strucura
						punandu-se data tip S
@param dataTipS - variabila de tip PacketSData care reprezinta chiar data
					de tip S ce trebuie pusa in apchet
*/
void puneDataSInPacket(MiniKermitPacket *kermiPacket, PacketSData dataTipS) {
	unsigned short crc;

	memset(kermiPacket->data, 0, MAXL);
	kermiPacket->len = 16;

	memcpy(kermiPacket->data, &(dataTipS.maxl), 1);
	memcpy(kermiPacket->data + 1, &(dataTipS.time), 1);
	memcpy(kermiPacket->data + 2, &(dataTipS.npad), 1);
	memcpy(kermiPacket->data + 3, &(dataTipS.padc), 1);
	memcpy(kermiPacket->data + 4, &(dataTipS.eol), 1);
	memcpy(kermiPacket->data + 5, &(dataTipS.qctl), 1);
	memcpy(kermiPacket->data + 6, &(dataTipS.qbin), 1);
	memcpy(kermiPacket->data + 7, &(dataTipS.chkt), 1);
	memcpy(kermiPacket->data + 8, &(dataTipS.rept), 1);
	memcpy(kermiPacket->data + 9, &(dataTipS.capa), 1);
	memcpy(kermiPacket->data + 10, &(dataTipS.r), 1);

	crc = getCRC(kermiPacket, DATA_S_LENGTH);
	kermiPacket->check = crc;
}
