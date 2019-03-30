#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc ,char *argv[])
{
	int inFd,outFd;
	int flags,readNum;
	mode_t mode;
	char buf[BUF_SIZE];
	if(argc!=3||!strcmp(argv[1],"--help"))
	{
		printf("%s src-file dst-file\n",argv[0]);
		return 0;
	}
	inFd=open(argv[1],O_RDONLY);
	if(inFd==-1)
	{
		perror("open src-file fail");
		return -1;
	}	
	flags=O_WRONLY|O_CREAT|O_TRUNC;
	mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
	outFd=open(argv[2],flags,mode);
	if(outFd==-1)
	{
		perror("open dst-file fail");
		return -1;
	}
	while((readNum=read(inFd,buf,BUF_SIZE))>0)
	{
		if(readNum!=write(outFd,buf,readNum))
		{
			printf("write fail\n");
			return -1;
		}
	}
	if(close(inFd)==-1)
	{
		perror("close fail\n");
		return -1;
	}
	if(close(outFd)==-1)
	{
		perror("close fail\n");
		return -1;
	}	
	return 0;
}