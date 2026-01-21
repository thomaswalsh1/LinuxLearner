#include "validators.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int validate_grep_basic(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "error");
}

int validate_grep_count(void) {
    if (!file_exists("output.txt")) return 0;
    FILE *f = fopen("output.txt", "r");
    if (!f) return 0;
    int count;
    int ret = fscanf(f, "%d", &count);
    fclose(f);
    return ret == 1 && count == 2; // assuming 2 error lines
}

int validate_grep_dir_skip(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "error") &&
           !file_contains("output.txt", "logs/subdir"); // directories skipped
}

int validate_grep_extended(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "error") &&
           file_contains("output.txt", "warning");
}

int validate_grep_ignore_case(void) {
    return file_exists("output.txt") &&
           (file_contains("output.txt", "error") || file_contains("output.txt", "Error"));
}

int validate_grep_recursive(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "error: log1") &&
           file_contains("output.txt", "error: log2") &&
           file_contains("output.txt", "error: log");
}

int validate_grep_invert(void) {
    return file_exists("output.txt") &&
           !file_contains("output.txt", "error");
}

int validate_grep_combo(void) {
    return file_exists("output.txt") &&
           !file_contains("output.txt", "error") &&
           !file_contains("output.txt", "Error");
}