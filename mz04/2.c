#include <stdio.h>
#include <string.h>

const char rights[] = "rwxrwxrwx";

enum { MASK_SIZE = sizeof(rights) - 1};

int
main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        int a;
        if (!sscanf(argv[i], "%o", &a)) {
            continue;
        }
        for (int j = MASK_SIZE - 1; j >= 0; j--) {
            if (((a >> j) & 1) == 1) {
                putchar(rights[MASK_SIZE - 1 - j]);
            } else {
                putchar('-');
            }
        }
        putchar('\n');
    }
    return 0;
}