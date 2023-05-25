#include "include/lib.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        put(2, "USAGE:\t./inject [process name] [function_name] [shellcode.bin]\n\t./inject hello \"print_hello\" shellcode.bin\n");
        return 1;
    }
    inject_code(argv[1], argv[2], argv[3]);
    return 0;
}
