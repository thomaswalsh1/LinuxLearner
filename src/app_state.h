#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum {
    APP_EXIT,
    APP_TITLE,
    APP_EXPLANATION,
    APP_MAIN_MENU,
    APP_EXERCISE_LIST,
    APP_EXERCISE,
    APP_EXERCISE_METADATA,
    APP_SETTINGS,
} AppState;

typedef enum {
    ACTION_CONTINUE,
    ACTION_RETURN,
    ACTION_EXIT,
    ACTION_SKIP,
    ACTION_RETRY
} ExerciseResult;

extern int last_top_index;

#endif