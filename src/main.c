#include <ncurses.h>
#include "exercises.h"
#include "engine/runner.h"
#include "ui/screens.h"

int main(void) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    init_project_root();

    int title_status = run_title();
    if (title_status == ACTION_EXIT) {
        endwin();
        return 0;
    }
    int explanation_status = run_explanation();
    if (explanation_status == ACTION_EXIT){
        endwin();
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

    endwin();
    return 0;
}
