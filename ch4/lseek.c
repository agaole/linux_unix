#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd,numWrite;
	off_t offset;
	fd=open("test",O_RDWR,O_CREAT,0666);
	if(fd==-1)
	{
		printf("open fail\n");
		return -1;
	}
	numWrite=write(fd,"123\n456\n",8);
	printf("numWrite=%d\n",numWrite);
	offset=lseek(fd,10000,SEEK_CUR);
	printf("offset=%d\n",(int)offset);
	numWrite=write(fd,"789\n987\n",8);
	printf("numWrite=%d\n",numWrite);
	sleep(5);
	close(fd);
	return 0;
}
