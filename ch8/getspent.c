#include <shadow.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
struct spwd  *pwd;

int main()
{
	while((pwd=getspent())!=NULL)
		printf("- %-8s %5ld\n",pwd->sp_namp,(long)pwd->sp_pwdp);
	endspent();
	return 0;
}
