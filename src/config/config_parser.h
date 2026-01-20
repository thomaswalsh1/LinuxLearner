#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "../exercises.h"

typedef struct {
    Exercise *exercises;
    int count;
} ExerciseList;


/**
 * Loads all the exercises from directory with config files
 * @return ExerciseList comprised of all the .conf files in labs_reprise
 */
ExerciseList load_exercises_from_all(void);

/**
 * Load all exercises from config files in a directory
 * @param config_dir Directory containing .conf files
 * @return ExerciseList with all loaded exercises
 */
ExerciseList load_exercises_from_config(const char *config_dir);

/**
 * Free the exercise list allocated by load_exercises_from_config
 * @param list The ExerciseList to free
 */
void free_exercise_list(ExerciseList list);

/**
 * Get a validator function pointer by name
 * @param validator_name Name of the validator (e.g., "file_exists")
 * @return Function pointer to the validator, or NULL if not found
 */
int (*get_validator_function(const char *validator_name))(void);


#endif
