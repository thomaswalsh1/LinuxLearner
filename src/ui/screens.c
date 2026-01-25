// screens.c
#include "screens.h"
#include "helpers.h"
#include <ncurses.h>
#include "exercises.h"
#include <string.h>
#include "runner.h"
#include <stdlib.h>
#include <errno.h>

#define GRID_COLS 3
#define CELL_WIDTH 25
#define CELL_HEIGHT 3

int show_success(void)
{
    while (1)
    {
        clear();
        print_left_auto(stdscr, 5, "Success!");
        print_left_auto(stdscr, 7, "You completed the exercise correctly.");
        print_left_auto(stdscr, 9, "Press any key to continue.");
        return_cursor(stdscr);
        refresh();

        int ch = getch();
        if (ch == KEY_RESIZE)
        {
            continue; // redraw on resize
        }
        else if (ch == 27)
        { // ESC
            return ACTION_EXIT;
        }
        return ACTION_CONTINUE;
    }
}

int show_failure(const char *hint)
{
    int show_hint = 0;
    while (1)
    {
        clear();
        print_left_auto(stdscr, 5, "Not quite.");
        char hint_str[256] = "Hint: ";
        strcat(hint_str, hint);
        if (show_hint)
            print_left_auto(stdscr, 7, hint_str);
        print_left_auto(stdscr, 9, "Press ENTER to retry, ESC to quit, or H for a hint.");
        return_cursor(stdscr);
        refresh();

        int ch = getch();
        if (ch == KEY_RESIZE)
        {
            continue; // redraw on resize
        }
        if (ch == 27)
        { // ESC
            return ACTION_EXIT;
        }
        if (ch == 'h' || ch == 'H')
        {
            show_hint = 1;
            continue;
        }
        return ACTION_RETRY;
    }
}

void show_instructions(const Exercise *ex)
{
    const enum Option options[] = {EXIT, VALIDATE, SHELL, OPTIONS_END};
    clear();
    print_left_auto(stdscr, 5, ex->title);
    print_left_auto(stdscr, 7, ex->description);
    print_options(stdscr, options);
    refresh();
}

void show_title(void)
{
    const enum Option options[] = {EXIT, CONTINUE, OPTIONS_END};
    clear();
    print_center_auto(stdscr, 5, "CompTIA Linux+ text and file exercises");
    print_center_auto(stdscr, 9, "By Thomas Walsh");
    print_options(stdscr, options);
    refresh();
}

// void show_explanation(void)
// {
//     const enum Option options[] = {RESET_ALL, MENU, EXIT, CONTINUE, OPTIONS_END};
//     clear();
//     print_center_auto(stdscr, 2, "How this works:");
//     print_center_auto(stdscr, 4, "Follow the instructions and enter the corresponding commands to complete exercises.");
//     print_options(stdscr, options);
//     refresh();
// }

int show_outputs_reset(void)
{
    while (1)
    {
        clear();
        print_left_auto(stdscr, 5, "All output files have been reset.");
        print_left_auto(stdscr, 7, "You can now go through all of the exercises again.");
        print_bottomleft(stdscr, 0, "ENTER when done, ESC to quit");
        refresh();

        int ch = getch();
        if (ch == KEY_RESIZE)
        {
            continue; // redraw on resize
        }
        if (ch == 27)
        { // ESC
            return ACTION_EXIT;
        }
        return ACTION_CONTINUE;
    }
}

void show_exercise_menu(void)
{
    const enum Option options[] = {RETURN_INSTRUCTIONS, VIEW_EXERCISES, OPTIONS_END};
    clear();
    print_left_auto(stdscr, 5, "This is the exercise menu.");
    print_left_auto(stdscr, 7, "Here you can jump to an exercise by viewing the exercise list.");
    print_options(stdscr, options);
    refresh();
}

void show_exercise_list_commentary(int top_window_border, int bottom_window_border)
{
    const enum Option options[] = {RETURN_MENU, GENERATE_RANDOM, SELECT_EXERCISE, OPTIONS_END};

    clear();
    print_left_auto(stdscr, 1, "This is the exercise list.");
    print_left_auto(stdscr, 2, "Use WASD or the arrow keys to navigate through the exercises.");
    print_border_line(stdscr, top_window_border);
    print_border_line(stdscr, bottom_window_border);
    print_options(stdscr, options);
    refresh();
}

void show_exercise_list_contents(
    Exercise *viewable_exercises,
    int top_window_border,
    int bottom_window_border,
    int selected_index,
    int top_index,
    int per_page)
{
    int y = top_window_border + 1;
    int end = top_index + per_page - 1;
    if (end > exercise_count)
        end = exercise_count;
    
    // Clear only the content area (not the whole screen)
    for (int i = top_index; i < end; i++)
    {
        move(y, 0);
        clrtoeol();  // Clear only this line
        
        if (i == selected_index)
            mvwprintw(stdscr, y, 0, ">");
        mvwprintw(stdscr, y, 2, "%s", viewable_exercises[i].title);
        mvwprintw(stdscr, y, 40, "%s", viewable_exercises[i].lab_dir);
        mvwprintw(stdscr, y, 60, "%s", viewable_exercises[i].is_enabled ? "on" : "off");
        y++;
    }
    
    return_cursor(stdscr);
    refresh();  // Single refresh after all updates
}

void show_exercise_selected_menu(Exercise *ex) {
    const enum Option options[] = {RETURN_MENU, ABLE_EXERCISE, OPTIONS_END};

    clear();
    char description_line[256];
    char enabled_line[256];
    char directory_line[256];
    snprintf(description_line, sizeof(description_line), "Description: %s", ex->description);
    snprintf(enabled_line, sizeof(enabled_line), "Enabled: %s", ex->is_enabled? "On" : "Off");
    snprintf(directory_line, sizeof(directory_line), "Dirrectory: %s", ex->lab_dir);
    print_left_auto(stdscr, 5, ex->title);
    print_left_auto(stdscr, 7, description_line);
    print_left_auto(stdscr, 9, enabled_line);
    print_left_auto(stdscr, 11, directory_line);
    print_options(stdscr, options);

    refresh();
}

// road-to-v0.2.0
void show_main_menu(void) {
    const enum Option options[] = {EXIT, VIEW_INSTRUCTIONS, VIEW_SETTINGS, VIEW_EXERCISES, RUN_CURRENT_EXERCISES, OPTIONS_END};
    clear();
    print_left_auto(stdscr, 5, "Main Menu");
    print_left_auto(stdscr, 7, "Welcome to the main menu of LinuxLearner.");
    print_options(stdscr, options);
    refresh();
}

void show_explanation(void)
{
    const enum Option options[] = {RETURN_MENU, OPTIONS_END};
    clear();
    print_center_auto(stdscr, 2, "How this works:");
    print_center_auto(stdscr, 4, "Follow the instructions and enter the corresponding commands to complete exercises.");
    print_options(stdscr, options);
    refresh();
}