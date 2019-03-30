#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
int main(int argc, char* argv[])
{
	key_t key;
	int msqid;
	const int MQ_PREMS = S_IRUSR | S_IWUSR | S_IWGRP;
	
	key = ftok("./msg_test",1);
	if(key ==  -1)
	{
		printf("fotk fail\n");
		return -1;
	}
	while((msqid = msgget(key, IPC_CREAT | IPC_EXCL | MQ_PREMS)) ==  -1)
	{
		if(errno == EEXIST)
		{
			msqid = msgget(key , 0);
			if(msqid == -1)
			{
				printf("msgget fail\n");
				return -1;
			}
			if(msgctl(msqid, IPC_RMID, NULL) == -1)
			{
				printf("msgctl fail\n");
				return -1;
			}
			printf("rm old msssage queue msqid=%d\n", msqid);
		}
		else
		{
			printf("msgget() fail\n");
			return -1;
		}
	}
	return 0;
}
