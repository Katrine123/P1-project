#include "workouts_new.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//TODO: Merge this workouts_new.c with the old workouts.c

// General constants
static const int ARRAY_MAX = 32; // 32 simply because it is big enough.

// Enums
typedef enum {
    //TODO: Not implemented yet. Should contain stuff like biceps, triceps, chest, etc.
} muscle_group_name;
typedef enum {
    //TODO: Not implemented yet. Should contain stuff like, bench_press, squat, deadlift, etc.
} exercise_name;

// Structs
typedef struct muscle_group {
    muscle_group_name name;
    struct muscle_group* parent; // Muscle groups in struct exercise refer to muscle groups in struct workout which refers to muscle groups in the global routine variable.
    int sets; // Irrelevant for struct exercise, is daily sets for struct workout, and is weekly sets for the global routine variable.
} muscle_group;
typedef struct {
    exercise_name name;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups targeted by the exercise. Aerobic exercises do not target any specific muscles.
    int sets;
    int is_aerobic; // Is boolean.
    double duration; // In minutes.
    double specific_warmup_duration; // In minutes. Only relevant for resistance training exercises.
} exercise;
typedef struct {
    exercise exercises[ARRAY_MAX]; int exercises_count;
    double duration; double max_duration;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups included in the workout.
} workout;

// For the whole fitness routine
static muscle_group routine_muscles[ARRAY_MAX]; static int routine_muscles_count; // Muscle groups included in the routine.


// Workout rules
const int general_warmup_duration = 5; // In minutes.
const int max_daily_sets = 6; // For resistance training.
int max_weekly_sets; // For resistance training.
int resistance_recovery;
int max_weekly_aerobic_workouts;
int aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.

// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

// Helper functions
static int does_adding_a_set_exceed_daily_or_weekly_set_max(exercise *_exercise) {

    // Foreach muscle group the exercise targets
    for (int i = 0; _exercise->muscles_count; i++) {

        // Declare variables
        muscle_group *exercise_muscle = &_exercise->muscles[i];
        muscle_group *workout_muscle = exercise_muscle->parent;
        muscle_group *routine_muscle = workout_muscle->parent;

        // Exceeds daily set max?
        int new_daily_sets = workout_muscle->sets + 1;
        if (new_daily_sets > max_daily_sets) {
            return 1;
        }

        // Exceeds daily set max?
        int new_weekly_sets = routine_muscle->sets + 1;
        if (new_weekly_sets > max_weekly_sets) {
            return 1;
        }
    }

    // Return false if the checks pass
    return 0;
}
static int does_adding_a_set_exceed_workout_duration_max(exercise *_exercise, workout* _workout) {

    // Does it exceed workout duration max?
    double new_duration = _workout->duration + _exercise->duration;
    if (new_duration > _workout->max_duration) {
        return 1;
    }

    // Return false if the check passes
    return 0;
}
static int does_routine_already_contain_exercise(exercise *_exercise, workout* workouts, int workouts_count) {

    // Foreach workout in the routine
    for (int i = 0; i < workouts_count; i++) {

        // Declare variables
        workout* _workout = &workouts[i];

        // Foreach exercise in the workouts
        for (int j = 0; j < _workout->exercises_count; j++) {

            // Declare variables
            exercise* workout_exercise = &_workout->exercises[j];

            // Is the exercise a duplicate?
            if (workout_exercise->name == _exercise->name) {
                return 1;
            }
        }
    }

    // Return false if the checks passes
    return 0;
}
static void add_set_to_exercise(exercise *_exercise, workout* _workout) {

    // Is exercise aerobic?
    if (!_exercise->is_aerobic) {

        // Add sets to parent muscle groups
        // Foreach muscle group the exercise targets
        for (int i = 0; _exercise->muscles_count; i++) {

            // Declare variables
            muscle_group *exercise_muscle = &_exercise->muscles[i];
            muscle_group *workout_muscle = exercise_muscle->parent;
            muscle_group *routine_muscle = workout_muscle->parent;

            // Add sets to muscle groups
            workout_muscle->sets++;
            routine_muscle->sets++;
        }

        // If sets = 0, then add specific warmup to workout duration
        if (_exercise->sets == 0) {
            _workout->duration += _exercise->specific_warmup_duration;
        }
    }

    // Add to workout duration
    _workout->duration += _exercise->duration;

    // Add set to exercise
    _exercise->sets++;
}
/// @param candidate Output. It is set to NULL if no candidate is found.
static void try_to_find_resistance_exercise_candidate(exercise* candidate, muscle_group* target_muscle, workout _workout, workout* workouts, int workouts_count) {

    // Declare variables
    exercise* last_valid_exercise = NULL;

    // Get a random start index of the valid resistance exercises
    srand(time(NULL));
    int exercises_count = valid_resistance_exercises_count;
    int start_index = rand() % exercises_count;

    // Foreach valid resistance exercise
    for (int old_i = 0; old_i < exercises_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= exercises_count) {
            i -= exercises_count;
        }

        // Declare variables
        exercise* _exercise = &valid_resistance_exercises[i];

        // Includes target muscle group?
        int includes_target_muscle = 0;
        // Foreach muscle group that the exercise targets
        for (int j = 0; j < _exercise->muscles_count; j++) {
            // Does the muscle group name match the muscle group name of the exercise?
            if (_exercise->muscles[j].name == target_muscle->name) {
                includes_target_muscle = 1;
                break;
            }
        }
        if (!includes_target_muscle) {
            continue;
        }

        // Exceeds workout duration max?
        if (does_adding_a_set_exceed_workout_duration_max(_exercise, _workout)) {
            continue;
        }

        // Exceeds either weekly sets max or daily sets max?
        if (does_adding_a_set_exceed_daily_or_weekly_set_max(_exercise)) {
            continue;
        }

        // Store valid exercise
        last_valid_exercise = _exercise;

        // We will now try to get a unique exercise (an exercise that has not yet been included in the routine).
        // Routine already contains the exercise?
        if (does_routine_already_contain_exercise(_exercise, workouts, workouts_count)) {
            continue;
        }

        // Clone the exercise to the output, if all checks pass
        *candidate = *_exercise;
        return;
    }

    // Since we could not find a unique exercise, we will settle for a duplicate,
    // provided that we actually have found a valid duplicate.
    if (last_valid_exercise != NULL) {
        *candidate = *last_valid_exercise;
        return;
    }

    // If no checks pass, no candidate is found
    candidate = NULL;
}

