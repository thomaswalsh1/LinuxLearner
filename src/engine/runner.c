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
        if (ch == 's' || ch == 'S') launch_shell();
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
    }
}

void launch_shell(void) {
    def_prog_mode(); // prog mode
    endwin(); // close out

    // introduce the shell to the user
    printf("\n--- LAB SHELL ---\n");
    printf("Type your commands. Type 'exit' to return.\n\n");
    system(getenv("SHELL") ? getenv("SHELL") : "/bin/sh");

    reset_prog_mode();
    refresh();
}

int run_title(void) {
    int ch;
    // first menu, name and title
    clear();
    print_center(stdscr, 2, "CompTIA Linux+ text and file exercises");
    print_center_multiline(stdscr, 4, "By Thomas Walsh");
    print_bottomleft(stdscr, 0, "Press ENTER when done, ESC to quit");
    refresh();

    while (1) {
        ch = getch();
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
    }
}

int run_explanation(void) {
    int ch;
    // explanation menu
    clear();
    print_center(stdscr, 2, "How this works:");
    print_center_multiline(stdscr, 4, "Follow the instructions and enter the corresponding commands to complete exercises.");
    print_bottomleft(stdscr, 0, "Press ENTER when done, ESC to quit, R to reset all labs");
    refresh();

    while (1) {
        ch = getch();
        if (ch == 27) return ACTION_EXIT;
        if (ch == '\n' || ch == KEY_ENTER) return ACTION_CONTINUE;
        if (ch == 'r' || ch == 'R') {
            reset_all_output_files();
            return ACTION_EXIT;
        }
    }
}
