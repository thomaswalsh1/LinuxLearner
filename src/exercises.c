// exercises.c
#include "exercises.h"
#include "../validators/validators.h"

// Example validator for first exercise
int validate_grep_basic(void) {
    return file_exists("errors.txt") &&
           file_contains("errors.txt", "error");
}

Exercise exercises[] = {
    {
        .id = "grep-01",
        .title = "Exercise 1: Basic grep",
        .description = "Use grep to extract all lines containing 'error' from log.txt and save them to errors.txt",
        .lab_dir = "labs/ex01",
        .validate = validate_grep_basic,
        .hint = "grep error log.txt > errors.txt",
        .target_file = "errors.txt"
    }, {
        .id = "grep-02",
        .title = "Exercise 2: Grep Count",
        .description = "Count the number of lines in log.txt that contain 'error' and save to count.txt",
        .lab_dir = "labs/ex02",
        .validate = validate_grep_count,
        .hint = "grep -c error log.txt > count.txt",
        .target_file = "count.txt"
    },
    {
        .id = "grep-03",
        .title = "Exercise 3: Grep Directory Skip",
        .description = "Search logs/ folder for 'error' and save matches to output.txt, skipping directories",
        .lab_dir = "labs/ex03",
        .validate = validate_grep_dir_skip,
        .hint = "grep -d skip error logs/* > output.txt",
        .target_file = "output.txt"
    },
    {
        .id = "grep-04",
        .title = "Exercise 4: Grep Extended Regex",
        .description = "Extract lines containing 'error' OR 'warning' using extended regex into filtered.txt",
        .lab_dir = "labs/ex04",
        .validate = validate_grep_extended,
        .hint = "grep -E 'error|warning' log.txt > filtered.txt",
        .target_file = "filtered.txt"
    },
    {
        .id = "grep-05",
        .title = "Exercise 5: Grep Ignore Case",
        .description = "Extract lines containing 'error' ignoring case from log.txt to case.txt",
        .lab_dir = "labs/ex05",
        .validate = validate_grep_ignore_case,
        .hint = "grep -i error log.txt > case.txt",
        .target_file = "case.txt"
    },
    {
        .id = "grep-06",
        .title = "Exercise 6: Grep Recursive",
        .description = "Search all files in logs/ folder recursively for 'error' and save matches to recursive.txt",
        .lab_dir = "labs/ex06",
        .validate = validate_grep_recursive,
        .hint = "grep -r error logs/ > recursive.txt",
        .target_file = "recursive.txt"
    },
    {
        .id = "grep-07",
        .title = "Exercise 7: Grep Invert Match",
        .description = "Extract all lines from log.txt that do NOT contain 'error' into invert.txt",
        .lab_dir = "labs/ex07",
        .validate = validate_grep_invert,
        .hint = "grep -v error log.txt > invert.txt",
        .target_file = "invert.txt"
    },
    {
        .id = "grep-08",
        .title = "Exercise 8: Grep Combo",
        .description = "Extract all lines from log.txt that do NOT contain 'error' ignoring case, save to combo.txt",
        .lab_dir = "labs/ex08",
        .validate = validate_grep_combo,
        .hint = "grep -vi error log.txt > combo.txt",
        .target_file = "combo.txt"
    }


};

const int exercise_count = sizeof(exercises) / sizeof(exercises[0]);
