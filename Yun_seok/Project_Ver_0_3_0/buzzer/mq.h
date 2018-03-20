#ifndef __MQ_H__
#define __MQ_H__

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


typedef struct _msg_RD_buf{
	long mtype;
	char device_name[10];
	char data[10]; //0: start 1:fin
}msg_RD_buf;

typedef struct _msg_WR_buf{
	long mtype;
	char device_name[10];
	char data[10]; //0: start 1:fin
}msg_WR_buf;

#endif //__MQ_H__
