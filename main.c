#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    char resolvedPath[PATH_MAX];
    realpath(argv[1], resolvedPath);
    printf("File path: %s\n", resolvedPath);


    

    return 0;
}
