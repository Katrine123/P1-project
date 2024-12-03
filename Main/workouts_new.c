#include "workouts_new.h"
#include <stdio.h>
#include <stdlib.h>

//TODO: Merge this workouts_new.c with the old workouts.c

// General constants
static const int ARRAY_MAX = 32; // 32 simply because it is big enough.

// Enums
typedef enum {
    //TODO: Must be expanded to include biceps, triceps, chest, etc.
} muscle_group_name_e;

// Structs
typedef struct {
    exercise_t a_exercises[ARRAY_MAX]; int exercises_count;
    double duration; double max_duration;
} workout_t;
typedef struct muscle_group_t {
    enum muscle_group_name_e name;
    int sets; // Either daily or weekly sets depending on whether the muscle_group struct is past of the routine_muscle_groups array of muscle_groups (weekly sets) or the muscle_group struct is a property of a workout struct (daily sets).
    struct muscle_group_t *p_routine_muscle_group; // The struct workout_t has properties of the struct exercise_t which has properties of struct muscle_group_t.
} muscle_group_t;

// Workout rules
const int general_warmup_duration = 5; // In minutes.
const int max_daily_sets = 6; // For resistance training.
int max_weekly_sets; // For resistance training.
int resistance_recovery;
int max_weekly_aerobic_workouts;
int aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.

// For the whole routine
muscle_group_t a_routine_included_muscle_groups[ARRAY_MAX];
int routine_included_muscle_groups_count;




// Functions
static void set_workout_rules() {

    fitness_level_e level = questionnaire.fitnessLevel;

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
int adding_a_set_exceeds_daily_set_max(exercise_t *p_exercise) {

    // Todo: Implement this.

    //TODO:
    // What is fucking me up is that
    // each workout_t has muscle_group[] which contains sets (daily sets)
    // furthermore, there is a global muscle_group[] for the whole routine which contains sets (weekly sets)

    // Foreach targeted muscle group
    for (int i = 0; p_exercise->muscle_groups_count; i++) {

        //TODO:
        // Each exercise_muscle_group has a pointer to a global variable muscle_group inside the routine's muscle_groups,
        // so that you may find the routine's total amount of sets through that.

        // Declare variables
        muscle_group_t *p_muscle_group = &p_exercise->muscle_groups[i];
        muscle_group_t *p_routine_muscle_group = p_muscle_group->p_routine_muscle_group;

        //
        int new_sets = p_routine_muscle_group->sets + 1;
        if (max_daily_sets) {

        }

    }

    // Return false if the checks pass
    return 0;
}
static void fill_workouts_with_sets(workout_t *a_workouts, int workouts_count) {

    // Todo: Implement this (after you've implemented "adding_a_set_exceeds_daily_set_max()").

    // Do while sets are being added
    int loop_added_a_set;
    do {
        loop_added_a_set = 0;

        // Foreach workout
        for (int i = 0; i < workouts_count; i++) {

            // Declare variables
            workout_t* p_workout = &a_workouts[i];
            int exercise_count = p_workout->exercises_count;

            // Foreach exercise
            for (int j = 0; j < exercise_count; j++) {

                // Declare variables
                exercise_t* p_exercise = &p_workout->a_exercises[j];

                // Workout duration max exceeded?
                double new_duration = p_workout->duration + p_exercise->duration;
                if (new_duration > p_workout->max_duration) {
                    continue;
                }

                // Resistance exercise?
                if (!p_exercise->is_aerobic) {

                    // Daily set max exceeded?
                    if (adding_a_set_exceeds_daily_set_max()) {
                        continue;
                    }

                    // Weekly set max exceeded?
                    if (has_exceeded_weekly_set_max()) {
                        continue;
                    }
                }

                // Add a set
                p_exercise->sets++;
                p_workout->duration += p_exercise->duration;
            }

        }

    } while (loop_added_a_set);
}
static void reverse_order_of_exercises(workout_t* a_workouts, int workouts_count) {

    // Foreach workout
    for (int i = 0; i < workouts_count; i++) {

        // Declare variables
        exercise_t* p_exercises = a_workouts[i].a_exercises;
        int count = a_workouts[i].exercises_count;
        exercise_t a_reversed[ARRAY_MAX];

        // Create reversed array
        for (int j = 0; j < count; j++) {
            a_reversed[j] = p_exercises[count - j - 1];
        }

        // Clone reversed array
        for (int j = 0; j < a_workouts[i].exercises_count; j++) {
            p_exercises[j] = a_reversed[j];
        }
    }
}
workout_t *create_workouts ()
{
    // Get workout rules
    set_workout_rules();

    // Initialize workouts
    workout_t* a_workouts;
    int workouts_count;
    initialize_workouts();

    // Initialize resistance training days
    resistance_training_day* p_resistance_workouts;
    int resistance_workouts_count;
    initialize_resistance_training_days();

    // Add exercises and fill with sets
    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();

    // Make aerobic exercises come before resistance exercises
    reverse_order_of_exercises(a_workouts, workouts_count);

    return a_workouts;
}



