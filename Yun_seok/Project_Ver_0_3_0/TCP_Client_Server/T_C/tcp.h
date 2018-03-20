#ifndef __TCP_H__

#define __TCP_H__



#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/msg.h>



#ifdef __GUN_SOURCE

#define __USE_GNU 1

D_GNU_SOURCE when compile recv.c

#endif





typedef struct _msg_struct{
	char device_name[20];
	char data[10];
}msg_struct;

		

#endif //__TCP_H__
