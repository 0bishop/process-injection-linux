#include "../include/lib.h"

extern int put(int fd, char *str)
{
    return write(fd, str, strlen(str));
}
