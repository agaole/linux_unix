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
	int ret;
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
	msgLen = 6;
	if((ret = msgrcv(id, &msg, 100, 1, 0)) == -1)
	{
		printf("msgrcv fail\n");	
	}
	printf("ret = %d , mtext = %s\n",ret,msg.mtext);
	return 0;
}
