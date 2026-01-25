#ifndef RUNNER_H
#define RUNNER_H

#include "../exercises.h"
#include "app_state.h"

// Global variable for the project root
extern char project_root[512];

/**
 * Initializes the project root
 */
void init_project_root(void);

// Generic runner for any exercise
ExerciseResult run_exercise(const Exercise *ex);

/**
 * Launch a "sandbox version of the shell"
 */
void launch_shell(void);

int run_exercise_menu(void);

int run_exercise_list(void);

int run_exercise_selected_menu(Exercise *ex);


// road-to-v0.2.0
Exercise* run_exercise_list_and_select(int *selected_index);

#endif
