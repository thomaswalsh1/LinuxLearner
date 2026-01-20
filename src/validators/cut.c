#include "validators.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int validate_cut_characters(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "123");
}

int validate_cut_bytes(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "AB");
}

int validate_cut_delimiter(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "alice") &&
           file_contains("output.txt", "bob");
}

int validate_cut_fields(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "John") &&
           file_contains("output.txt", "Mike");
}

int validate_cut_only_delimited(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "one") &&
           !file_contains("output.txt", "NODASH");
}
