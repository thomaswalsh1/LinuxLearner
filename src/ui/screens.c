// screens.c
#include "screens.h"
#include <ncurses.h>

void show_success(void) {
    clear();
    mvprintw(5, 5, "Success!");
    mvprintw(7, 5, "You completed the exercise correctly.");
    mvprintw(9, 5, "Press any key to continue.");
    refresh();
}

void show_failure(const char *hint) {
    clear();
    mvprintw(5, 5, "Not quite.");
    mvprintw(7, 5, "Hint: %s", hint);
    mvprintw(9, 5, "Press any key to retry.");
    refresh();
}
