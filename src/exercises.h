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
} Exercise;

extern Exercise exercises[];
extern const int exercise_count;

#endif
