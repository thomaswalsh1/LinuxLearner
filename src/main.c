#include <ncurses.h>
#include <stdlib.h>
#include "exercises.h"
#include "config/config_parser.h"
#include "engine/runner.h"
#include "ui/screens.h"

int main(void) {
    // ncurses initialization
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    // initializing project root
    init_project_root();

    // generate exercise list from configuration files
    // warning from 01/20/26: hardcoded path, should change in future versions
    ExerciseList exercise_list = load_exercises_from_config("labs_reprise/grep/config");
    exercises = exercise_list.exercises; // unloading exercises to global variable
    exercise_count = exercise_list.count; // unloading exercise count to global variable

    if (exercise_count == 0) {
        endwin();
        fprintf(stderr, "Failed to load exercises from config files\n");
        return 1;
    }

    int title_status = run_title();
    if (title_status == ACTION_EXIT) {
        endwin();
        free_exercise_list(exercise_list); // free allocated memory using utility function
        return 0;
    }
    int explanation_status = run_explanation();
    if (explanation_status == ACTION_EXIT){
        endwin();
        free_exercise_list(exercise_list); // free allocated memory using utility function
        return 0;
    }

    for (int i = 0; i < exercise_count; i++) {
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
