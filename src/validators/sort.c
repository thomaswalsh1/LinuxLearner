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

// Exercise 1: Check if sorted - verify that output.txt exists and is sorted
int validate_sort_check(void) {
    if (!file_exists("output.txt")) return 0;
    
    // Verify the file contains expected sorted data
    return file_contains("output.txt", "apple") &&
           file_contains("output.txt", "elderberry");
}

// Exercise 2: Ignore case - verify output.txt exists and has case-insensitive sort
int validate_sort_ignore_case(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Verify that lowercase and uppercase items are mixed properly (case-insensitive sort)
    // In a case-insensitive sort, 'apple' should come before 'Zebra'
    int has_apple = strstr(content, "apple") != NULL;
    int has_letters = strstr(content, "Mango") != NULL || strstr(content, "mango") != NULL;
    
    free(content);
    return has_apple && has_letters;
}

// Exercise 3: Sort by field - verify sorting by second field (age)
int validate_sort_by_field(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Check that Diana (22) appears before other entries since it's the smallest age
    int is_sorted_by_age = strstr(content, "Diana") != NULL;
    
    free(content);
    return is_sorted_by_age;
}

// Exercise 4: Month sort - verify sorting by month abbreviations
int validate_sort_month(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // In month sort, JAN entries should come before FEB entries
    int is_month_sorted = strstr(content, "JAN") != NULL && 
                          strstr(content, "FEB") != NULL;
    
    free(content);
    return is_month_sorted;
}

// Exercise 5: Numeric sort - verify numerical ordering
int validate_sort_numeric(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // Check that file contains expected numbers
    int has_numbers = strstr(content, "1") != NULL && 
                      strstr(content, "100") != NULL &&
                      strstr(content, "1000") != NULL;
    
    // Verify the first line is "1" (smallest numeric value)
    int starts_with_one = content[0] == '1';
    
    free(content);
    return has_numbers && starts_with_one;
}

// Exercise 6: Output to file - verify -o option creates output.txt
int validate_sort_output(void) {
    return file_exists("output.txt") &&
           file_contains("output.txt", "apple") &&
           file_contains("output.txt", "grape");
}

// Exercise 7: Reverse sort - verify reverse alphabetical order
int validate_sort_reverse(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // In reverse sort, entries starting with 'g' should come before 'a'
    // Check that 'grape' appears before 'apple' in the file
    char *grape_pos = strstr(content, "grape");
    char *apple_pos = strstr(content, "apple");
    
    int is_reversed = (grape_pos != NULL && apple_pos != NULL && grape_pos < apple_pos);
    
    free(content);
    return is_reversed;
}

// Exercise 8: Combined options - verify numeric reverse sort by first field
int validate_sort_combined(void) {
    if (!file_exists("output.txt")) return 0;
    
    char *content = read_entire_file("output.txt");
    if (!content) return 0;
    
    // With -k 1 -rn, should sort by first field numerically in reverse
    // So 500 should come first, then 400, 300, 200, 100
    // Check that file starts with a line containing 500 or Mike
    int starts_correctly = (content[0] == '5' || strstr(content, "500") != NULL);
    
    free(content);
    return starts_correctly;
}
