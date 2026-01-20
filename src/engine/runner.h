#ifndef RUNNER_H
#define RUNNER_H

#include "../exercises.h"

#define ACTION_EXIT 0
#define ACTION_CONTINUE 1

// Global variable for the project root
extern char project_root[512];

// Initializing the project root
void init_project_root(void);

// Generic runner for any exercise
int run_exercise(const Exercise *ex);
int run_title(void);
int run_explanation(void);

// Launch shell in sandbox
void launch_shell(void);

// Reset our sandbox
void reset_lab(const char *lab_dir);

#endif
