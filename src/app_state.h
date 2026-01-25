#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum {
    APP_EXIT,
    APP_TITLE,
    APP_EXPLANATION,
    APP_MAIN_MENU,
    APP_EXERCISE_LIST,
    APP_EXERCISE,
    APP_SETTINGS
} AppState;

typedef enum {
    ACTION_CONTINUE_A,
    ACTION_RETURN_A,
    ACTION_EXIT_A
} ExerciseResult;

#endif