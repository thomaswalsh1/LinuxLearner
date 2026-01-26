#include "runner.h"
#include "helpers.h"
#include "screens.h"
#include "app_state.h"
#include "config_parser.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

char project_root[512];

void init_project_root(void)
{
    if (!getcwd(project_root, sizeof(project_root)))
    { // assign to the project root buffer
        perror("getcwd");
        exit(1);
    }
}

void mark_complete(Exercise *ex)
{
    // change in memory
    ex->is_completed = 1;
    // now change on disk
    modify_exercise_data(ex, MARK_EX_COMPLETE);
};

void mark_incomplete(Exercise *ex)
{
    // change in memory
    ex->is_completed = 0;
    // now change on disk
    modify_exercise_data(ex, MARK_EX_INCOMPLETE);
}

void reset_all_output_files(void)
{
    if (chdir(project_root) != 0)
    {
        perror("reset_all_output_files: chdir project_root");
        return;
    }
    for (int i = 0; i < exercise_count; i++)
    {
        const Exercise *ex = &exercises[i];

        mark_incomplete(ex);

        // reduntant checking for target file on object
        if (!ex->target_file || strlen(ex->target_file) == 0)
        {
            continue;
        }
        // check for lab directory
        if (chdir(ex->lab_dir) != 0)
        {
            perror("reset_all_output_files: chdir lab_dir");
            chdir(project_root);
            continue;
        }
        // attempt to remove
        if (remove(ex->target_file) == 0)
        {
            printf("%s : target file %s removed. \n", ex->title, ex->target_file);
        }
        else
        {
            printf("%s : failed to remove target file %s \n", ex->title, ex->target_file);
        }
        chdir(project_root);
    }
}

void reset_single_exercise(Exercise *ex)
{
    if (chdir(project_root) != 0)
    {
        perror("reset_all_output_files: chdir project_root");
        return;
    }
    mark_incomplete(ex);

    if (!ex->target_file || strlen(ex->target_file) == 0)
        return;
    // check for lab directory
    if (chdir(ex->lab_dir) != 0)
    {
        perror("reset_all_output_files: chdir lab_dir");
        chdir(project_root);
        return;
    }
    // attempt to remove
    if (remove(ex->target_file) == 0)
        printf("%s : target file %s removed. \n", ex->title, ex->target_file);
    else
        printf("%s : failed to remove target file %s \n", ex->title, ex->target_file);
    chdir(project_root);
}

ExerciseResult run_exercise(const Exercise *ex)
{
    if (ex->is_enabled == 0)
    {
        return ACTION_SKIP;
    }

    int ch;

    // reset to lab directory
    if (chdir(project_root) != 0)
    {
        perror("chdir to project root");
        return ACTION_EXIT;
    }

    // change to exercise sandbox
    if (chdir(ex->lab_dir) != 0)
    {
        perror("chdir to correct exercise");
        return ACTION_EXIT;
    }

    // write the instructions
    show_instructions(ex);

    // track input
    while (1)
    {
        ch = getch();
        if (ch == KEY_RESIZE)
        {
            show_instructions(ex);
        }
        if (ch == 's' || ch == 'S')
            launch_shell();
        if (ch == 27)
            return ACTION_EXIT;
        if (ch == 127 || ch == KEY_BACKSPACE)
            return ACTION_RETURN;
        if (ch == '\n' || ch == KEY_ENTER)
            if (ex->validate())
            {
                // success
                mark_complete(ex);
                return show_success();
            }
            else
            {
                // fail
                return show_failure(ex->hint);
            }
    }
}

void launch_shell(void)
{
    def_prog_mode(); // prog mode
    endwin();        // close out

    // introduce the shell to the user
    system("clear");
    printf("\n--- LAB SHELL ---\n");
    printf("\n\nYou are now using your shell within the exercise's directory.");
    printf("\nOnly use the commands needed for the exercise.\n\n");
    printf("Type your commands. Type 'exit' to return.\n\n");
    printf("If the command doesn't respond, use ctrl + c to stop it and try again.\n\n");
    system(getenv("SHELL") ? getenv("SHELL") : "/bin/sh");

    reset_prog_mode();
    refresh();
}

Exercise *run_exercise_list_and_select(int *selected_index)
{
    int ch;
    int top_index = last_top_index;
    int border_top = 4;
    int border_bottom = LINES - 5;
    int visible_spots = border_bottom - border_top - 1;
    int current_index = *selected_index;

    // Initial draw - draw everything once
    show_exercise_list_commentary(border_top, border_bottom);
    show_exercise_list_contents(exercises, border_top, border_bottom,
                                current_index, top_index, visible_spots);

    int needs_redraw = 0;
    while (1)
    {
        ch = getch();

        if (ch == KEY_UP || ch == 'w' || ch == 'W')
        {
            if (current_index > 0)
            {
                current_index--;
                needs_redraw = 1;
            }
            if (current_index < top_index)
            {
                top_index--;
                needs_redraw = 1;
            }
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
        {
            if (current_index < exercise_count - 1)
            {
                current_index++;
                needs_redraw = 1;
            }
            if (current_index >= top_index + visible_spots)
            {
                top_index++;
                needs_redraw = 1;
            }
        }
        else if (ch == '\n' || ch == KEY_ENTER)
        {
            *selected_index = current_index;
            last_top_index = top_index;
            return &exercises[current_index];
        }
        else if (ch == 127 || ch == KEY_BACKSPACE)
        {
            last_top_index = top_index;
            return NULL;
        }
        else if (ch == KEY_RESIZE)
        {
            border_bottom = LINES - 5;
            visible_spots = border_bottom - border_top - 1;
            show_exercise_list_commentary(border_top, border_bottom);
            show_exercise_list_contents(exercises, border_top, border_bottom,
                                        current_index, top_index, visible_spots);
        }

        // Only redraw what changed
        if (needs_redraw)
        {
            // Only redraw the contents, not the commentary
            show_exercise_list_contents(exercises, border_top, border_bottom,
                                        current_index, top_index, visible_spots);
        }
    }
}