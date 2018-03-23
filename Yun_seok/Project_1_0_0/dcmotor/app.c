#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termio.h>

#include "dcmot.h"

int main(void)
{	
	int fd;
	fd = open("/dev/dcmot", O_RDWR);
	printf("fd = %d\n", fd);
	 if (fd<0) {
        	perror("open error");
        	exit(-1);}
	while(1){
			ioctl(fd, DC_GO, 0);
			sleep(10);
			ioctl(fd, DC_STOP, 0);
			sleep(3);
		}
	close(fd); 
	return 0;
}
