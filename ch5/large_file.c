#define _FILE_OFFDET_BITS 64
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc,char *argv[])
{
	int fd;
	off_t off;
	if(argc!=3||strcmp(argv[1],"--help")==0)
		printf("%s pathname offset\n",argv[0]);
	fd=open(argv[1], O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	if(fd==-1)
		perror("open fail");
	off=atoll(argv[2]);
	if(lseek(fd, off, SEEK_SET)==-1)
		perror("lseek fail");
	if(write(fd, "test", 4)!=4)
		perror("write fail");
	return 0;
}
