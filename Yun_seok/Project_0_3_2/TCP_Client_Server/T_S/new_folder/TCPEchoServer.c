#include <stdio.h>      /* for fopen(),fclose(),printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */      

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define CAR_NUMBER 1

#include "tcp.h"
#include "parson.h"

void DieWithError(char *errorMessage);  /* Error handling function */
void HandleTCPClient(int clntSocket);   /* TCP client handling function */
int Save_Data (int Car_number, char *MSG); /*data to .txt file */
void Save_JSON (char *motor_value, char *buz_value, char *servo_value);
int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
	int check_SaveSuccess;		     /* check make file and save Success */		    struct sockaddr_in echoServAddr; /* Local address */
   	int GetSize;					 /* buffer size */
	struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short PORT;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */
	char temp_buffer[60];			 /* temp buffer */
	msg_struct *msg_recv; /* recv msg struct */
    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    PORT= atoi(argv[1]);  /* First arg:  local port */

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
		printf("READ Data : %s %s\n",msg_recv->device_name, msg_recv->data);
		//check_SaveSuccess=Save_Data(CAR_NUMBER,Client_MSG);

		// JSON Formatter
		Save_JSON (msg_recv->motor_data, msg_recv->buz_data, msg_recv-> servo_data);


		if(check_SaveSuccess ==-1 ) return -1;
		memset(msg_recv,NULL,sizeof(msg_recv));
       // HandleTCPClient(clntSock);

    }
    /* NOT REACHED */
}
int Save_Data (int Car_number, char *MSG){
	FILE *Data_stream;
	Data_stream = fopen("Car_Data.txt","a+");
	if(Data_stream ==NULL){ /* open fail... */
		printf(" Open or Making Fail....\n");
		return -1;
	}
	fprintf(Data_stream,"%d %s\n",Car_number,MSG);
	fclose(Data_stream);
	return 0;
}


void Save_JSON (char *motor_value, char *buz_value, char *servo_value)
{
    	JSON_Value *rootValue;
    	JSON_Object *rootObject;

	rootValue = json_value_init_object();             // JSON_Value 생성 및 초기화
	rootObject = json_value_get_object(rootValue);    // JSON_Value에서 JSON_Object를 얻음

	// 객체에 키를 추가하고 문자열 저장
	//// json_object_set_string(rootObject, "Title", "Inception-jisoo");
	// json_object_set_string(rootObject, "Title", value);
	// // 객체에 키를 추가하고 숫자 저장
	// json_object_set_number(rootObject, key, value);
	// json_object_set_number(rootObject, "Runtime", 148);
	// // 객체에 키를 추가하고 문자열 저장
	// json_object_set_string(rootObject, "Genre", "Sci-Fi");
	// json_object_set_string(rootObject, "Director", "Christopher Nolan");

	// // 객체에 키를 추가하고 배열 생성
	// json_object_set_value(rootObject, "Actors", json_value_init_array());
	// // 객체에서 배열 포인터를 가져옴
	// JSON_Array *actors = json_object_get_array(rootObject, "Actors");
	// // 배열에 문자열 요소 추가
	// json_array_append_string(actors, "Leonardo DiCaprio");
	// json_array_append_string(actors, "Joseph Gordon-Levitt");
	// json_array_append_string(actors, "Ellen Page");
	// json_array_append_string(actors, "Tom Hardy");
	// json_array_append_string(actors, "Ken Watanabe");

	// // 객체에 키를 추가하고 숫자 저장
	// json_object_set_number(rootObject, "imdbRating", 8.8);
	// // 객체에 키를 추가하고 불 값 저장
	// json_object_set_boolean(rootObject, "KoreaRelease", true);
		json_object_set_string(rootObject, "motor", motor_value);
		json_object_set_string(rootObject, "buz", buz_value);
		json_object_set_string(rootObject, "servo", servo_value);
	
	// JSON_Value를 사람이 읽기 쉬운 문자열(pretty)로 만든 뒤 파일에 저장
	json_serialize_to_file_pretty(rootValue, "example.json");

	json_value_free(rootValue);    // JSON_Value에 할당된 동적 메모리 해제
	// return 0;
}

