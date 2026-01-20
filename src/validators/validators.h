#ifndef VALIDATORS_H
#define VALIDATORS_H

// Generic reusable validators
int file_exists(const char *path);
int file_contains(const char *path, const char *needle);

// Grep validators
int validate_grep_count(void);
int validate_grep_dir_skip(void);
int validate_grep_extended(void);
int validate_grep_ignore_case(void);
int validate_grep_recursive(void);
int validate_grep_invert(void);
int validate_grep_combo(void);

#endif
