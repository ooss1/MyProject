#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<termio.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include "mq.h"
#include "dcmot.h"

#define L 0
#define R 1
#define NUM_THREADS 4 /* MAKE THREAD NUMBER */
msg_RD_buf Rd_msg;
int flag = 0;
void Buzzer_function(void* );

pthread_mutex_t buz_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buz_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t servo_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t servo_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t motor_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t motor_cond = PTHREAD_COND_INITIALIZER;

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
		printf("%s :  %s\n",Rd_msg.device_name,Rd_msg.buz_data);
		if((strcmp(Rd_msg.device_name,"Buzzer"))==0)
			pthread_cond_signal(&buz_cond);
		else if((strcmp(Rd_msg.device_name,"Servo"))==0)
			pthread_cond_signal(&servo_cond);
		else if((strcmp(Rd_msg.device_name,"Moter"))==0)
			pthread_cond_signal(&motor_cond);
	}
}

void Buzzer_function(void *argumentPointer){
	int fd;
	volatile int data=0;
	fd = open("/dev/buz", O_RDWR);
	if(fd>0) printf("Buzzer open...\n");
	while(1){
		pthread_mutex_lock(&buz_mutex);
		pthread_cond_wait(&buz_cond,&buz_mutex);
		if (fd<0) perror("open error");
		printf("buzzer on");
		do{
		data = atoi(Rd_msg.buz_data);
		read(fd, data,0);
		}while(data==1);
		pthread_mutex_unlock(&buz_mutex);
	}
	close(fd); 
}
void Servo_function(void * voidpointer)
{
	int fd;
	int data;
	static int temp_data=0;
	fd = open("/dev/submot",O_RDWR);
	if(fd>0) printf("Servo open...\n");
	while(1){
		pthread_mutex_lock(&servo_mutex);
		pthread_cond_wait(&servo_cond,&servo_mutex);
		if (fd<0) perror("open error");
		printf("Servo on");
		data = atoi(Rd_msg.servo_data);
		if(temp_data>data) write(fd,L,0);
		else if(temp_data<data) write(fd,R,0);
		temp_data = data;
		pthread_mutex_unlock(&servo_mutex);
	}
	close(fd);
}
void Motor_function(void * voidpointer)
{
	int fd;
	int data;
	fd = open ("/dev/dcmot",O_RDWR);
	if(fd>0) printf("Motor open....\n");
	while(1){
		pthread_mutex_lock(&motor_mutex);
		pthread_cond_wait(&motor_cond,&motor_mutex);
		printf("Motor on");
		do{	
			ioctl(fd, DC_GO, 0);
			sleep(1);
			data = atoi(Rd_msg.motor_data);
			printf("data : %d\n",data);
			//ioctl(fd, DC_STOP,0);
			//sleep(3);
		}while(data>1);
		ioctl(fd, DC_STOP,0);
		pthread_mutex_unlock(&motor_mutex);
	}
	close(fd);
}
int main(void){
	int status;
	pthread_t p_thread[NUM_THREADS];
	pthread_create(&p_thread[0],NULL,MSG_Queue_Read,NULL);
	pthread_create(&p_thread[1],NULL,Buzzer_function,NULL);
	pthread_create(&p_thread[2],NULL,Servo_function,NULL);
	pthread_create(&p_thread[3],NULL,Motor_function,NULL);
	pthread_join(p_thread[0],(void **)&status);
	pthread_join(p_thread[1],(void **)&status);
	pthread_join(p_thread[2],(void **)&status);
	pthread_join(p_thread[3],(void **)&status);

	printf("Program Fin");
	return 0;
}

