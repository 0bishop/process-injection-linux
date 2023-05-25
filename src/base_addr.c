#include "../include/lib.h"

static char *get_proc_pid(char *name)
{
    DIR *dir;
    int pid = 0;
    ssize_t bytesRead = 0;
    int fd = 0;
    struct dirent *ent;
    struct stat st;

    char *cmp = malloc(sizeof(char) * getpagesize());
    char *buf = NULL;
    char *ret = NULL;
    size_t buf_size = getpagesize();

    if (!(dir = opendir("/proc")))
        return NULL;
    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..") || ent->d_type != 4)
            continue;
        cmp = strcat(strcat(strcpy(cmp, "/proc/"), ent->d_name), "/comm");

        if (stat(cmp, &st) == -1)
            continue;
        fd = open(cmp, O_RDONLY);
        bytesRead = read(fd, (buf = malloc(buf_size)), buf_size - 1);
        close(fd);
        buf[bytesRead - 1] = '\0';

        if (!strcmp(name, buf)) {
            free(buf);
            free(cmp);
            ret = strdup(ent->d_name);
            closedir(dir);
            return ret;
        }
        free(buf);
    }
    free(cmp);
    closedir(dir);
    return NULL;
}

static char* parse_path(const char* line) {
    const char* end = NULL;
    const char* start = strrchr(line, ' ');
    char* path = NULL;
    size_t length = 0;

    if (!start)
        return NULL;
    start++;
    end = strchr(start, '\n');
    if (!end)
        end = strchr(start, '\0');
    length = end - start;

    path = strncpy(malloc(length + 1), start, length);
    path[length] = '\0';
    return path;
}

static char *get_token(info_t *inf, char *path)
{

    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    FILE *fp = fopen(path, "r");

    if (!fp)
        return NULL;

    while ((read = getline(&line, &len, fp)) != -1)
        break;
    fclose(fp);
    inf->filename_path = parse_path(line);
    return strtok(line, "-");
}

static unsigned long int core_base_addr(info_t *inf)
{
    unsigned long int base_adress = 0;
    char *buff = NULL;
    char *tmp = NULL;
    char *path = strcat(strcat(strcpy(malloc(sizeof(char) * (strlen(inf->pid) + 12)), "/proc/"), inf->pid), "/maps");
    
    if (!(buff = get_token(inf, path))) {
        free(path);
        free(inf->pid);
        return -1;
    }
    tmp = malloc(sizeof(char) * (strlen(buff) + 3));
    base_adress = strtol(strcat(strcpy(tmp, "0x"), buff), NULL, 16);

    free(tmp);
    free(path);
    free(buff);
    return base_adress;
}

extern unsigned long int get_base_addr(info_t *inf)
{
    inf->pid = get_proc_pid(inf->filename);

    if (!inf->pid) {
        put(2, "Error: ");
        put(2, inf->filename);
        put(2, " not found in current process\n");
        return 0;
    }
    return core_base_addr(inf);
}
