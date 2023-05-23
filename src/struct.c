#include "../include/lib.h"

extern info_t *init_struct(char *filename, char *function_name, char *filename_shellcode)
{
    info_t *info = malloc(sizeof(info_t));

    if (!info) {
        put(2, "Error: Failed to allocate memory\n");
        return NULL;
    }

    info->filename = filename;
    info->function_name = function_name;
    info->filename_shellcode = filename_shellcode;
    info->pid = NULL;
    info->size_shellcode = 0;
    info->function_adress = 0;
    info->function_offset = 0;
    info->base_addr = 0;
    return info;
}

extern int free_struct(info_t *info)
{
    free(info->pid);
    free(info);
    return 0;
}