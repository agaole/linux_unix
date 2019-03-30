#include <unistd.h>
#include <sys/reboot.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int ret;
	ret = reboot(0x1234567);
	if(ret != 0)
	{
		printf("reboot fail!!\n");
		perror("reboot");
	}
	return 0;
}
