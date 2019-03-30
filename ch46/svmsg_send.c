#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
struct mbuf{
	long mtype;
	char mtext[1024];
};

int main(int argc, char *argv[])
{
	key_t key;
	int id;
	struct mbuf msg;
	int msgLen;
	key = ftok("msg_test", 1);
	while((id = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR)) <  0)
	{
		if(errno == EEXIST)
		{
			id = msgget(key,0);
			if(id == -1)
				printf("msgget fail\n");
			if(msgctl(id, IPC_RMID, NULL) == -1)
				printf("msgctl fail\n");
			printf("remove old message queue %d\n", id);
		}
		else
		{
			printf("msgget fail\n");
		}
	}
	msg.mtype = 1;
	strcpy(msg.mtext, "12345\n");
	msgLen = 6;
	if(msgsnd(id, &msg, msgLen,0 ) == -1)
	{
		printf("msgsnd fail\n");	
	}
	return 0;
}
