#include "validators.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int validate_grep_basic(void) {
    return file_exists("errors.txt") &&
           file_contains("errors.txt", "error");
}

int validate_grep_count(void) {
    if (!file_exists("count.txt")) return 0;
    FILE *f = fopen("count.txt", "r");
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
    return file_exists("filtered.txt") &&
           file_contains("filtered.txt", "error") &&
           file_contains("filtered.txt", "warning");
}

int validate_grep_ignore_case(void) {
    return file_exists("case.txt") &&
           (file_contains("case.txt", "error") || file_contains("case.txt", "Error"));
}

int validate_grep_recursive(void) {
    return file_exists("recursive.txt") &&
           file_contains("recursive.txt", "error: log1") &&
           file_contains("recursive.txt", "error: log2") &&
           file_contains("recursive.txt", "error: log");
}

int validate_grep_invert(void) {
    return file_exists("invert.txt") &&
           !file_contains("invert.txt", "error");
}

int validate_grep_combo(void) {
    return file_exists("combo.txt") &&
           !file_contains("combo.txt", "error") &&
           !file_contains("combo.txt", "Error");
}