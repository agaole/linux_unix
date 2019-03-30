#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#define BACKLOG 5
#define SV_SOCK_PATH "/tmp/sock"
int 
main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int sfd,cfd;
	ssize_t numRead;
	char buf[1024];
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		printf("socket fail\n");
	}
	
	if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
	{
		printf("remove fail \n");
	}
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path));
	if(bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un))== -1)
	{
		printf("bind fail\n");
	}
	if(listen(sfd, BACKLOG)==-1)
	{
		printf("listen");
	}	
	for( ; ; )
	{
		cfd = accept(sfd, NULL, NULL);	
		while((numRead = read(cfd, buf,1024 )) > 0)
			if(write(STDOUT_FILENO,buf,numRead)!=numRead)
				printf("write fali\n");
		if(numRead == -1)
			printf("read\n");
		if(close(cfd)== -1)
			printf("close\n");
	}
}