// Main functions
static void set_workout_rules() {

    enum fitness_level level = questionnaire.fitnessLevel;

    if (level >= novice) { // (novice = 5, advanced_beginner = 4, competent = 3, proficient = 2)
        max_weekly_sets = 10; // To make it easier to get into the habit of fitness.
        resistance_recovery = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_weekly_aerobic_workouts = 3; // Limited, because beginners are recommended 1-3 sessions per week.
        aerobic_rest_multiplier = 3; // 1:3 work-to-rest ratio.
    } else if (level >= advanced_beginner) {
        max_weekly_sets = 10; // To make it easier to get into the habit of fitness.
        resistance_recovery = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        aerobic_rest_multiplier = 2; // 1:2 work-to-rest ratio.
    } else {
        max_weekly_sets = 20; // todo: add explanation (I should research what the max volume should be)
        resistance_recovery = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        aerobic_rest_multiplier = 1; // 1:1 work-to-rest ratio.
    }
}
static void add_resistance_exercises(workout *workouts, int workouts_count) {

    // TODO: Implement this.

    // Get a random start index of the valid muscle groups
    srand(time(NULL));
    int muscles_count = valid_muscles_count; // TODO: Implement this
    int start_index = rand() % muscles_count;

    // Foreach valid muscle group
    for (int old_i = 0; old_i < muscles_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= muscles_count) {
            i -= muscles_count;
        }

        // Declare variables
        muscle_group* target_muscle = &valid_muscles[i];

        // Foreach resistance training day
        for (int j = 0; j < resistance_days_count; j++) {

            // Declare variables
            workout *_workout = &resistance_days[j];

            // Try to find exercise candidate
            exercise* exercise_candidate = NULL;
            try_to_find_resistance_exercise_candidate(exercise_candidate, target_muscle, _workout, workouts, workouts_count);

            // Found a candidate?
            if (exercise_candidate == NULL) {
                continue;
            }

            // Add exercise to the training day
            // TODO: Implement this.
        }
    }

}
static void fill_workouts_with_sets(workout *workouts, int workouts_count) {

    // Do while sets are being added
    int loop_added_a_set;
    do {

        loop_added_a_set = 0;

        // Foreach workout
        for (int i = 0; i < workouts_count; i++) {

            // Declare variables
            workout* _workout = &workouts[i];

            // Foreach exercise
            for (int j = 0; j < _workout->exercises_count; j++) {

                // Declare variables
                exercise* _exercise = &_workout->exercises[j];

                // Workout duration max exceeded?
                if (does_adding_a_set_exceed_workout_duration_max(_exercise, _workout)) {
                    continue;
                }

                // Resistance exercise?
                // If so, will daily set max or weekly set max be exceeded when adding a set?
                if (!_exercise->is_aerobic && does_adding_a_set_exceed_daily_or_weekly_set_max(_exercise)) {
                    continue;
                }

                // Add a set
                add_set_to_exercise(_exercise, _workout);
            }
        }
    } while (loop_added_a_set);
}
static void reverse_order_of_exercises(workout* workouts, int workouts_count) {

    // Foreach workout
    for (int i = 0; i < workouts_count; i++) {

        // Declare variables
        exercise* exercises = workouts[i].exercises;
        int count = workouts[i].exercises_count;
        exercise reversed[ARRAY_MAX];

        // Create reversed array
        for (int j = 0; j < count; j++) {
            reversed[j] = exercises[count - j - 1];
        }

        // Clone reversed array
        for (int j = 0; j < workouts[i].exercises_count; j++) {
            exercises[j] = reversed[j];
        }
    }
}
workout *create_workouts ()
{
    // Get workout rules
    set_workout_rules();

    // Initialize workouts
    workout* workouts;
    int workouts_count;
    initialize_workouts();

    // Find which days are resistance training days
    // TODO: Implement this

    // Find which days are aerobic training days
    // TODO: Implement this

    // Add exercises and fill with sets
    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();

    // Make aerobic exercises come before resistance exercises in the workouts
    reverse_order_of_exercises(workouts, workouts_count);

    return workouts;
}



