#include "runner.h"
#include "helpers.h"
#include "screens.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

char project_root[512];

void init_project_root(void) {
    if (!getcwd(project_root, sizeof(project_root))) { // assign to the project root buffer
        perror("getcwd");
        exit(1);
    }
}

void reset_all_output_files(void) {
    if (chdir(project_root) != 0) {
        perror("reset_all_output_files: chdir project_root");
        return;
    }
    for (int i = 0; i < exercise_count; i++) {
        const Exercise *ex = &exercises[i];
        // reduntant checking for target file on object
        if (!ex->target_file || strlen(ex->target_file) == 0) {
            continue;
        }
        // check for lab directory
        if (chdir(ex->lab_dir) != 0) {
            perror("reset_all_output_files: chdir lab_dir");
            chdir(project_root);
            continue;
        }
        // attempt to remove
        if (remove(ex->target_file) == 0) {
            printf("%s : target file %s removed. \n", ex->title, ex->target_file);
        } else {
            printf("%s : failed to remove target file %s \n", ex->title, ex->target_file);
        }
        chdir(project_root);
    }
}

int run_exercise(const Exercise *ex) {
    int ch;

    // reset to lab directory
    if (chdir(project_root) != 0) {
        perror("chdir to project root");
        return ACTION_EXIT;
    }

    // change to exercise sandbox
    if (chdir(ex->lab_dir) != 0) {
        perror("chdir to correct exercise");
        return ACTION_EXIT;
    }

    // write the instructions
    show_instructions(ex);

    // track input
    while (1) {
        ch = getch();
        if (ch == KEY_RESIZE) {
            show_instructions(ex);
        }
        if (ch == 's' || ch == 'S') launch_shell();
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
    }
}

void launch_shell(void) {
    def_prog_mode(); // prog mode
    endwin(); // close out

    // introduce the shell to the user
    system("clear");
    printf("\n--- LAB SHELL ---\n");
    printf("Type your commands. Type 'exit' to return.\n\n");
    printf("If the command doesn't respond, use ctrl + c to stop it and try again.\n\n");
    system(getenv("SHELL") ? getenv("SHELL") : "/bin/sh");

    reset_prog_mode();
    refresh();
}

int run_title(void) {
    int ch;
    // first menu, name and title
    show_title();

    while (1) {
        ch = getch();
        if (ch == KEY_RESIZE) { // handle resizing
            show_title();
        }
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
    }
}

int run_explanation(void) {
    int ch;
    // explanation menu
    show_explanation();

    while (1) {
        ch = getch();
        if (ch == KEY_RESIZE) {
            show_explanation();
        }
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
        if (ch == 'r' || ch == 'R') {
            reset_all_output_files();
            int secondary_action = show_outputs_reset();
            if (secondary_action == ACTION_CONTINUE) {
                show_explanation();
            } else { // exit
                return ACTION_EXIT;
            }
        }
        if (ch == 'm' || ch == 'M') {
            int menu_action = run_exercise_menu();
            if (menu_action == ACTION_EXIT) {
                show_explanation();
            }
            continue;
        }
    }
}

int run_exercise_menu(void) {
    int ch;
    show_exercise_menu();
    while(1) {
        ch = getch();
        if (ch == KEY_RESIZE) {
            show_exercise_menu();
        }
        if (ch == 127 || ch == KEY_BACKSPACE) {
            return ACTION_EXIT;
        }
        if (ch == 'v' || ch == 'V') {
            int list_action = run_exercise_list();
            if (list_action == ACTION_EXIT) {
                show_exercise_menu();
            }
        }
    }
}

int run_exercise_list(void) {
    int ch;

    int border_top = 4;
    int border_bottom = LINES - 5;

    int top_index = 0;

    int possible_exercise_spots = border_bottom - border_top;
    show_exercise_list_commentary(border_top, border_bottom);

    show_exercise_list_contents(exercises, border_top, border_bottom, 0, 0, possible_exercise_spots);
    while(1) {
        ch = getch();
        if (ch == KEY_RESIZE) {
            border_bottom = LINES - 5;
            show_exercise_list_commentary(border_top, border_bottom);
            possible_exercise_spots = border_bottom - border_top;
            show_exercise_list_contents(exercises, border_top, border_bottom, 0, 0, possible_exercise_spots);
        }
        if (ch == 127 || ch == KEY_BACKSPACE) {
            return ACTION_EXIT;
        }
    }
}
