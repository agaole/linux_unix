#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	key_t key;
	int id;

	key = ftok("./msg_test", 1);
	if(key == -1)
	{
		printf(" ftok fail \n");
		return -1;
	}	
	id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(id == -1)
	{
		printf("msgget fail\n");
		return -1;
	}
	else
		printf("id = %d\n", id);
	return 0;
}
