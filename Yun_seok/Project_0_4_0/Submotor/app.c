#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termio.h>

#define L		0
#define R		1

int main(void)
{	
	int fd;
	fd = open("/dev/submot", O_RDWR);
	printf("fd = %d\n", fd);
	 if (fd<0) {
        	perror("open error");
        	exit(-1);}
	while(1){
			printf("left\n");
			write(fd, L, 0);
			sleep(1);
			printf("right\n");
			write(fd, R, 0);
			sleep(1);
			printf("right\n");
			write(fd, R, 0);
			sleep(1);
			printf("left\n");
			write(fd, L, 0);
			sleep(1);
		}
	close(fd); 
	return 0;
}
