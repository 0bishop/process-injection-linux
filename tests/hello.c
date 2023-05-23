#include <stdio.h>
#include <unistd.h>

void print_hello(int *i) {
    printf("{%d} -> {%p} hello adress : %p\n", *i, i, print_hello);
    sleep(3);
    return;
}

int main() {
    printf("base addr : %p %d\n", main, getpid());
    for (int i = 0; i < 10000; ++i) {
        print_hello(&i);
    }
    return 0;
}
