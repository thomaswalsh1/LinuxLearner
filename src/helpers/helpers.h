// helpers.h
#ifndef HELPERS_H
#define HELPERS_H

#include <ncurses.h>

// Centered printing
void print_center(WINDOW *win, int y, const char *text);
void print_center_multiline(WINDOW *win, int start_y, const char *text);
void print_center_auto(WINDOW *win, int start_y, const char *text);

// Left printing
void print_left_auto(WINDOW *win, int start_y, const char *text);

// Corner printing
void print_topleft(WINDOW *win, int y, int x, const char *text);
void print_topright(WINDOW *win, int y, const char *text);
void print_bottomleft(WINDOW *win, int y, const char *text);
void print_bottomright(WINDOW *win, int y, const char *text);

// print input options
enum Option {
    SHELL, EXIT, CONTINUE, VIEW_EXERCISES, VALIDATE, MENU, RETURN_INSTRUCTIONS, RETURN_MENU, RESET_ALL, OPTIONS_END 
};
void print_options(WINDOW *win, const enum Option options[]);

void return_cursor(WINDOW *win);

void print_border_line(WINDOW *win, int y);

#endif
