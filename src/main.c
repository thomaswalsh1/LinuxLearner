#include <ncurses.h>
#include <stdlib.h>
#include <errno.h>
#include "exercises.h"
#include "config/config_parser.h"
#include "engine/runner.h"
#include "ui/screens.h"
#include "app_state.h"

int last_top_index = 0;

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
            last_top_index = 0;
            show_main_menu();
            ch = getch();
            if (ch == KEY_RESIZE)
                show_main_menu();
            if (ch == 27)
                current_app_state = APP_EXIT;
            if (ch == '\n' || ch == KEY_ENTER)
                current_app_state = APP_EXERCISE;
            if (ch == 'h' || ch == 'H')
                current_app_state = APP_EXPLANATION;
            if (ch == 'v' || ch == 'V')
                current_app_state = APP_EXERCISE_LIST;
            if (ch == 's' || ch == 'S')
                current_app_state = APP_SETTINGS;
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
                current_app_state = APP_EXERCISE_METADATA;
            }
            else
            {
                current_app_state = APP_MAIN_MENU;
            }
            break;
        case APP_EXERCISE_METADATA:
            show_exercise_selected_menu(current_exercise);
            ch = getch();
            if (ch == KEY_RESIZE)
                show_exercise_selected_menu(current_exercise);
            if (ch == 127 || ch == KEY_BACKSPACE)
                current_app_state = APP_EXERCISE_LIST;
            if (ch == '\n' || ch == KEY_ENTER)
                current_app_state = APP_EXERCISE;
            if (ch == 'e' || ch == 'E')
            {
                int enabled = current_exercise->is_enabled;
                current_exercise->is_enabled = 1 - enabled;
                show_exercise_selected_menu(current_exercise);
            }
            if (ch == 'r' || ch == 'R') {
                reset_single_exercise(current_exercise);
                show_exercise_selected_menu(current_exercise);
            }
            break;
        case APP_EXERCISE:
            if (current_exercise == NULL)
                current_exercise = &exercises[current_exercise_index];
            while (current_exercise->is_completed == 1) {
                current_exercise = &exercises[++current_exercise_index];
            }
            ExerciseResult result = run_exercise(current_exercise);
            if (result == ACTION_CONTINUE)
            {
                int next_index = current_exercise_index + 1;
                while (next_index < exercise_count && !(exercises[next_index].is_enabled == 0))
                    next_index++;

                if (next_index < exercise_count)
                {
                    current_exercise = &exercises[next_index];
                    current_exercise_index = next_index;
                    current_app_state = APP_EXERCISE;
                }
                else
                {
                    current_app_state = APP_MAIN_MENU;
                }
            }
            else if (result == ACTION_RETURN)
            {
                current_app_state = APP_MAIN_MENU;
            }
            else if (result == ACTION_EXIT)
            {
                current_app_state = APP_EXIT;
            }
            else if (result == ACTION_RETRY)
            {
                current_app_state = APP_EXERCISE;
            }
            break;
        case APP_SETTINGS:
            show_settings();
            ch = getch();
            if (ch == KEY_RESIZE)
            {
                show_settings();
            }
            if (ch == 127 || ch == KEY_BACKSPACE)
            {
                current_app_state = APP_MAIN_MENU;
            }
            if (ch == 'r' || ch == 'R')
            {
                int ch2;
                show_reset_confirmation_screen();

                while (1)
                {
                    ch2 = getch();
                    if (ch2 == KEY_RESIZE)
                    {
                        show_reset_confirmation_screen();
                    }
                    if (ch2 == '\n' || ch2 == KEY_ENTER)
                    {
                        reset_all_output_files();
                        break;
                    }
                    if (ch2 == 127 || ch2 == KEY_BACKSPACE)
                    {
                        break;
                    }
                }
            }
            break;
        default:
            current_app_state = APP_EXIT;
        }
    }

    endwin();
    return 0;
}
