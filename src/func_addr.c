#include "../include/lib.h"

extern unsigned long int get_function_adress(info_t *inf)
{
    inf->base_addr = get_base_addr(inf);
    inf->function_offset = get_function_offset(inf);

    return (!inf->base_addr || !inf->function_offset) ? 0 : inf->base_addr + inf->function_offset;
}