#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include "mq.h"
#include "buzzer.h"

#define NUM_THREADS 4 /* MAKE THREAD NUMBER */

msg_RD_buf Rd_msg;
int flag = 0;
void Buzzer_function(void* );

pthread_mutex_t buz_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buz_cond = PTHREAD_COND_INITIALIZER;



void MSG_Queue_Read(void *argumentPointer)
{ /*Read MSG_Queue function */
	key_t key_id;

	key_id = msgget((key_t)1234,IPC_CREAT|0666);	
	if(key_id == -1)
	{
		printf("key_get Error: \n");
		exit(0);
	}
	while(1)
	{
		if(msgrcv(key_id,(void *)&Rd_msg,sizeof(msg_RD_buf),1,0)==-1)
		{
			perror("msgrcv");
			exit(-1);
		}
		printf("%s :  %s\n",Rd_msg.device_name,Rd_msg.data);
		if((strcmp(Rd_msg.device_name,"Buzzer"))==0)
			pthread_cond_signal(&buz_cond);
	}
}

void Buzzer_function(void *argumentPointer){
	int fd;
	int len = 0;
	int i;
	int data;
	fd = open("/dev/buz", O_RDWR);
	while(1){
		pthread_mutex_lock(&buz_mutex);
		pthread_cond_wait(&buz_cond,&buz_mutex);
		if (fd<0) perror("open error");
		printf("buzzer on");
		data = atoi(Rd_msg.data);
		if(data ==1) {
			for(i=0;i<=0xfff;i++) ioctl(fd, BUZZER_ON, 0);
		}
		ioctl(fd, BUZZER_OFF,0);
		pthread_mutex_unlock(&buz_mutex);
	}
	close(fd); 
}
	// key_t key_id;
   // msg_WR_buf Wr_msg={2,"key",0};
   //key_id = msgget((key_t)1234,IPC_CREAT|0666);

	//if(key_id ==-1){
	//	printf("Key_get Error \n");
	//	exit(0);
	//}
	/*
	Wr_msg.data[0]='0';
	if(msgsnd(key_id,(void *)&Wr_msg,sizeof(msg_WR_buf)-4,IPC_NOWAIT)==-1){
		perror("msgsnd error \n");
		exit(0);
	}
	*/
int main(void){
	int status;
	pthread_t p_thread[NUM_THREADS];
	pthread_create(&p_thread[0],NULL,MSG_Queue_Read,NULL);
	pthread_create(&p_thread[1],NULL,Buzzer_function,NULL);
	pthread_join(p_thread[0],(void **)&status);
	pthread_join(p_thread[1],(void **)&status);

	printf("Program Fin");
	return 0;
}

