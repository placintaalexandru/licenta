#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "PacketManager.h"
#include "FileManager.h"

#define HOST "127.0.0.1"
#define PORT 10000

/*
Creeaza un pointer de pointeri la structuri de date de tip
MiniKermitPacket unde retin toate tipruile de pachete pe care poate sa
le foloseasca emitatorul
*/
MiniKermitPacket **creeazaPachete() {
    MiniKermitPacket **pachete;

    pachete = calloc(6, sizeof(MiniKermitPacket *));
    if (pachete == NULL) {
        return NULL;
    }

    pachete[0] = creeazaKermitPacket('S');
    pachete[1] = creeazaKermitPacket('F');
    pachete[2] = creeazaKermitPacket('D');
    pachete[3] = creeazaKermitPacket('Z');
    pachete[4] = creeazaKermitPacket('B');
    pachete[5] = creeazaKermitPacket('R');

    return pachete;
}

/*
Asteapta un raspuns, iar daca nu primeste trimite acelasi mesaj pana primeste
ACK, iar daca s-a ajuns la timeout se opreste executia
Efectuez asteptarea de TIME milisecunde dupa care verific daca am primit ceva, iar
daca nu inseamna ca e timeout si retrimit de maxim 3 ori
Daca s-a primit un mesaj verific daca codul crc aferent este identic cu cel
din campul check, altfel retrimit acel mesaj
Daca este NAK, il retrimit
Daca este ACK opresc procesul
Daca numerele de secventa sunt decalate, retrmit mesajul pentru ca inseamna ca cel
vechi nu a ajuns si trebuie retransmis
In caz de timeout de 3 ori eliberez memoria alocata pentru pachete
@param vectorPAchet - pointer-ul de pointeri care contine toate tipurile de pachete pe
                        care le poae transmite emitatorul
@param t - adresa unei variabile de tip mesaj care e folosita pentru a trimite mesaje
@param r - pointer folosit pentru receptionarea mesajelor
@param timeoutCounter - contor de timeout cu ajutorul caruia verific daca s-a ajuns la tiemout
@param seqNo - numarul de secventa cu ajutorul caruia verific daca un pachet este duplicat
@return - valoare ce indica daca se termina exectuita emtiatorului (-1) sau se continua (0)
*/
int waitForResponse(MiniKermitPacket **vectorPachete, msg *t, msg *r, int timeoutCounter, unsigned char *seqNo) {
    while (1) {
        r = receive_message_timeout(TIME);
        if (r == NULL) {
            if (timeoutCounter == 3) {
                elibereaza(vectorPachete, 6);
                perror("Timeout la Emitator de 3 ori");
                return -1;
            }

            send_message(t);
            timeoutCounter++;
        } else {
            timeoutCounter = 0;
            puneMesajInPacket(vectorPachete[5], r);

            if (vectorPachete[5]->check == crc16_ccitt(r->payload, r->len - 3)) {  // verific daca receptorul primeste un mesaj necorupt
                *seqNo = ((*seqNo) + 2) % MAX_SEQ;
                
                if (vectorPachete[5]->type == NAK) {         // daca emitatorul primeste NAK, actualizez mesajul, crc-ul si secventa din el si retrimit
                    unsigned short crc;
                    memcpy(t->payload + 2, seqNo, 1);
                    crc = crc16_ccitt(t->payload, t->len - 3);
                    memcpy(t->payload + t->len - 3, &crc, 2);
                    send_message(t);
                } else if (vectorPachete[5]->type == ACK) {            // daca emitatorul primeste ACK actualizez doar numarul de secventa
            	    free(r);
                    break;
                }

                free(r);
            } else {
            	send_message(t);
            }
        }
    }

    return 0;
}

/*
Initializeaza un buffer in care se vor citi date din fisier

@param size - lungimea bufferului
@return - adresa inceputlui zonei de memorie alocate pentru citire
*/
char *initBuffer(int size) {
    char *buffer;

    buffer = calloc(size, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    return buffer;
}

int main(int argc, char** argv) {
    init(HOST, PORT);
    
    msg t, *r = NULL;
    MiniKermitPacket **vectorPachete;
    PacketSData packetSData;
    unsigned int octetiCititi;
    unsigned char seqNo = 0;
    int fileId = -1, timeoutCounter = 0, i;
    char *buffer;
   
    vectorPachete = creeazaPachete();                                                         // creez pachetele folosite de emitator
    buffer = initBuffer(MAXL);                                                                // aloc spatiu pentru bufferu-ul de citire
    if (buffer == NULL) {
        elibereaza(vectorPachete, 6);
        return -1;
    }

    completeazaDataS(&packetSData, MAXL, TIME);                                               //incep trimiterea pachetului de SEND_INIT
    puneDataSInPacket(vectorPachete[0], packetSData);
    punePacketDateInMesaj(&t, vectorPachete[0]);
    send_message(&t);

    if (waitForResponse(vectorPachete, &t, r, timeoutCounter, &seqNo) == -1) {                 // astept raspuns pentru SEND_INIT
        free(buffer);
        return -1;
    }

    for (i = 1; i < argc; i++) {                                                              // parcurg toate numele fisierelor

    	fileId = deschideFisierSursa(argv[i]);
    	modificaPacketD(vectorPachete[1], argv[i], strlen(argv[i]), seqNo);                   // trimit un pachet de tip FILE_HEADER
    	punePacketDateInMesaj(&t, vectorPachete[1]);
    	send_message(&t);

        if (waitForResponse(vectorPachete, &t, r, timeoutCounter, &seqNo) == -1) {             // astept raspunsul
            if (fileId != -1) {
                    close(fileId);
            }

            free(buffer);
            return -1;
        }

    	while (1) {                                                                            // efectuez cititrea din fisier

        	octetiCititi = read(fileId, buffer, MAXL - 1);

        	if (octetiCititi <= 0) {                                                           // am ajuns la final sau a aparut o problema la citire
        		modificaPacketD(vectorPachete[3], vectorPachete[3]->data, 0, seqNo);           // trimit un pachet de END_OF_FILE
        		punePacketDateInMesaj(&t, vectorPachete[3]);
            	send_message(&t);

                if (waitForResponse(vectorPachete, &t, r, timeoutCounter, &seqNo) == -1) {       // astept raspunsul
                    if (fileId != -1) {
                        close(fileId);
                    }

                    free(buffer);
                    return -1;
                }

                close(fileId);
                fileId = -1;
            	break;
        	}

        	modificaPacketD(vectorPachete[2], buffer, octetiCititi, seqNo);                    // trimit un pachet de DATE
        	punePacketDateInMesaj(&t, vectorPachete[2]);
        	memset(buffer, 0, MAXL);
        	send_message(&t);

            if (waitForResponse(vectorPachete, &t, r, timeoutCounter, &seqNo) == -1) {          // astept raspunsul
                if (fileId != -1) {
                    close(fileId);
                }

                free(buffer);
                return -1;
            }
    	}
    }

    modificaPacketD(vectorPachete[4], vectorPachete[4]->data, 0, seqNo);                       // trimit un pachet de END_OF_TRANSMISION   
    punePacketDateInMesaj(&t, vectorPachete[4]);
    send_message(&t);

    if (waitForResponse(vectorPachete, &t, r, timeoutCounter, &seqNo) == -1) {                  // astept raspunsul
        if (fileId != -1) {
            close(fileId);
        }

        free(buffer);
        return -1;
    }

    free(buffer);                                                                              // eliberez memoria folosita
    elibereaza(vectorPachete, 6);
    return 0;
}