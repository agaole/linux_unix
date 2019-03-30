#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#define BACKLOG 5
#define SV_SOCK_PATH "/tmp/sock"
#define BUF_SIZE 1024
int 
main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1)
		printf("socket fail\n");
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path));

	if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un))==-1)
	{
		printf("connect fail\n");
	}
	while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
		if(write(sfd, buf, numRead) != numRead)
			printf("write fail\n");
	if(numRead == -1)
		printf("read fail\n");

	return 0;
}
