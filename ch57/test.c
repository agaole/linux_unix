#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd;
	int readNum;
       	int buf[100];
	fd = open("./test.txt",O_RDONLY);
	while(1)
	{
		readNum = read(fd,buf,10);
		printf("readNum = %d\n",readNum);
		sleep(1);
	}
	return 0;
}
