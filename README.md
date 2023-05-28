# Function Adress Injector Linux

![Alt Text](tests/linux-inject.webp)

## Requirements & Installation:
```bash
sudo apt install -y binutils-dev
git clone git@github.com:0bishop/lib-injection-linux.git
cd lib-injection-linux/
make
```

## Run:
```bash
sudo ./inject hello print_hello tests/shellcode.bin
```

## Here is how to use the injector:
*https://thumbsnap.com/DqE7bNrs*

## If you want to use it in your code, just call this function:

```c
extern
int inject_code(char *filename, char *function_name, char *filename_shellcode);
// Return 1 if an error has been caught else 0, create an Issue if u get a SEGV
```

