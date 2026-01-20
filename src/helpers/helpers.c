#include "helpers.h"
#include <string.h>
#include <stdio.h>

void print_center(WINDOW *win, int y, const char *text) {
    int x = (COLS - strlen(text)) / 2;
    mvwprintw(win, y, x, "%s", text);
}

void print_center_multiline(WINDOW *win, int start_y, const char *text) {
    // Split text on \n and call print_center for each line
    int y = start_y;
    char buffer[1024];
    int i = 0, j = 0;
    while (text[i]) {
        if (text[i] == '\n') {
            buffer[j] = '\0';
            print_center(win, y++, buffer);
            j = 0;
        } else {
            buffer[j++] = text[i];
        }
        i++;
    }
    if (j > 0) buffer[j] = '\0', print_center(win, y, buffer);
}

void print_topleft(WINDOW *win, int y, int x, const char *text) {
    mvwprintw(win, y, x, "%s", text);
}

void print_topright(WINDOW *win, int y, const char *text) {
    int x = COLS - strlen(text) - 1;
    mvwprintw(win, y, x, "%s", text);
}

void print_bottomleft(WINDOW *win, int y, const char *text) {
    mvwprintw(win, LINES - y - 1, 0, "%s", text);
}

void print_bottomright(WINDOW *win, int y, const char *text) {
    int x = COLS - strlen(text) - 1;
    mvwprintw(win, LINES - y - 1, x, "%s", text);
}
