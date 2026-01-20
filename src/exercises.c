// exercises.c
#include "exercises.h"
#include "validators/validators.h"
#include <stddef.h>
#include <stdlib.h>

// Global exercises array and count - will be initialized by config loader
Exercise *exercises = NULL;
int exercise_count = 0;

