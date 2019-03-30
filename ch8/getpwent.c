#include <shadow.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
struct passwd *pwd;

int main()
{
	while((pwd=getpwent())!=NULL)
		printf("%-8s %5ld\n",pwd->pw_name,(long)pwd->pw_uid);
	endpwent();
	return 0;
}
