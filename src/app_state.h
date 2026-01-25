#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum {
    APP_EXIT,
    APP_TITLE,
    APP_EXPLANATION,
    APP_MAIN_MENU,
    APP_EXERCISE_LIST,
    APP_EXERCISE
} AppState;

typedef enum {
    ACTION_CONTINUE,
    ACTION_RETURN,
    ACTION_EXIT
} ExerciseResult;

#endif