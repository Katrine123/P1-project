#include "workouts.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//TODO:
// For resistance training: compound movements should be given priority (for people with only little time).

//TODO:
// Make specific exercise warmup optional (if people don't feel like they need it, they can save a lot of time/
// do a lot more exercises if they do not do the specific warmup).

//TODO:
// In the report: add that there is an edge case where if you have only little time, you might not get a full-body resistance workout.
// Then you could actually have more than 3 resistance training days a week, because you would have muscle groups that
// are not used in one workout. This is something our design does not take into account.

//TODO:
// Implement supersets (will decrease time spent + will need information about opposing muscle groups).

//TODO:
// (ACTUALLY, THIS SHOULD BE DONE BY TEAM MISCHA AND LUNA)
// Implement ignored exercises (user story: "I hate squats, please give me any leg exercise other than squats.")

// General constants
static const int ARRAY_MAX = 32; // 32 simply because it is big enough.

// Enums
typedef enum {
    //TODO: Not implemented yet. Should contain stuff like biceps, triceps, chest, etc.
} muscle_group_name;
typedef enum {
    //TODO: Not implemented yet. Should contain stuff like, bench_press, squat, deadlift, etc.
} exercise_name;
typedef enum {
    monday = 1, tuesday = 2, wednesday = 3, thursday = 4,
    friday = 5, saturday = 6, sunday = 7
} day_of_the_week;

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
    double set_duration; // In minutes. How long it takes to perform 1 set of the exercise.
    int is_aerobic; // Is boolean.
    double specific_warmup_duration; // In minutes. Only relevant for resistance training exercises.
} exercise;
typedef struct {
    exercise exercises[ARRAY_MAX]; int exercises_count;
    double duration; double max_duration;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups included in the workout.
    day_of_the_week day;
} workout;

// For the whole fitness routine
workout routine_workouts[7]; // At most 7 workouts in a week (1 per day).
int routine_workouts_count = 0;
static muscle_group routine_muscles[ARRAY_MAX]; static int routine_muscles_count; // Muscle groups included in the routine.
static int resistance_workout_indexes[3]; static int resistance_workout_indexes_count; // Max 3 per week because of 48-72 hour recovery time and doing full-body exercises.
static int aerobic_workout_indexes[7]; static int aerobic_workout_indexes_count; //Max 7 per week (1 per day).

// Workout rules
static const int general_warmup_duration = 5; // In minutes.
static const int max_daily_sets = 6; // For resistance training.
static const int max_daily_aerobic_exercises = 3; // 3 brings a good amount of variety without becoming overly complex.
static int max_weekly_sets; // For resistance training.
static int resistance_recovery;
static int max_weekly_aerobic_workouts;
static int aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.

