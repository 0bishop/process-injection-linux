/*
** EPITECH PROJECT, 2023
** lib.h
** File description:
** LIB_H
*/

#ifndef LIB_H
    #define LIB_H

    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <bfd.h>
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/reg.h>
    #include <sys/user.h>

    typedef struct info_s {
        char *filename;
        char *filename_path;
        char *function_name;
        char *filename_shellcode;
        char *pid;
        unsigned long int size_shellcode;
        unsigned long int function_adress;
        unsigned long int function_offset;
        unsigned long int base_addr;
    } info_t;

    extern info_t *init_struct(char *filename, char *function_name, char *filename_shellcode);
    extern int free_struct(info_t *info);
    extern unsigned long int get_function_offset(info_t *inf);
    extern unsigned long int get_base_addr(info_t *inf);
    extern unsigned long int get_function_adress(info_t *inf);
    extern int inject_code(char *filename, char *function_name, char *filename_shellcode);
    extern int injection(info_t *inf);
    extern int put(int fd, char *str);
    extern bool get_scope(void);

#endif /* !LIB_H */
