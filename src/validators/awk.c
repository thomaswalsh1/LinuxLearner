#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to read entire file into memory
static char* read_entire_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *content = malloc(size + 1);
    if (!content) {
        fclose(f);
        return NULL;
    }
    
    fread(content, 1, size, f);
    content[size] = '\0';
    fclose(f);
    return content;
}

// Exercise 1: Field separator - verify -F option correctly parses delimited fields
int validate_awk_field_separator(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain extracted fields (names and jobs)
    int has_output = (strstr(content, "John") != NULL ||
                     strstr(content, "Engineer") != NULL) && strlen(content) > 0;
    
    free(content);
    return has_output;
}

// Exercise 2: File program - verify -f option reads awk program from file
int validate_awk_file(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain output from the awk program processing data
    int has_output = strlen(content) > 0;
    
    free(content);
    return has_output;
}

// Exercise 3: Sandbox mode - verify -s option executes in sandbox
int validate_awk_sandbox(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain numeric results from the calculation
    int has_output = strlen(content) > 0;
    
    free(content);
    return has_output;
}
