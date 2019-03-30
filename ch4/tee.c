#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
int main(int argc,char *argv[])
{
	int fdW=-1;
	int numRead,numWrite;
	int flags;
	char buf[BUF_SIZE];
	mode_t mode;
	if(argc==3&&strcmp(argv[1],"-a"))
	{
		printf("%s -a file\n",argv[0]);
		return -1;
	}
	flags=O_WRONLY|O_CREAT;
	mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
	if(argc==2)
	{
		fdW=open(argv[1],flags|O_TRUNC,mode);
		if(fdW==-1)
		{
			printf("open fail\n");
			return -1;
		}
	}	
	else if(argc==3)
	{
		fdW=open(argv[2],flags|O_APPEND,mode);
		if(fdW==-1)
		{
			printf("open fail\n");
			return -1;
		}
	}
	while((numRead=read(STDIN_FILENO,buf,BUF_SIZE))>0)
	{
		numWrite=write(STDOUT_FILENO,buf,numRead);
		if(numWrite!=numRead)
		{
			printf("could't write whole\n");
			return -1;
		}	
		if(fdW!=-1)
		{
			numWrite=write(fdW,buf,numRead);
			if(numWrite!=numRead)
			{
				printf("could't write whole\n");
				return -1;
			}
		}
	}
	if(fdW!=-1)
	{
		if(close(fdW)==-1)
		{
			printf("close fail\n");
			return -1;
		}		
	}
	return 0;
}