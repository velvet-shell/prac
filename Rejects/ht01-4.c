#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { START_SIZE = 8 };

char *
getline2(FILE *f)
{
    int cur_pos = 0;
    int buf_size = START_SIZE;
    int read_buf = START_SIZE;
    char *buf = calloc(buf_size, sizeof(*buf));
    if (buf == NULL) {
        return NULL;
    }
    while (fgets(buf + cur_pos, read_buf, f)) {

        size_t read_len = strlen(buf + cur_pos);
        if (buf[cur_pos + read_len - 1] == '\n') {
            return buf;
        }

        if (cur_pos != 0) {
            cur_pos += read_buf - 1;
            read_buf *= 2;
        } else {
            cur_pos += read_buf - 1;
        }
        buf_size *= 2;

        char *tmp = realloc(buf, buf_size * sizeof(*buf));
        if (tmp == NULL) {
            free(buf);
            return NULL;
        }
        buf = tmp;
    }
    if (cur_pos == 0) {
        free(buf);
        return NULL;
    }
    return buf;
}