// screens.h
#ifndef SCREENS_H
#define SCREENS_H

#include "exercises.h"

/**
 * UI helper function that displays the success page
 */
int show_success(void);

/**
 * UI helper function that displays the instructions for an assignment
 */
void show_instructions(const Exercise *ex);

/**
 * UI helper function that displays the failure page
 */
int show_failure(const char *hint);

void show_title(void);

void show_explanation(void);

void show_exercise_selection(void);

int show_outputs_reset(void);

void show_exercise_menu(void);

void show_exercise_list_commentary(int top_window_border, int bottom_window_border);

void show_exercise_list_contents(Exercise *viewable_exercises, int top_window_border, int bottom_window_border, int selected_index, int top_index, int per_page);

void show_selected(int curr, int top_window_border);

#endif
