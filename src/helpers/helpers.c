#include "helpers.h"
#include <string.h>
#include <stdio.h>

void print_center(WINDOW *win, int y, const char *text) {
    int x = (COLS - strlen(text)) / 2;
    mvwprintw(win, y, x, "%s", text);
}

void print_center_auto(WINDOW *win, int start_y, const char *text) {
    int max_width = COLS - 4;   // margins
    int y = start_y;

    char line[1024] = "";
    int line_len = 0;

    const char *p = text;

    while (*p) {
        // Skip spaces
        while (*p == ' ') p++;

        // Extract a word
        char word[256];
        int wlen = 0;
        while (*p && *p != ' ') {
            word[wlen++] = *p++;
        }
        word[wlen] = '\0';

        if (wlen == 0)
            break;

        // If word won't fit on the current line, print line first
        if (line_len > 0 && line_len + 1 + wlen > max_width) {
            print_center(win, y++, line);
            line[0] = '\0';
            line_len = 0;
        }

        // If word is longer than max width, force-break it
        if (wlen > max_width) {
            if (line_len > 0) {
                print_center(win, y++, line);
                line[0] = '\0';
                line_len = 0;
            }

            for (int i = 0; i < wlen; i += max_width) {
                char chunk[256];
                int len = (wlen - i > max_width) ? max_width : wlen - i;
                strncpy(chunk, word + i, len);
                chunk[len] = '\0';
                print_center(win, y++, chunk);
            }
            continue;
        }

        // Append word to line
        if (line_len > 0) {
            strcat(line, " ");
            line_len++;
        }
        strcat(line, word);
        line_len += wlen;
    }

    // Print remaining text
    if (line_len > 0) {
        print_center(win, y, line);
    }
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
