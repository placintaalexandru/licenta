#ifndef LIB
#define LIB

#define MAXL 250
#define TIME 5000
#define MAX_SEQ 64
#define MAX_CAPACITY 1400
#define DATA_S_LENGTH 11

#define SOH 0x01
#define EOL 0x0D

#define SEND_INIT 'S'
#define FILE_HEADER 'F'
#define DATA 'D'
#define EOFI 'Z'
#define EOTR 'B'
#define ACK 'Y'
#define NAK 'N'


typedef struct {
    int len;
    char payload[1400];
} msg;

void init(char* remote, int remote_port);
void set_local_port(int port);
void set_remote(char* ip, int port);
int send_message(const msg* m);
int recv_message(msg* r);
msg* receive_message_timeout(int timeout); //timeout in milliseconds
unsigned short crc16_ccitt(const void *buf, int len);

typedef struct {
	char soh;
	unsigned char len;
	unsigned char seq;
	char type;
	char data[MAXL];
	unsigned short check;
	char mark;
} MiniKermitPacket;

typedef struct {
	unsigned char maxl;
	unsigned char time;
	char npad;
	char padc;
	char eol;
	char qctl;
	char qbin;
	char chkt;
	char rept;
	char capa;
	char r;
} PacketSData;

#endif