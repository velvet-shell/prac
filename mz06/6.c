#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum { ST_SIZE = 2 };

int
cmp_dir_names(const void *p1, const void *p2) {
    return strcasecmp(*(char **)p1, *(char **)p2); 
}

void
dir_traverse(char *global_path, int offset, struct stat *file)
{
    DIR *d;
    if ((d = opendir(global_path)) == NULL) {
        return;
    }
    struct dirent *entry;
    int list_size = ST_SIZE;
    char **dir_list = calloc(list_size, sizeof(*dir_list));
    int dir_cnt = 0;
    while ((entry = readdir(d))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        snprintf(global_path + offset, NAME_MAX + 2, "/%s", entry->d_name);

        if (lstat(global_path, file) < 0) {
            continue;
        }
        if (S_ISDIR(file->st_mode) && !access(global_path, R_OK)) {
            if (dir_cnt == list_size - 1) {
                list_size *= 2;
                char **tmp = realloc(dir_list, list_size * sizeof(*dir_list));
                if (!tmp) {
                    return;
                }
                dir_list = tmp;
            }
            dir_list[dir_cnt] = strdup(entry->d_name);
            dir_cnt++;
        }
    }
    qsort(dir_list, dir_cnt, sizeof(*dir_list), cmp_dir_names);
    
    closedir(d);
    for (int i = 0; i < dir_cnt; i++) {
        printf("cd %s\n", dir_list[i]);
        snprintf(global_path + offset, NAME_MAX + 2, "/%s", dir_list[i]);

        dir_traverse(global_path, offset + strlen(dir_list[i]) + 1, file);

        printf("cd ..\n");
        free(dir_list[i]);
    }

    free(dir_list);
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        return 1;
    }
    struct stat file;
    char global_path[PATH_MAX + 2];
    snprintf(global_path, PATH_MAX, "%s", argv[1]);
    dir_traverse(global_path, strlen(global_path), &file);
    return 0;
}
