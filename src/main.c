#include <ncurses.h>
#include <stdlib.h>
#include <errno.h>
#include "exercises.h"
#include "config/config_parser.h"
#include "engine/runner.h"
#include "ui/screens.h"
#include "app_state.h"


int main(void) {
    // ncurses initialization
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0); // hide the cursor

    // initializing project root
    init_project_root();

    // app state
    AppState current_app_state = APP_TITLE;

    // exercise state
    Exercise *current_exercise = NULL;
    int current_exercise_index = 0;

    // main loop
    while(current_app_state != APP_EXIT) {
        int ch;
        switch(current_app_state) {
            
            case APP_TITLE: 
                break;
            case APP_EXPLANATION:
                break;
            case APP_MAIN_MENU:
                break;
            case APP_EXERCISE_LIST:
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
