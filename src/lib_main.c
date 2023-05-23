/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** aa
*/

#include "../include/lib.h"

extern int inject_code(char *filename, char *function_name, char *filename_shellcode)
{
    info_t *inf = NULL;

    return (!(inf = init_struct(filename, function_name, filename_shellcode)) ||
    !(inf->function_adress = get_function_adress(inf)) ||
    !injection(inf)) ? -1 : free_struct(inf);
}
