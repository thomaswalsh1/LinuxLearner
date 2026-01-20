#include "validators.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int file_exists(const char *path) {
    return access(path, F_OK) == 0;
}

int file_contains(const char *path, const char *needle) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char buf[512];
    while (fgets(buf, sizeof(buf), f)) {
        if (strstr(buf, needle)) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
