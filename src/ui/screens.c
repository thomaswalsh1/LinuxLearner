// screens.c
#include "screens.h"
#include "helpers.h"
#include <ncurses.h>
#include "exercises.h"
#include <string.h>
#include "runner.h"
#include <stdlib.h>
#include <errno.h>

int show_success(void) {
    while(1) {
        clear();
        print_left_auto(stdscr, 5, "Success!");
        print_left_auto(stdscr, 7, "You completed the exercise correctly.");
        print_left_auto(stdscr, 9, "Press any key to continue.");
        refresh();

        int ch = getch();
        if (ch == KEY_RESIZE) {
            continue; // redraw on resize
        } else if (ch == 27) { // ESC
            return ACTION_EXIT;
        }
        return ACTION_CONTINUE;

    }
}

int show_failure(const char *hint) {
    clear();
    print_center_auto(stdscr, 5, "Not quite.");
    char hint_str[256] = "Hint: ";
    strcat(hint_str, hint);
    print_center_auto(stdscr, 7, hint_str);
    print_center_auto(stdscr, 9, "Press SPACE to retry or ESC to quit.");
    refresh();
    
    int ch = getch();
    if (ch == 27) { // ESC
        return ACTION_EXIT;
    }
    return ACTION_RETRY;
}

void show_instructions(const Exercise *ex) {
    clear();
    print_left_auto(stdscr, 5, ex->title);
    print_left_auto(stdscr, 7, ex->description);
    print_bottomleft(stdscr, 0, "Press S for shell, ENTER when done, ESC to quit");
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