// Miscellaneous
static muscle_group valid_muscle_groups[]; static int valid_muscle_groups_count;

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
    double new_duration = _workout->duration + _exercise->set_duration;
    // Also factor in specific warmup for resistance exercise?
    if (!_exercise->is_aerobic && _exercise->sets == 0) {
        new_duration += _exercise->specific_warmup_duration;
    }
    if (new_duration > _workout->max_duration) {
        return 1;
    }

    // Return false if the check passes
    return 0;
}
static int does_routine_already_contain_exercise(exercise *_exercise) {

    // Foreach workout in the routine
    for (int i = 0; i < routine_workouts_count; i++) {

        // Declare variables
        workout* _workout = &routine_workouts[i];

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

    /// NOTE: Also adds specific warmup for resistance exercises, if sets = 0.

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
    _workout->duration += _exercise->set_duration;

    // Add set to exercise
    _exercise->sets++;
}
static void add_exercise_candidate_to_workout(exercise *exercise_candidate, exercise* workout_exercise, workout* _workout) {

    // NOTE: Added exercises start with 0 sets. This does not add sets.

    // NOTE: workout_exercise is the output.

    // Add exercise to workout by cloning exercise candidate
    workout_exercise = &_workout->exercises[_workout->exercises_count];
    *workout_exercise = *exercise_candidate;
    workout_exercise->sets = 0;
    _workout->exercises_count++;
}
static void update_resistance_exercise_muscle_groups(exercise *_exercise, workout* _workout) {

    // Update the muscle groups of the exercise, workout, and routine
    // Foreach muscle group that the exercise targets
    for (int i = 0; i < _exercise->muscles_count; i++) {

        // Declare variables
        muscle_group *exercise_muscle = &_exercise->muscles[i];
        muscle_group *workout_muscle = NULL;
        muscle_group *routine_muscle = NULL;

        // Find whether the muscle group is already included in either the workout or the routine.
        // Foreach muscle group included the workout
        for (int j = 0; j < _workout->muscles_count; j++) {
            if (_workout->muscles[j].name == exercise_muscle->name) {
                workout_muscle = &_workout->muscles[j];
                routine_muscle = workout_muscle->parent;
                break;
            }
        }
        // If the workout includes the muscle group, the routine will always also include the muscle group
        if (workout_muscle == NULL) {
            // Foreach muscle group included the routine
            for (int j = 0; j < routine_muscles_count; j++) {
                if (routine_muscles[j].name == exercise_muscle->name) {
                    routine_muscle = &routine_muscles[j];
                    break;
                }
            }
        }

        // Add muscle group to workout, if it is not included yet
        if (workout_muscle == NULL) {
            workout_muscle = &_workout->muscles[_workout->muscles_count];
            *workout_muscle = *exercise_muscle;
            _workout->muscles_count++;
        }

        // Add muscle group to routine, if it is not included yet
        if (routine_muscle != NULL) {
            routine_muscle = &routine_muscles[routine_muscles_count];
            *routine_muscle = *exercise_muscle;
            routine_muscles_count++;
        }

        // Set up muscle group references
        exercise_muscle->parent = workout_muscle;
        if (workout_muscle->parent == NULL) {
            workout_muscle->parent = routine_muscle;
        }
    }
}
static void try_to_find_resistance_exercise_candidate(exercise* candidate, muscle_group* target_muscle, workout* _workout) {

    // NOTE: 'candidate' is the output. It is set to NULL in this function if no candidate is found.

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
        if (does_routine_already_contain_exercise(_exercise, routine_workouts, routine_workouts_count)) {
            continue;
        }

        // Make the output point to the exercise, if all checks pass
        candidate = _exercise;
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
static void try_to_find_aerobic_exercise_candidate(exercise* candidate, workout* _workout) {

    // TODO: Implement this.

     // NOTE: 'candidate' is the output. It is set to NULL in this function if no candidate is found.

    // Declare variables
    exercise* last_valid_exercise = NULL;

    // Get a random start index of the valid aerobic exercises
    srand(time(NULL));
    int exercises_count = valid_aerobic_exercises_count;
    int start_index = rand() % exercises_count;

    // Foreach valid resistance exercise
    for (int old_i = 0; old_i < exercises_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= exercises_count) {
            i -= exercises_count;
        }

        // Declare variables
        exercise* _exercise = &valid_aerobic_exercises[i];

        // Exceeds workout duration max?
        if (does_adding_a_set_exceed_workout_duration_max(_exercise, _workout)) {
            continue;
        }

        // Store valid exercise
        last_valid_exercise = _exercise;

        // We will now try to get a unique exercise (an exercise that has not yet been included in the routine).
        // Routine already contains the exercise?
        if (does_routine_already_contain_exercise(_exercise, routine_workouts, routine_workouts_count)) {
            continue;
        }

        // Make the output point to the exercise, if all checks pass
        candidate = _exercise;
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

// Primary functions
static void update_valid_muscle_groups()
{

    // Reset array count
    valid_muscle_groups_count = 0;

    // Foreach of all muscle groups
    // TODO: all_muscle_groups is a global muscle group array containing all muscle groups
    for (int i = 0; i < all_muscle_groups_count; i++) {

        // Declare variables
        muscle_group* _muscle = &all_muscle_groups[i];
        int is_valid = 1;

        // Foreach ignored muscle group
        for (int j = 0; j < questionnaire.ignored_muscle_groups_count; j++) {

            // Mark ignored groups as invalid
            if (_muscle->name == questionnaire.ignored_muscle_groups[j].name) {
                is_valid = 0;
                break;
            }
        }

        // Add valid muscle groups
        if (is_valid) {
            valid_muscle_groups[valid_muscle_groups_count] = *_muscle;
            valid_muscle_groups_count++;
        }
    }
}
static void update_workout_rules() {

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
static void reset_routine_workouts() {

    // Reset array count
    routine_workouts_count = questionnaire.available_workout_days_count;

    // Foreach new workout
    for (int i = 0; i < routine_workouts_count; i++) {

        // Reset properties to defaults
        routine_workouts[i].day = questionnaire.available_workout_days[i].week_day;
        routine_workouts[i].max_duration = questionnaire.available_workout_days[i].max_duration_in_minutes;
        routine_workouts[i].duration = 0;
        routine_workouts[i].exercises_count = 0;
        routine_workouts[i].muscles_count = 0;

        // Add general warmup to workout duration.
        routine_workouts[i].duration = general_warmup_duration;
    }

}
static void update_resistance_days() {

    // Reset array count
    resistance_workout_indexes_count = 0;

    // Foreach workout in routine
    for (int i = 0; i < routine_workouts_count; i++ ) {

        // Declare variables
        workout *_workout = &routine_workouts[i];
        int day_is_valid = 1;

        // Valid recovery time?
        // Foreach resistance training day
        for (int j = 0; j < resistance_workout_indexes_count; j++) {

            // Declare variables
            workout *resistance_workout = &routine_workouts[resistance_workout_indexes[j]];

            // Get days in-between
            int days_between = _workout->day - resistance_workout->day;
            // Account for if the check day is in next week (e.g. the days between Sunday and Monday).
            if (days_between < 0) {
                days_between += 7;
            }

            // Mark day as invalid, if recovery rules are not met.
            if (days_between < resistance_recovery) {
                day_is_valid = 0;
                break;
            }
        }

        // Add to resistance days, if day is valid
        if (day_is_valid) {
            resistance_workout_indexes[resistance_workout_indexes_count] = i;
            resistance_workout_indexes_count++;
        }
    }
}
static void update_aerobic_days() {

    // Reset array count
    aerobic_workout_indexes_count = 0;

    // Do 2 loops
    for (int loop = 0; loop < 2; loop++) {
        // Foreach workout in routine
        for (int i = 0; i < routine_workouts_count; i++ ) {

            // Assume day is valid
            int day_is_valid = 1;

            // On 1st loop
            if (loop == 0) {
                // Is workout day also a resistance training day?
                for (int j = 0; j < resistance_workout_indexes_count; j++) {
                    // Ignore this day
                    if (resistance_workout_indexes[j] == i) {
                        day_is_valid = 0;
                        break;
                    }
                }
            }

            // On both loops
            // Weekly aerobic workout max exceeded?
            if (aerobic_workout_indexes_count >= max_weekly_aerobic_workouts) {
                day_is_valid = 0;
            }

            // Add to aerobic days, if all checks pass
            if (day_is_valid) {
                aerobic_workout_indexes[aerobic_workout_indexes_count] = i;
                aerobic_workout_indexes_count++;
            }
        }
    }


}
static void add_resistance_exercises() {

    // NOTE: Adds 1 set of exercises.

    // Get a random start index of the valid muscle groups
    srand(time(NULL));
    int muscles_count = valid_muscle_groups_count;
    int start_index = rand() % muscles_count;

    // Foreach valid muscle group
    for (int old_i = 0; old_i < muscles_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= muscles_count) {
            i -= muscles_count;
        }

        // Declare variables
        muscle_group* target_muscle = &valid_muscle_groups[i];

        // Foreach resistance training day
        for (int j = 0; j < resistance_workout_indexes_count; j++) {

            // Declare variables
            workout *_workout = &routine_workouts[resistance_workout_indexes[j]];

            // Try to find exercise candidate
            exercise* exercise_candidate = NULL;
            try_to_find_resistance_exercise_candidate(exercise_candidate, target_muscle, _workout);

            // Found a candidate?
            if (exercise_candidate == NULL) {
                continue;
            }

            // Add exercise to the training day and add a set
            exercise* new_exercise_in_workout;
            add_exercise_candidate_to_workout(exercise_candidate, _workout, new_exercise_in_workout);
            update_resistance_exercise_muscle_groups(new_exercise_in_workout, _workout);
            add_set_to_exercise(new_exercise_in_workout, _workout);
        }
    }

}
static void add_aerobic_exercises() {

    // TODO: Implement this.

    // Foreach aerobic exercise day
    for (int i = 0; i < aerobic_workout_indexes_count; i++) {

        // Declare variables
        int new_index = aerobic_workout_indexes[i];
        workout* _workout = &routine_workouts[new_index];

        // Loop x times (x = max amount of aerobic exercises per day)
        for (int j = 0; j < max_daily_aerobic_exercises; j++) {

            // Find exercise candidate
            exercise* exercise_candidate = NULL;
            try_to_find_aerobic_exercise_candidate(exercise_candidate, _workout);

            // Candidate found?
            if (exercise_candidate == NULL) {
                continue;
            }

            // Add exercise
            exercise* new_exercise_in_workout;
            add_exercise_candidate_to_resistance_training_workout(exercise_candidate, _workout, new_exercise_in_workout);
            add_set_to_exercise(new_exercise_in_workout, _workout);
        }
    }




}
static void fill_workouts_with_sets() {

    // Do while sets are being added
    int loop_added_a_set;
    do {

        loop_added_a_set = 0;

        // Foreach workout
        for (int i = 0; i < routine_workouts_count; i++) {

            // Declare variables
            workout* _workout = &routine_workouts[i];

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
static void reverse_order_of_exercises() {

    // Foreach workout
    for (int i = 0; i < routine_workouts_count; i++) {

        // Declare variables
        exercise* exercises = routine_workouts[i].exercises;
        int count = routine_workouts[i].exercises_count;
        exercise reversed[ARRAY_MAX];

        // Create reversed array
        for (int j = 0; j < count; j++) {
            reversed[j] = exercises[count - j - 1];
        }

        // Clone reversed array
        for (int j = 0; j < routine_workouts[i].exercises_count; j++) {
            exercises[j] = reversed[j];
        }
    }
}

// Global functions
void update_workouts()
{
    // Get workout rules (for example max weekly sets)
    update_workout_rules();

    // Get valid muscle groups to target
    update_valid_muscle_groups();

    // Reset routine
    reset_routine_workouts();

    // Find which days are resistance training days
    update_resistance_days();

    // Find which days are aerobic training days
    update_aerobic_days();

    // Add exercises and fill with sets
    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();

    // Make aerobic exercises come before resistance exercises in the workouts
    reverse_order_of_exercises(routine_workouts, routine_workouts_count);
}



