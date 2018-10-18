#include <string.h>

const char rights[] = "rwxrwxrwx";

enum { MASK_SIZE = sizeof(rights) - 1 };

int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    long size = strlen(str);
    if (size != MASK_SIZE) {
        return -1;
    }
    int num = 0;
    for (int i = 0; i < MASK_SIZE; i++) {
        if (str[i] != '-' && str[i] != rights[i]) {
            return -1;
        }
        if (str[i] == rights[i]) {
            num |= (1 << (MASK_SIZE - i - 1));
        }
    }
    return num;
}