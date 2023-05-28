#include "../include/lib.h"

extern bool get_scope(void)
{
    int fd = open("/proc/sys/kernel/yama/ptrace_scope", O_RDONLY);
    char *buffer = NULL;

    if (fd < 0)
        return true;
    buffer = malloc(2);
    read(fd, buffer, 1);
    close(fd);
    buffer[1] = '\0';
    if (!strcmp(buffer, "0")) {
        free(buffer);
        return false;
    }
    free(buffer);
    return true;
}

extern int put(int fd, char *str)
{
    return write(fd, str, strlen(str));
}
