#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "FileManager.h"
#include "PacketManager.h"

#define HOST "127.0.0.1"
#define PORT 10001

/*
Creeaza un pointer de pointeri ce puncteaza la zone
de memorie unde sunt alocate structuri de tipul
MiniKermitPacket pe care le foloseste receptorul

@return - adresa inceputlui zonei de memorie unde
            sunt alocati acei pointeri
*/
MiniKermitPacket **creeazaPachete() {
    MiniKermitPacket **pachete;
    pachete = calloc(3, sizeof(MiniKermitPacket *));
    if (pachete == NULL) {
        return NULL;
    }

    pachete[0] = creeazaKermitPacket('Y');
    pachete[1] = creeazaKermitPacket('N');
    pachete[2] = creeazaKermitPacket('N');
    pachete[2]->seq = -1;
    return pachete;
}


int main(int argc, char** argv) {
    init(HOST, PORT);

    msg *r, t;
    MiniKermitPacket **vectorPachete;
    char seqNo = -1, ultimulTip = NAK;
    int fileId = -1, timeoutCounter = 0;
    unsigned int timeToWait = TIME;
    unsigned char proba;
    
    vectorPachete = creeazaPachete();
 
 	while (1) {                                                                                           // astept mesaje
 		r = receive_message_timeout(timeToWait);

 		if (r == NULL) {                                                                                  // in caz de timeout
            vectorPachete[2]->type = ultimulTip;
            vectorPachete[2]->len = 5;                                        
            vectorPachete[2]->seq = seqNo;
 			punePacketDateInMesaj(&t, vectorPachete[2]);                                                  // retrimit ultimul mesaj

            if (timeoutCounter == 3) {                                                                    // in caz de timeout ma opresc
                elibereaza(vectorPachete, 3);
                perror("Timeout la Receptor de 3 ori");
                if (fileId != -1) {
                    close(fileId);
                }

                return -1;
            }

            send_message(&t);                                                                             // trimit un mesaj si cresc numararea de timeout
            timeoutCounter++;
 		} else {
            timeoutCounter = 0;                                                                           // resetez numaratorul de timeout 
            puneMesajInPacket(vectorPachete[2], r);
            memset(t.payload, 0, MAX_CAPACITY);
            seqNo = (seqNo + 2) % MAX_SEQ;                                                                // cresc numarul de secventa
 			
            if (vectorPachete[2]->check == crc16_ccitt(r->payload, r->len - 3)) {                         // verific daca pachetul e corupt

                vectorPachete[0]->seq = seqNo;
                ultimulTip = ACK;                                                                         // retin ultimul tip de msaj transmis

                switch (vectorPachete[2]->type) {                                                         // vad ce tip de pachet primesc

                    case SEND_INIT:                                                                       // preiau SEND_INIT                  

                        memcpy(&proba, vectorPachete[2]->data + 1, 1);                                    // aflu preferintele emitatorului cu privire la timpul de timeout
                        timeToWait = proba * 1000;

                        vectorPachete[2]->type = ACK;                                                     // trimit acelasi pachet ca ACK                                                   
                        vectorPachete[2]->seq = seqNo;
                        vectorPachete[2]->check = getCRC(vectorPachete[2], DATA_S_LENGTH);                // creez CRC-ul
                        punePacketDateInMesaj(&t, vectorPachete[2]);                                      // introduc pachetul in mesaj si il trimit
                        send_message(&t);

                    break;

                    case FILE_HEADER:                                                                     // preiau FILE_HEADER

                        fileId = creeazaFisierOutput(vectorPachete[2]->data);                             // deschid fisier nou
                        vectorPachete[0]->check = getCRC(vectorPachete[0], 0);                            // creez CRC-ul
                        punePacketDateInMesaj(&t, vectorPachete[0]);                                      // pun pachetul in mesaj si il trimit
                        send_message(&t);

                    break;


                    case DATA:                                                                             // preiau DATE

                        vectorPachete[0]->check = getCRC(vectorPachete[0], 0);                             // creez CRC-ul
                        punePacketDateInMesaj(&t, vectorPachete[0]);                                       // pun pachetul in mesaj si trimit
                        send_message(&t);
                        
                        if (r->len - 7 > 0) {                                                              // scriu in fisier
                            write(fileId, vectorPachete[2]->data, r->len - 7);
                        }

                    break;

                    case EOFI:                                                                              // preiau END_OF_FILE

                        vectorPachete[0]->check = getCRC(vectorPachete[0], 0);                              // creez CRC-ul
                        punePacketDateInMesaj(&t, vectorPachete[0]);                                        // pun pachetul in mesaj si il trimit
                        send_message(&t);   
                        close(fileId);                                                                      // inchid fisierul curent
                        fileId = -1;

                    break;

                    case EOTR:                                                                              // preiau END_OF_TRANSMISION

                        vectorPachete[0]->check = getCRC(vectorPachete[0], 0);                              // creez CRC-ul
                        punePacketDateInMesaj(&t, vectorPachete[0]);                                        // pun pachetul in mesaj si il trimit
                        send_message(&t);
                        free(r);                                                                            // eliberez resursele si termin receptorul
                        elibereaza(vectorPachete, 3);

                    return 0;
                }
 			} else {																						// mesajul e corupt
                vectorPachete[1]->seq = seqNo;                                                            
                vectorPachete[1]->check = getCRC(vectorPachete[1], 0);                                      // creez CRC-ul
                punePacketDateInMesaj(&t, vectorPachete[1]);                                                // pun pachetul cu NAK in mesaj si il trimit
 			 	send_message(&t);
                ultimulTip = NAK;                                                                           // retin ultimul tip de mesaj transmis
            }

            free(r);
 		}
 	}

	return 0;
}