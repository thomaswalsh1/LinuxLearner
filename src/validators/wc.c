#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to parse wc output
// wc output format: "  <count> <filename>" or just "<count>"
static int parse_wc_count(const char *line) {
    int count = 0;
    sscanf(line, "%d", &count);
    return count;
}

// Helper function to read first line of output file
static char* read_first_line(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;
    
    static char line[256];
    if (fgets(line, sizeof(line), f)) {
        fclose(f);
        return line;
    }
    fclose(f);
    return NULL;
}

// Exercise 1: Byte count - verify -c option output
int validate_wc_bytes(void) {
    if (!file_exists("output.txt")) return 0;
    
    // The file should contain byte count output
    // Expected: around 120+ bytes for the test file
    char *line = read_first_line("output.txt");
    if (!line) return 0;
    
    int count = parse_wc_count(line);
    return count > 0;
}

// Exercise 2: Line count - verify -l option output
int validate_wc_lines(void) {
    if (!file_exists("output.txt")) return 0;
    
    // The file should contain line count output
    // Expected: 5 lines in the test file
    char *line = read_first_line("output.txt");
    if (!line) return 0;
    
    int count = parse_wc_count(line);
    return count == 5;
}

// Exercise 3: Word count - verify -w option output
int validate_wc_words(void) {
    if (!file_exists("output.txt")) return 0;
    
    // The file should contain word count output
    // Expected: around 11 words in the test file
    char *line = read_first_line("output.txt");
    if (!line) return 0;
    
    int count = parse_wc_count(line);
    return count > 0 && count == 14;
}

// Exercise 4: Character count - verify -m option output
int validate_wc_chars(void) {
    if (!file_exists("output.txt")) return 0;
    
    // The file should contain character count output
    char *line = read_first_line("output.txt");
    if (!line) return 0;
    
    int count = parse_wc_count(line);
    return count > 0;
}

// Exercise 5: Max line length - verify -L option output
int validate_wc_max_line_length(void) {
    if (!file_exists("output.txt")) return 0;
    
    // The file should contain max line length output
    // The longest line is around 90+ characters
    char *line = read_first_line("output.txt");
    if (!line) return 0;
    
    int count = parse_wc_count(line);
    return count > 0;
}
