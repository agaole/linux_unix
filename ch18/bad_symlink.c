#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define errExit printf
int
main(int argc, char *argv[])
{
    int fd;

    if (mkdir("test", S_IRUSR | S_IWUSR | S_IXUSR) == -1)
        errExit("mkdir");
    if (chdir("test") == -1)
        errExit("chdir");
    fd = open("myfile", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    if (close(fd) == -1)
        errExit("close");
    chdir("..");
    if (symlink("test/myfile", "mylink") == -1)
        errExit("symlink");
    if (chmod("mylink", S_IRUSR) == -1)
        errExit("chmod");

    return 0;
}
