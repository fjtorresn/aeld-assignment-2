#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>


int main(int argc, char**argv)
{
    openlog("writer", LOG_CONS, LOG_USER);
    
    if (argc == 1) {
        printf("Writer requires 2 arguments: writefile and writestr are missing.\n");
        syslog(LOG_ERR, "Writer requires 2 arguments: writefile and writestr are missing.\n");
        return 1;
    }
    if (argc == 2) {
        printf("Writer requires 2 arguments: writestr is missing.\n");
        syslog(LOG_ERR, "Writer requires 2 arguments: writestr is missing.\n");
        return 1;
    }
    if (argc > 3 ) {
        printf("Too many arguments provided.\n");
        syslog(LOG_ERR, "Too many arguments provided.\n");
        return 1;
    }
    
    const char *filename = *(argv + 1);
    const char *writestr = *(argv + 2);

    int fd;

    fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if (fd == -1) {
        perror("open");
        syslog(LOG_ERR, "An error has ocurred while opening the file: %s. Error: %d\n", filename, errno);
        printf("An error has ocurred while opening the file: %s. Error: %d\n", filename, errno);
        return 1;
    }

    ssize_t n;
    size_t count = strlen(writestr);
    n = write(fd, writestr, count);
    if (n == -1) {
        perror("write");
        syslog(LOG_ERR, "Writing error: %d", errno);
        return 1;
    } else if (n != count) {
        printf("Partial write: %ld out of %ld\n", n, count);
        syslog(LOG_ERR, "Partial write: %ld out of %ld\n", n, count);
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, filename);
    return 0;
}