#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
int main()
{
	struct passwd *p1, *p2;
	p1=getpwnam("gaole");
	p2=getpwnam("sunyunbo");
	printf("%ld %ld\n",(long)(p1->pw_uid),(long)(p2->pw_uid));
	sleep(5);
	return 0;
}
