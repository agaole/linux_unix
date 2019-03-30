#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc,char *argv[])
{
	int fd,oldfd,newfd,numRead;
	char buf[1024];
	if(strcmp(argv[1],"--help")==0)
	{
		printf("%s dup/dup2 oldfd [newfd]\n",argv[1]);
		return 0;
	}
	if(strcmp(argv[1],"dup")==0)
	{
		fd=fcntl(atoi(argv[2]),F_DUPFD,0);
		if(fd==-1)
		{
			perror("fcntl");
			return -1;
		}
	}
	else if(strcmp(argv[1],"dup2")==0)
	{	
		oldfd=atoi(argv[2]);
		newfd=atoi(argv[3]);
		if(oldfd==newfd)
			return 0;
		if(fcntl(oldfd,F_GETFL)==-1)
		{
			errno=EBADF;
			printf("file test fail\n");
			return -1;
		}
		close(newfd);	
		fd=fcntl(oldfd,F_DUPFD,newfd);
	}
	while((numRead=read(fd,buf,1024))>0)
		write(STDOUT_FILENO,buf,numRead);
	return 0;
}
