#include <limits.h>

STYPE bit_reverse(STYPE value)
{
    UTYPE input = value;
    UTYPE res = 0;
    for (int i = 0; i < sizeof(UTYPE) * CHAR_BIT; i++) {
        res <<= 1;
        res |= (input >> i) & 1;
    }
    return (STYPE) res;
}
