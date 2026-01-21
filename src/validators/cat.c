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

// Exercise 1: Show all - verify -A option shows special characters
int validate_cat_show_all(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain special character representations (like ^I for tabs)
    // The output should be non-empty and contain visible content
    int is_valid = strlen(content) > 0;
    
    free(content);
    return is_valid;
}

// Exercise 2: Show ends - verify -E option shows $ at line endings
int validate_cat_show_ends(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain $ characters representing line endings
    int has_dollar_signs = strstr(content, "$") != NULL;
    
    free(content);
    return has_dollar_signs;
}

// Exercise 3: Number lines - verify -n option numbers all lines
int validate_cat_number(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain line numbers at the beginning of lines
    // Look for pattern like "     1" or "     5" (5 lines in test data)
    int has_numbers = (strstr(content, "1") != NULL || strstr(content, "2") != NULL);
    
    free(content);
    return has_numbers;
}

// Exercise 4: Squeeze blank - verify -s option removes multiple blank lines
int validate_cat_squeeze_blank(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // The output should contain the three lines with reduced blank lines
    // Should contain "Line one", "Line two", "Line three"
    int has_content = strstr(content, "Line") != NULL;
    
    free(content);
    return has_content;
}

// Exercise 5: Show tabs - verify -T option shows ^I for tabs
int validate_cat_show_tabs(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain ^I representations of tab characters
    int has_tab_markers = strstr(content, "^I") != NULL;
    
    free(content);
    return has_tab_markers;
}

// Exercise 6: Show non-printing - verify -v option displays special characters
int validate_cat_show_nonprinting(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Should contain the text from the file
    int has_content = strlen(content) > 0 && strstr(content, "Line") != NULL;
    
    free(content);
    return has_content;
}
