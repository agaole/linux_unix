#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[])
{
	int i,num,size;
	char *ptr;
	if(argc!=3||strcmp(argv[1],"--help")==0)
	{
		printf("%s size num\n",argv[0]);
		return 0;
	}
	size=atoi(argv[1]);
	num=atoi(argv[2]);
	for(i=0;i<num;i++)
	{
		ptr=(char *)malloc(size);
		if(ptr==NULL)
		{
			printf("malloc fail\n");
			return -1;
		}
		else
		{
			printf("i=%d  programbrak=%10p\n",i,sbrk(0));
		}
	}
	return 0;

}
