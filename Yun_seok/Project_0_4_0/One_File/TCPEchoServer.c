#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */  
#include "tcp.h"		/* msg_recv,msg_send struct define */

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define CAR_NUMBER 1
#define NUM_THREADS 4 /* MAKE THREAD NUMBER */

int flag = 0;
void Buzzer_function(void* );

void DieWithError(char *errorMessage);  /* Error handling function */
void HandleTCPClient(int clntSocket);   /* TCP client handling function */


msg_struct *msg_recv; /* recv msg to client */

pthread_mutex_t buz_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buz_cond = PTHREAD_COND_INITIALIZER;


void TCP_SERVER(unsigned short PORT)
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
	int check_SaveSuccess;		     /* check make file and save Success */		    struct sockaddr_in echoServAddr; /* Local address */
   	int GetSize;					 /* buffer size */
	struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int clntLen;            /* Length of client address data structure */
	char temp_buffer[60];			 /* temp buffer */
	

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
      
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(PORT);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
           		DieWithError("accept() failed");
		
		//data recv..
		GetSize = recv(clntSock,temp_buffer,50,0);

		temp_buffer[GetSize]='\0';
		msg_recv =(msg_struct*)temp_buffer;

        /* clntSock is connected to a client! */
		
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
		printf("READ Data : %s %s %s %s\n",msg_recv->device_name, msg_recv->motor_data,msg_recv->buz_data,msg_recv->servo_data);
		//check_SaveSuccess=Save_Data(CAR_NUMBER,Client_MSG);
		if((strcmp(msg_recv->device_name,"Buzzer"))==0){
			printf("aaaa");
			pthread_cond_signal(&buz_cond);
		}
		memset(msg_recv,NULL,sizeof(msg_recv));

    }
    /* NOT REACHED */
}

void Buzzer_function(void *argumentPointer){
	int fd;
	int len = 0;
	int data;
	char argument[6][20];
//	fd = open("/dev/buz", O_RDWR);
	while(1){
		pthread_mutex_lock(&buz_mutex);
		pthread_cond_wait(&buz_cond,&buz_mutex);
		strcpy(argument[0],"Buzzer");
		strcpy(argument[1],"192.168.0.90");
		strcpy(argument[2],"Buzzer");
		strcpy(argument[3],msg_recv->motor_data);
		strcpy(argument[4],msg_recv->buz_data);
		strcpy(argument[5],msg_recv->servo_data);
		TCP_Client(argument);
		//TCP_Client("Buzzer","192.168.0.90","Buzzer",msg_recv->motor_data,msg_recv->buz_data,msg_recv->servo_data);
//		if (fd<0) perror("open error");
//		data = atoi(msg_recv->buz_data);
//		read(fd, data,0);
		printf("aaaa");
//		strcpy(msg_recv->buz_data,"0");
		pthread_mutex_unlock(&buz_mutex);
	}
	close(fd); 
}
void TCP_Client(char  *argv[6])
{
    int sock;                        /* Socket descriptor */				
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    msg_struct send_msg;			 /* struct to send to echo server */
    unsigned int msg_struct_size;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
                                        and total bytes read */


    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
	strcpy(send_msg.device_name,argv[2]);
	strcpy(send_msg.motor_data,argv[3]);/* Second arg: device_name */
	strcpy(send_msg.buz_data,argv[4]);
	strcpy(send_msg.servo_data,argv[5]);/*Third arg : data value */

    echoServPort = 8;

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

    close(sock);
    exit(0);
}

int main(int argc,char *argv[]){
	int status;
	pthread_t p_thread[NUM_THREADS];
	pthread_create(&p_thread[0],NULL,TCP_SERVER,atoi(argv[1]));
	pthread_create(&p_thread[1],NULL,Buzzer_function,NULL);
	pthread_join(p_thread[0],(void **)&status);
	pthread_join(p_thread[1],(void **)&status);

	printf("Program Fin");
	return 0;
}

