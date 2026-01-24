// exercises.h
#ifndef EXERCISES_H
#define EXERCISES_H

typedef struct {
    const char *id;
    const char *title;
    const char *description;
    const char *lab_dir;
    int (*validate)(void);
    const char *hint;
    const char *target_file;
    int is_enabled;
} Exercise;

// Global exercises array and count
extern Exercise *exercises;
extern int exercise_count;

#endif
