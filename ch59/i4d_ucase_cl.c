#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 10
#define PORT_NUM 50002


int 
main(int argc, char *argv[])
{
	struct sockaddr_in svaddr;
	int sfd,j;
	size_t msgLen;
	ssize_t numBytes;
	char resp[BUF_SIZE];
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1){
		printf("socket fail\n");
	}
	memset(&svaddr, 0, sizeof(struct sockaddr_in));
	svaddr.sin_family = AF_INET;
	svaddr.sin_port = htons(PORT_NUM);
	if(inet_pton(AF_INET, argv[1], &svaddr.sin_addr) <= 0)
	{
		printf("inet_pton fail \n");
	}
	for(j = 2; j < argc; j++)
	{
		msgLen = strlen(argv[j]);
		if(sendto(sfd, argv[j],msgLen,0,(struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) <= 0)
		{
			printf("sendto fail\n");
		}
		numBytes = recvfrom(sfd,resp,BUF_SIZE,0, NULL,NULL);
		if(numBytes == -1)
			printf("recvfrom fail\n");
		printf("Response %d:%.*s\n",j-1,(int)numBytes,resp);
	}
	return 0;
}
