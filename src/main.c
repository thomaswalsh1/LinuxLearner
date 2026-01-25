#include <ncurses.h>
#include <stdlib.h>
#include <errno.h>
#include "exercises.h"
#include "config/config_parser.h"
#include "engine/runner.h"
#include "ui/screens.h"
#include "app_state.h"

int main(void)
{
    // ncurses initialization
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0); // hide the cursor

    // initializing project root
    init_project_root();

    ExerciseList exercise_list = load_exercises_from_all();
    exercises = exercise_list.exercises; // unloading exercises to global variable
    exercise_count = exercise_list.count;
    
    // app state
    AppState current_app_state = APP_TITLE;

    // exercise state
    Exercise *current_exercise = NULL;
    int current_exercise_index = 0;

    // main loop
    while (current_app_state != APP_EXIT)
    {
        int ch;
        switch (current_app_state)
        {

        case APP_TITLE:
            show_title();
            ch = getch();
            if (ch == KEY_RESIZE)
                show_title();
            if (ch == 27)
                current_app_state = APP_EXIT;
            if (ch == '\n' || ch == KEY_ENTER)
                current_app_state = APP_MAIN_MENU;
            break;
        case APP_MAIN_MENU:
            show_main_menu();
            ch = getch();
            if (ch == KEY_RESIZE)
                show_main_menu();
            if (ch == 27)
                current_app_state = APP_EXIT;
            if (ch == '\n' || ch == KEY_ENTER)
                current_app_state = APP_EXIT;
            if (ch == 'h' || ch == 'H')
                current_app_state = APP_EXPLANATION;
            if (ch == 'v' || ch == 'V')
                current_app_state = APP_EXERCISE_LIST;
            break;
        case APP_EXPLANATION:
            show_explanation();
            ch = getch();
            if (ch == KEY_RESIZE)
                show_explanation();
            if (ch == 127 || ch == KEY_BACKSPACE)
                current_app_state = APP_MAIN_MENU;
            break;
        case APP_EXERCISE_LIST:
            current_exercise = run_exercise_list_and_select(&current_exercise_index);
            if (current_exercise != NULL)
            {
                current_app_state = APP_EXERCISE;
            }
            else
            {
                current_app_state = APP_MAIN_MENU;
            }
            break;
        case APP_EXERCISE:
            break;
        default:
            current_app_state = APP_EXIT;
        }
    }

    endwin();
    return 0;
}
