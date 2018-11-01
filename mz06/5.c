#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

enum { ST_SIZE = 2 };

int
cmp_dir_names(const void *p1, const void *p2) {
    return strcasecmp(*(char **)p1, *(char **)p2); 
}

void
dir_traverse(char *dpath, char level)
{
    static DIR *d;
    if ((d = opendir(dpath)) == NULL) {
        return;
    }
    static struct dirent *entry;
    static int list_size = ST_SIZE;
    char **dir_list = calloc(list_size, sizeof(*dir_list));
    int dir_cnt = 0;
    char entry_path[PATH_MAX + 2];
    while ((entry = readdir(d))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        snprintf(entry_path, PATH_MAX + 2, "%s/%s", dpath, entry->d_name);
        static struct stat file;
        if (lstat(entry_path, &file) < 0) {
            continue;
        }
        if (S_ISDIR(file.st_mode) && !access(entry_path, R_OK)) {
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
        snprintf(entry_path, PATH_MAX + 2, "%s/%s", dpath, dir_list[i]);
        dir_traverse(entry_path, 1);
        free(dir_list[i]);
    }

    free(dir_list);
    if (level) {
        printf("cd ..\n");
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        return 1;
    }
    dir_traverse(argv[1], 0);
    return 0;
}
