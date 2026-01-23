// screens.c
#include "screens.h"
#include "helpers.h"
#include <ncurses.h>
#include "exercises.h"
#include <string.h>

void show_success(void) {
    clear();
    mvprintw(5, 5, "Success!");
    mvprintw(7, 5, "You completed the exercise correctly.");
    mvprintw(9, 5, "Press any key to continue.");
    refresh();
}

void show_instructions(const Exercise *ex) {
    clear();
    mvprintw(5, 5, "%s", ex->title);
    mvprintw(7, 5, "%s", ex->description);
    print_bottomleft(stdscr, 0, "Press S for shell, ENTER when done, ESC to quit");
    refresh();
}

void show_failure(const char *hint) {
    clear();
    mvprintw(5, 5, "Not quite.");
    mvprintw(7, 5, "Hint: %s", hint);
    mvprintw(9, 5, "Press any key to retry.");
    refresh();
}

void show_title(void) {
    clear();
    print_center_auto(stdscr, 5, "CompTIA Linux+ text and file exercises");
    print_center_auto(stdscr, 9, "By Thomas Walsh");
    print_bottomleft(stdscr, 0, "Press ENTER when done, ESC to quit");
    refresh();
}

void show_explanation(void) {
    clear();
    print_center_auto(stdscr, 2, "How this works:");
    print_center_auto(stdscr, 4, "Follow the instructions and enter the corresponding commands to complete exercises.");
    print_bottomleft(stdscr, 0, "Press ENTER when done, ESC to quit, R to reset all labs");
    refresh();
}
