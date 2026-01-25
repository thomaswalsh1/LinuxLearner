#ifndef RUNNER_H
#define RUNNER_H

#include "../exercises.h"

#define ACTION_EXIT 0
#define ACTION_CONTINUE 1
#define ACTION_RETRY 2

// Global variable for the project root
extern char project_root[512];

/**
 * Initializes the project root
 */
void init_project_root(void);

// Generic runner for any exercise
int run_exercise(const Exercise *ex);

/**
 * Run the title screen
 * @return message of success or exit
 */
int run_title(void);

/**
 * Run the explanation menu
 * @return menu option
 */
int run_explanation(void);

/**
 * Launch a "sandbox version of the shell"
 */
void launch_shell(void);

int run_exercise_menu(void);

int run_exercise_list(void);

int run_exercise_selected_menu(Exercise *ex);

#endif
