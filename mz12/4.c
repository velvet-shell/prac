#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    unsigned mod = atoi(argv[2]);
    
    char filename[FILENAME_MAX] = "/tmp/up12-4.XXXXXX.c";
    mkstemps(filename, 2);
    FILE *tmp = fopen(filename, "w");

    fprintf(tmp, "#include <stdio.h>\nint main(void) { unsigned a; scanf(\"%%u\", &a);"
            "printf(\"%%u\\n\", (a * (unsigned long long) (a + 1) / 2) %% %u ); return 0;}", mod);

    fclose(tmp);
    if (!fork()) {
        execlp("gcc", "gcc", filename, "-o", argv[1], NULL);
        _exit(1);
    }
    wait(NULL);
    chmod(argv[1], 0751);
    unlink(filename);
    return 0;
}
