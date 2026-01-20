#include "config_parser.h"
#include "../validators/validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_LINE 512
#define MAX_EXERCISES 100

// Validator registry - maps validator names to function pointers
typedef struct {
    const char *name;
    int (*func)(void);
} ValidatorEntry;

static ValidatorEntry validator_registry[] = {
    {"file_exists", validate_grep_basic},
    {"grep_count", validate_grep_count},
    {"grep_dir_skip", validate_grep_dir_skip},
    {"grep_extended", validate_grep_extended},
    {"grep_ignore_case", validate_grep_ignore_case},
    {"grep_recursive", validate_grep_recursive},
    {"grep_invert", validate_grep_invert},
    {"grep_combo", validate_grep_combo},
    {NULL, NULL}
};

int (*get_validator_function(const char *validator_name))(void) {
    if (!validator_name) return NULL;
    
    for (int i = 0; validator_registry[i].name != NULL; i++) {
        if (strcmp(validator_registry[i].name, validator_name) == 0) {
            return validator_registry[i].func;
        }
    }
    return NULL;
}

// Utility function to trim whitespace from strings
static void trim_string(char *str) {
    if (!str) return;
    
    // Trim leading whitespace
    char *start = str;
    while (*start && isspace((unsigned char)*start)) start++;
    
    // Trim trailing whitespace
    char *end = start + strlen(start) - 1;
    while (end >= start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
    
    // Move trimmed string back to original
    memmove(str, start, strlen(start) + 1);
}

// Parse a single .conf file
static Exercise parse_conf_file(const char *filepath) {
    Exercise ex = {0};
    FILE *fp = fopen(filepath, "r");
    
    if (!fp) {
        perror("Failed to open config file");
        return ex;
    }
    
    char line[MAX_LINE];
    char *validator_name = NULL;
    
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines and comments
        if (line[0] == '\0' || line[0] == '#' || line[0] == ';') {
            continue;
        }
        
        // Parse key=value pairs
        char *eq = strchr(line, '=');
        if (!eq) continue;
        
        *eq = '\0';
        char *key = line;
        char *value = eq + 1;
        
        trim_string(key);
        trim_string(value);
        
        if (strcmp(key, "id") == 0) {
            ex.id = strdup(value);
        } else if (strcmp(key, "title") == 0) {
            ex.title = strdup(value);
        } else if (strcmp(key, "description") == 0) {
            ex.description = strdup(value);
        } else if (strcmp(key, "lab_dir") == 0) {
            ex.lab_dir = strdup(value);
        } else if (strcmp(key, "hint") == 0) {
            ex.hint = strdup(value);
        } else if (strcmp(key, "target_file") == 0) {
            ex.target_file = strdup(value);
        } else if (strcmp(key, "validator") == 0) {
            validator_name = strdup(value);
        }
    }
    
    fclose(fp);
    
    // Get validator function pointer from registry
    if (validator_name) {
        ex.validate = get_validator_function(validator_name);
        free(validator_name);
    }
    
    return ex;
}

// Comparison function for sorting .conf files
static int compare_conf_files(const struct dirent **a, const struct dirent **b) {
    return strcmp((*a)->d_name, (*b)->d_name);
}

ExerciseList load_exercises_from_config(const char *config_dir) {
    ExerciseList list = {0};
    struct dirent **namelist;
    int n;
    
    n = scandir(config_dir, &namelist, NULL, compare_conf_files);
    
    if (n < 0) {
        perror("scandir");
        return list;
    }
    
    // Allocate space for exercises
    list.exercises = malloc(sizeof(Exercise) * MAX_EXERCISES);
    if (!list.exercises) {
        fprintf(stderr, "Memory allocation failed\n");
        return list;
    }
    
    list.count = 0;
    
    // Process each .conf file
    for (int i = 0; i < n && list.count < MAX_EXERCISES; i++) {
        if (namelist[i]->d_name[0] != '.' && 
            strlen(namelist[i]->d_name) > 5) {
            
            char *ext = namelist[i]->d_name + strlen(namelist[i]->d_name) - 5;
            if (strcmp(ext, ".conf") == 0) {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", 
                         config_dir, namelist[i]->d_name);
                
                Exercise ex = parse_conf_file(filepath);
                if (ex.id) {
                    list.exercises[list.count++] = ex;
                }
            }
        }
        free(namelist[i]);
    }
    free(namelist);
    
    return list;
}

void free_exercise_list(ExerciseList list) {
    for (int i = 0; i < list.count; i++) {
        if (list.exercises[i].id) free((void *)list.exercises[i].id);
        if (list.exercises[i].title) free((void *)list.exercises[i].title);
        if (list.exercises[i].description) free((void *)list.exercises[i].description);
        if (list.exercises[i].lab_dir) free((void *)list.exercises[i].lab_dir);
        if (list.exercises[i].hint) free((void *)list.exercises[i].hint);
        if (list.exercises[i].target_file) free((void *)list.exercises[i].target_file);
    }
    free(list.exercises);
}
