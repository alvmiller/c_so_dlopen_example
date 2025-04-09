#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "foo.h"
#include "foo1.h"
#include "foo2.h"

// https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
// https://en.ittrip.xyz/c-language/dynamic-plugin-loading-c
// https://dev.to/iamkhalil42/all-you-need-to-know-about-c-static-libraries-1o0b

// https://stackoverflow.com/questions/14884126/build-so-file-from-c-file-using-gcc-command-line
// https://medium.com/@johnos3747/shared-libraries-in-c-programming-ab149e80be22
// https://www.ibm.com/docs/en/aix/7.1?topic=memory-creating-shared-library
// https://medium.com/@4318_26766/creating-and-using-dynamic-libraries-in-c-language-912b078b7c52

// https://man7.org/linux/man-pages/man3/dlopen.3.html
// https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-dlopen-gain-access-dynamic-link-library

// https://medium.com/@927/static-libraries-in-c-ae888e5bcbc7
// https://www.tabbykatz.com/writings/static-libraries-in-C

// gcc -c -Wall -Werror -fpic foo.c
// gcc -shared -o libfoo.so foo.o
// gcc -c -Wall -Werror -fpic foo1.c
// gcc -shared -o libfoo1.so foo1.o
// gcc -c -Wall -Werror -Wextra foo2.c
// ar -rcs libfoo2.a foo2.o
// sudo cp /mnt/e/libfoo.so /usr/lib
// sudo chmod 0755 /usr/lib/libfoo.so
// sudo ldconfig
// unset LD_LIBRARY_PATH
// gcc -Wall -o test main.c -lfoo -ldl -L. -lfoo2
// ./test

int main(void)
{
    puts("This is a shared library test...");

	foo();

    void (*foo1)();
    void *handle = dlopen("/mnt/e/libfoo1.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }
    dlerror();
    *(void **)(&foo1) = dlsym(handle, "foo1");
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }
    foo1();
    dlclose(handle);

	foo2();

    return 0;
}