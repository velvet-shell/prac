#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int read_full(int fd, void *node, int buf_size) {
    char *buf = node;
    int total = 0;
    int n;
    while ((n = read(fd, buf + total, buf_size - total)) > 0) {
        total += n;
    }
    return total != buf_size;
}

void
traverse(int fd, int32_t cur_idx, char root)
{
    if (!cur_idx && !root) {
        return;
    }
    struct Node input_node;
    if (lseek(fd, cur_idx * sizeof(input_node), SEEK_SET) < 0) {
        close(fd);
        exit(errno);
    }
    if (read_full(fd, &input_node, sizeof(input_node))) {
        close(fd);
        exit(errno);
    }
    traverse(fd, input_node.right_idx, 0);
    printf("%d\n", input_node.key);
    traverse(fd, input_node.left_idx, 0);
}


int
main(int argc, char const *argv[])
{
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    traverse(fd, 0, 1);
    close(fd);
    return 0;
}