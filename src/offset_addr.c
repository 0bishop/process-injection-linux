#include "../include/lib.h"

extern unsigned long int get_function_offset(info_t *inf)
{
    bfd* binary;
    bfd_init();
    binary = bfd_openr(inf->filename_path, NULL);
    if (binary == NULL) {
        put(2, "Error: Failed to open binary\n");
        return 0;
    }
    if (!bfd_check_format(binary, bfd_object)) {
        put(2, "Error: Invalid binary format\n");
        bfd_close(binary);
        return 0;
    }

    long storage_needed = bfd_get_symtab_upper_bound(binary);
    if (storage_needed <= 0) {
        put(2, "Error: Failed to get symbol table\n");
        bfd_close(binary);
        return 0;
    }

    asymbol** symbol_table = (asymbol**)malloc(storage_needed);
    long num_symbols = bfd_canonicalize_symtab(binary, symbol_table);
    if (num_symbols <= 0) {
        put(2, "Error: Failed to read symbol table\n");
        free(symbol_table);
        bfd_close(binary);
        return 0;
    }

    bfd_vma offset = 0;
    long flag = 0;
    for (long i = 0; i < num_symbols; ++i) {
        if (strcmp(symbol_table[i]->name, inf->function_name) == 0) {
            offset = bfd_asymbol_value(symbol_table[i]);
            ++flag;
            break;
        }
    }
    free(symbol_table);
    bfd_close(binary);
    if (!flag) {
        put(2, "Error: Function offset not found\n");
        return 0;
    }
    return offset;
}
