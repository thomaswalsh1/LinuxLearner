#include <ncurses.h>
#include <stdlib.h>
#include "exercises.h"
#include "config/config_parser.h"
#include "engine/runner.h"
#include "ui/screens.h"

int main(void) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    init_project_root();

    // Load exercises from config files
    ExerciseList exercise_list = load_exercises_from_config("labs_reprise/grep/config");
    exercises = exercise_list.exercises;
    exercise_count = exercise_list.count;

    if (exercise_count == 0) {
        endwin();
        fprintf(stderr, "Failed to load exercises from config files\n");
        return 1;
    }

    int title_status = run_title();
    if (title_status == ACTION_EXIT) {
        endwin();
        free_exercise_list(exercise_list);
        return 0;
    }
    int explanation_status = run_explanation();
    if (explanation_status == ACTION_EXIT){
        endwin();
        free_exercise_list(exercise_list);
        return 0;
    }

    for (int i = 0; i < exercise_count; i++) {
        // printf("i is: %d", i);
        int action = run_exercise(&exercises[i]); // we run the exercise according to the exercise array
        if (action == ACTION_EXIT) break;

        if (exercises[i].validate())
            show_success();
        else {
            show_failure(exercises[i].hint);
            i--; // retry same exercise
        }

        getch(); // wait before next exercise
    }

    free_exercise_list(exercise_list);
    endwin();
    return 0;
}
