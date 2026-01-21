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

// Exercise 1: Expression option - verify -e option output with multiple substitutions
int validate_sed_expression(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain substitutions applied by -e commands
    // At minimum, should have modified content with THE in uppercase
    int has_modification = (strstr(content, "THE") != NULL || 
                           strstr(content, "the") == NULL);
    int is_valid = has_modification && strlen(content) > 0;
    
    free(content);
    return is_valid;
}

// Exercise 2: File option - verify -f option reads script from file
int validate_sed_file(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain substitutions from the script.sed file
    // Expect APPLE, BANANA, CHERRY in uppercase
    int has_substitutions = (strstr(content, "APPLE") != NULL ||
                            strstr(content, "BANANA") != NULL ||
                            strstr(content, "CHERRY") != NULL);
    
    free(content);
    return has_substitutions;
}

// Exercise 3: Extended regex - verify -r option enables extended regex patterns
int validate_sed_extended_regex(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain NUM replacing the numeric values
    int has_num_replacement = strstr(content, "NUM") != NULL;
    
    free(content);
    return has_num_replacement;
}
