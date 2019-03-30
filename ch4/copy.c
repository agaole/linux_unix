#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc,char *argv[])
{
#ifndef BUF_SIZE 
#define BUF_SIZE 1024
#endif
	char buf[BUF_SIZE];
	int inputFd,outputFd;	
	int openFlags;
	int numRead;
	mode_t filePerms;
	if(argc!=3||strcmp(argv[1],"--help"))
		printf("%s old-file new-file\n",argv[0]);
	inputFd=open(argv[1],O_RDONLY);
	if(inputFd==-1)
		perror("open inputFd fail");
	openFlags=O_CREAT|O_WRONLY|O_TRUNC;
	filePerms=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IWOTH|S_IWOTH;
	outputFd=open(argv[2],openFlags,filePerms);
	if(outputFd==-1)
		perror("open outputFd fail");
	/*遇到eof（-1）时返回0，空洞部分为0，所以空洞部分不影响继续读取*/
	while((numRead=read(inputFd,buf,BUF_SIZE))>0)
		if(write(outputFd,buf,numRead)!=numRead)
			printf("could't write whole buffer\n");
	if(numRead==-1)
		perror("read fail");
	if(close(inputFd)==-1)
		perror("close inputFd fail");
	if(close(outputFd)==-1)
		perror("close outputFd fail");
	return 0;
}
