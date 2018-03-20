#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#include "mq.h"
#include "tcp.h"
#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */


int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */				
	key_t key_id;					 /* MSG queue Key */
	msg_WR_buf msg_buf;				 /* MSG Queue write Buf */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    msg_struct send_msg;             /* struct to send to echo server */
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int msg_struct_size;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
                                        and total bytes read */


    if ((argc < 4) || (argc > 5)) /* Test for correct number of arguments */
    {
	   printf("apple");
       fprintf(stderr, "Usage: %s <Server IP> <Device name> <Data> [<Echo Port>]\n", argv[0]);
       exit(1);
    }
	/* set_mamory_queue */
	key_id = msgget((key_t)1234,IPC_CREAT|0666);
	if(key_id ==-1){
		printf("key_get error");
		exit(0);
	}
    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
    strcpy(send_msg.device_name,argv[2]);/* Second arg: device_name */
	strcpy(send_msg.data,argv[3]); /*Third arg : data value */
	msg_buf.mtype = 1;
	strcpy(msg_buf.device_name, send_msg.device_name);
	strcpy(msg_buf.data,send_msg.data);
    if (argc == 4)
        echoServPort = atoi(argv[4]); /* Use given port, if any */
    else
        echoServPort = 7;  /* 7 is the well-known port for the echo service */

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    msg_struct_size = sizeof(send_msg);    /* Determine input length */

    /* Send the string to the server */
    if (send(sock,(char*)&send_msg,msg_struct_size, 0) ==-1)
        DieWithError("send() sent a different number of bytes than expected");
	 if (msgsnd( key_id, (void *)&msg_buf, sizeof(msg_WR_buf), IPC_NOWAIT) == -1){
			printf("msgsnd error \n ");
			exit(0);
	 } 
    /* Receive the same string back from the server */
//    totalBytesRcvd = 0;
//  printf("Received: ");                /* Setup to print the echoed string */
//    while (totalBytesRcvd < echoStringLen)
//    {
//        /* Receive up to the buffer size (minus 1 to leave space for
//           a null terminator) bytes from the sender */
//        if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
//            DieWithError("recv() failed or connection closed prematurely");
//        totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
//        echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */
//        printf(echoBuffer);            /* Print the echo buffer */
//   }
//
//    printf("\n");    /* Print a final linefeed */

    close(sock);
    exit(0);
}
