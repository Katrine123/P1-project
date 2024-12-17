#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "references.h"

// For the whole fitness routine

muscle_group routine_muscles[ARRAY_MAX]; int routine_muscles_count; // Muscle groups included in the routine.
int resistance_workout_indexes[3]; int resistance_workout_indexes_count; // Max 3 per week because of 48-72 hour recovery time and doing full-body exercises.
int aerobic_workout_indexes[7]; int aerobic_workout_indexes_count; // Max 7 per week (1 per day).

// -----------------------------------------------------------------------------

// Helper functions

muscle_group* get_muscle_group_in_workout(muscle_group *muscle, workout *_workout) {

    muscle_group *muscle_in_workout = NULL;

    // Find whether the muscle group is already included in the workout.
    // Foreach muscle group included the workout
    for (int j = 0; j < _workout->muscles_count; j++) {
        if (_workout->muscles[j].name == muscle->name) {
            muscle_in_workout = &_workout->muscles[j];
            break;
        }
    }

    return muscle_in_workout;
}
muscle_group* get_muscle_group_in_routine(muscle_group *muscle) {

    muscle_group *muscle_in_routine = NULL;

    // Find whether the muscle group is already included in the routine.
    // Foreach muscle group included the routine
    for (int j = 0; j < routine_muscles_count; j++) {
        if (routine_muscles[j].name == muscle->name) {
            muscle_in_routine = &routine_muscles[j];
            break;
        }
    }

    return muscle_in_routine;
}
double new_workout_duration_when_adding_a_set(exercise _exercise, workout _workout) {

    // Add duration of the set
    double new_duration = _workout.duration + _exercise.rep_duration * _exercise.reps;

    // Add duration of rest between sets and specific warm-ups (if applicable)
    if (_exercise.is_aerobic) {
        new_duration += _exercise.rep_duration * _exercise.reps * aerobic_rest_multiplier;
    } else {
        new_duration += rest_between_sets_resistance;
        if (_exercise.sets == 0) {
            new_duration += _exercise.specific_warmup_duration;
        }
    }

    return new_duration;
}
int does_adding_a_set_exceed_daily_or_weekly_set_max(exercise _exercise, workout* _workout) {

    // Foreach muscle group that the exercise targets
    for (int i = 0; i <_exercise.muscles_count; i++) {

        // Declare variables
        muscle_group* exercise_muscle = &_exercise.muscles[i];

        // Find whether the muscle group is already included in the workout and/or the routine.
        muscle_group* workout_muscle = get_muscle_group_in_workout(exercise_muscle, _workout);;
        muscle_group* routine_muscle = get_muscle_group_in_routine(exercise_muscle);;
        
        // Exceeds weekly set max?
        if (routine_muscle != NULL) {
            int new_weekly_sets = routine_muscle->sets + 1;
            if (new_weekly_sets > max_weekly_sets) {
                return 1;
            }
        }

        // Exceeds daily set max?
        if (workout_muscle != NULL) {
            int new_daily_sets = workout_muscle->sets + 1;
            if (new_daily_sets > max_daily_sets) {
                return 1;
            }
        }
    }

    // Return false if the checks pass
    return 0;
}
int does_adding_a_set_exceed_workout_duration_max(exercise _exercise, workout _workout) {

    // Does it exceed workout duration max?
    double new_duration = new_workout_duration_when_adding_a_set(_exercise, _workout);
    if (new_duration > _workout.max_duration) {
        return 1;
    }
    return 0;
}
int does_routine_already_contain_exercise(exercise _exercise) {

    // Foreach workout in the routine
    for (int i = 0; i < routine_workouts_count; i++) {

        // Declare variables
        workout _workout = routine_workouts[i];

        // Foreach exercise in the workouts
        for (int j = 0; j < _workout.exercises_count; j++) {

            // Declare variables
            exercise workout_exercise = _workout.exercises[j];

            // Is the exercise a duplicate?
            if (workout_exercise.name == _exercise.name) {
                return 1;
            }
        }
    }

    // Return false if the checks passes
    return 0;
}
int does_workout_already_contain_exercise(exercise _exercise, workout _workout) {

    // Foreach exercise in the workout
    for (int i = 0; i < _workout.exercises_count; i++) {

        // Declare variables
        exercise workout_exercise = _workout.exercises[i];

        // Is the exercise a duplicate?
        if (workout_exercise.name == _exercise.name) {
            return 1;
        }
    }

    // Return false if the checks passes
    return 0;
}
void add_set_to_exercise(exercise *_exercise, workout* _workout) {

    /// NOTE: Also adds specific warmup for resistance exercises, if sets = 0.

    // Is exercise aerobic?
    if (!_exercise->is_aerobic) {

        // Add sets to parent muscle groups
        // Foreach muscle group the exercise targets
        for (int i = 0; i < _exercise->muscles_count; i++) {

            // Declare variables
            muscle_group *exercise_muscle = &_exercise->muscles[i];
            muscle_group *workout_muscle = exercise_muscle->parent;
            muscle_group *routine_muscle = workout_muscle->parent;

            // Add sets to muscle groups
            workout_muscle->sets++;
            routine_muscle->sets++;
        }

    }

    // Set new workout duration
    _workout->duration = new_workout_duration_when_adding_a_set(*_exercise, *_workout);

    // Add set to exercise
    _exercise->sets++;
}
exercise* add_exercise_candidate_to_workout(exercise added_exercise, workout* _workout) {

    // NOTE: Added exercises start with 0 sets.

    // Add exercise to workout by cloning exercise candidate
    exercise* workout_exercise = &_workout->exercises[_workout->exercises_count];
    *workout_exercise = added_exercise;
    workout_exercise->sets = 0;
    _workout->exercises_count++;
    return workout_exercise;
}
void update_resistance_exercise_muscle_groups(exercise *_exercise, workout* _workout) {

    // Update the muscle groups of the exercise, workout, and routine
    // Foreach muscle group that the exercise targets
    for (int i = 0; i < _exercise->muscles_count; i++) {

        // Declare variables
        muscle_group *exercise_muscle = &_exercise->muscles[i];

        // Find whether the muscle group is already included in the workout and/or the routine.
        muscle_group *workout_muscle = get_muscle_group_in_workout(exercise_muscle, _workout);
        muscle_group *routine_muscle = get_muscle_group_in_routine(exercise_muscle);

        // Add muscle group to workout, if it is not included yet
        if (workout_muscle == NULL) {
            workout_muscle = &_workout->muscles[_workout->muscles_count];
            *workout_muscle = *exercise_muscle;
            _workout->muscles_count++;
        }

        // Add muscle group to routine, if it is not included yet
        if (routine_muscle == NULL) {
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
void try_to_find_resistance_exercise_candidate(int *found_valid_candidate, exercise *candidate, muscle_group_name target_muscle_name, workout *_workout) {

    // Declare variables
    exercise last_valid_exercise;
    *found_valid_candidate = 0;

    // Get a random start index of the valid resistance exercises
    srand(time(NULL));
    int exercises_count = possible_resistance_exercises_count;
    if (possible_resistance_exercises_count == 0) return;
    int start_index = rand() % exercises_count;

    // Foreach valid resistance exercise
    for (int old_i = 0; old_i < exercises_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= exercises_count) {
            i -= exercises_count;
        }

        // Declare variables
        exercise _exercise = possible_resistance_exercises[i];

        // Includes target muscle group?
        int includes_target_muscle = 0;
        // Foreach muscle group that the exercise targets
        for (int j = 0; j < _exercise.muscles_count; j++) {
            // Does the muscle group name match the muscle group name of the exercise?
            if (_exercise.muscles[j].name == target_muscle_name) {
                includes_target_muscle = 1;
                break;
            }
        }
        if (!includes_target_muscle) {
            continue;
        }

        // Exceeds workout duration max?
        if (does_adding_a_set_exceed_workout_duration_max(_exercise, *_workout)) {
            continue;
        }

        // Exceeds either weekly sets max or daily sets max?
        if (does_adding_a_set_exceed_daily_or_weekly_set_max(_exercise, _workout)) {
            continue;
        }

        // Workout already contains the exercise?
        if (does_workout_already_contain_exercise(_exercise, *_workout)) {
            continue;
        }

        // Store valid exercise
        last_valid_exercise = _exercise;
        *found_valid_candidate = 1;

        // Though we now have a valid exercise, we will try to find
        // an exercise that is not yet included in the routine.
        // Routine already contains the exercise?
        if (does_routine_already_contain_exercise(_exercise)) {
            continue;
        }

        // Make the output point to the exercise, if all checks pass
        *candidate = _exercise;
        return;
    }

    // Since we could not find a unique exercise, we will settle for a duplicate,
    // provided that we actually have found a valid duplicate.
    if (*found_valid_candidate) {
        *candidate = last_valid_exercise;
    }
}
void try_to_find_aerobic_exercise_candidate(int *found_valid_candidate, exercise* candidate, workout _workout) {

    // Declare variables
    *found_valid_candidate = 0;
    exercise last_valid_exercise;

    // Get a random start index of the valid aerobic exercises
    srand(time(NULL));
    int exercises_count = possible_aerobic_exercises_count;
    if (exercises_count == 0) return;
    int start_index = rand() % exercises_count;

    // Foreach valid resistance exercise
    for (int old_i = 0; old_i < exercises_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= exercises_count) {
            i -= exercises_count;
        }

        // Declare variables
        exercise _exercise = possible_aerobic_exercises[i];

        // Exceeds workout duration max?
        if (does_adding_a_set_exceed_workout_duration_max(_exercise, _workout)) {
            continue;
        }

        // Workout already contains the exercise?
        if (does_workout_already_contain_exercise(_exercise, _workout)) {
            continue;
        }

        // Store valid exercise
        last_valid_exercise = _exercise;
        *found_valid_candidate = 1;

        // Though we now have a valid exercise, we will try to find
        // an exercise that is not yet included in the routine.
        // Routine already contains the exercise?
        if (does_routine_already_contain_exercise(_exercise)) {
            continue;
        }

        // Make the output point to the exercise, if all checks pass.
        // (Then the exercise is unique/non-duplicate in not only the
        // workout, but also in the routine.)
        *candidate = _exercise;
        return;
    }

    // Since we could not find a unique exercise, we will settle for a duplicate,
    // provided that we actually have found a valid duplicate.
    if (*found_valid_candidate) {
        *candidate = last_valid_exercise;
    }
}

// Primary functions

void update_workout_rules() {

    enum fitness_level level = _questionnaire._fitness_level;

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
        max_weekly_sets = 20; // We have not found any scientifically-backed max, so we assume it to 20.
        resistance_recovery = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        if (level >= competent) {
            aerobic_rest_multiplier = 1; // 1:1 work-to-rest ratio.
        } else if (level >= proficient) {
            aerobic_rest_multiplier = 1.0 / 2; // 2:1 work-to-rest ratio.
        } else { // Else, it's an expert
            aerobic_rest_multiplier = 1.0 / 3; // 3:1 work-to-rest ratio.
        }
    }
}
void reset_routine_workouts() {

    // Reset array count
    routine_workouts_count = _questionnaire.available_training_days_count;

    // Foreach new workout
    for (int i = 0; i < routine_workouts_count; i++) {

        // Reset properties to defaults
        routine_workouts[i].day = _questionnaire.available_training_days[i].day;
        routine_workouts[i].max_duration = _questionnaire.available_training_days[i].max_duration;
        routine_workouts[i].duration = 0;
        routine_workouts[i].exercises_count = 0;
        routine_workouts[i].muscles_count = 0;

        // Add general warmup to workout duration.
        routine_workouts[i].duration = general_warmup_duration;
    }

}
void update_resistance_days() {

    // Reset array count
    resistance_workout_indexes_count = 0;

    // Foreach workout in routine
    for (int i = 0; i < routine_workouts_count; i++ ) {

        // Declare variables
        workout _workout = routine_workouts[i];
        int day_is_valid = 1;

        // Valid recovery time?
        // Foreach resistance training day
        for (int j = 0; j < resistance_workout_indexes_count; j++) {

            // Declare variables
            workout resistance_workout = routine_workouts[resistance_workout_indexes[j]];

            // Get days in-between
            int days_between1 = _workout.day - resistance_workout.day;
            int days_between2 = resistance_workout.day + 7 - _workout.day; // Account for if the check day is in next week (e.g. the days between Sunday and Monday).

            // Mark day as invalid, if recovery rules are not met.
            if (days_between1 < resistance_recovery || days_between2 < resistance_recovery) {
                day_is_valid = 0;
                break;
            }
        }

        // Add to resistance days, if day is valid
        if (day_is_valid) {
            resistance_workout_indexes[resistance_workout_indexes_count++] = i;
        }
    }
}
void update_aerobic_days() {

    // Reset array count
    aerobic_workout_indexes_count = 0;

    // Foreach non-resistance training day
    for (int i = 0, j = 0; i < routine_workouts_count; i++ ) {

        printf("\ni = %d, Resistance index = %d", i, resistance_workout_indexes[i]);

        // Ignore resistance workouts
        if (i == resistance_workout_indexes[j]) {
            j++;
            continue;
        }

        // Weekly aerobic workout max exceeded?
        if (aerobic_workout_indexes_count >= max_weekly_aerobic_workouts) {
            return;
        }

        // Add day
        aerobic_workout_indexes[aerobic_workout_indexes_count++] = i;
    }

    // Foreach resistance training day
    for (int i = 0; i < resistance_workout_indexes_count; i++ ) {

        // Weekly aerobic workout max exceeded?
        if (aerobic_workout_indexes_count >= max_weekly_aerobic_workouts) {
            return;
        }

        // Add day
        aerobic_workout_indexes[aerobic_workout_indexes_count++] = resistance_workout_indexes[i];
    }
}
void add_resistance_exercises() {

    // NOTE: Adds 1 set of exercises.

    // Get a random start index of the valid muscle groups
    srand(time(NULL));
    int start_index = rand() % all_muscle_names_count;

    // Foreach valid muscle group
    for (int old_i = 0; old_i < all_muscle_names_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= all_muscle_names_count) {
            i -= all_muscle_names_count;
        }

        // Declare variables
        muscle_group_name target_muscle_name = all_muscle_names[i];

        // Is an ignored muscle group?
        int is_ignored_group = 0;
        for (int j = 0; j < _questionnaire.ignored_muscle_group_names_count; j++) {
            if (target_muscle_name == _questionnaire.ignored_muscle_group_names[j]) {
                is_ignored_group = 1;
                break;
            }
        }
        if (is_ignored_group) {
            continue;
        }

        // Foreach resistance training day
        for (int j = 0; j < resistance_workout_indexes_count; j++) {

            // Declare variables
            workout* _workout = &routine_workouts[resistance_workout_indexes[j]];

            // Try to find exercise candidate
            exercise exercise_candidate;
            int found_valid_candidate;
            try_to_find_resistance_exercise_candidate(&found_valid_candidate, &exercise_candidate, target_muscle_name, _workout);

            // Found a candidate?
            if (!found_valid_candidate) {
                continue;
            }

            // Add exercise to the training day and add a set
            exercise* new_exercise_in_workout = add_exercise_candidate_to_workout(exercise_candidate, _workout);
            update_resistance_exercise_muscle_groups(new_exercise_in_workout, _workout);
            add_set_to_exercise(new_exercise_in_workout, _workout);
        }
    }
}
void add_aerobic_exercises() {

    // Foreach aerobic exercise day
    for (int i = 0; i < aerobic_workout_indexes_count; i++) {

        // Declare variables
        int new_index = aerobic_workout_indexes[i];
        workout* _workout = &routine_workouts[new_index];

        // Loop x times (x = max amount of aerobic exercises per day)
        for (int j = 0; j < max_daily_aerobic_exercises; j++) {

            // Find exercise candidate
            exercise exercise_candidate;
            int found_valid_candidate;
            try_to_find_aerobic_exercise_candidate(&found_valid_candidate, &exercise_candidate, *_workout);

            // Candidate found?
            if (!found_valid_candidate) {
                continue;
            }

            // Add exercise
            exercise* new_exercise_in_workout = add_exercise_candidate_to_workout(exercise_candidate, _workout);
            add_set_to_exercise(new_exercise_in_workout, _workout);
        }
    }
}
void fill_workouts_with_sets() {

    // Do while sets are still being added (so every workout has not been filled yet.)
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
                if (does_adding_a_set_exceed_workout_duration_max(*_exercise, *_workout)) {
                    continue;
                }

                // Resistance exercise?
                // If so, will daily set max or weekly set max be exceeded when adding a set?
                if (!_exercise->is_aerobic && does_adding_a_set_exceed_daily_or_weekly_set_max(*_exercise, _workout)) {
                    continue;
                }

                // Add a set
                add_set_to_exercise(_exercise, _workout);
                loop_added_a_set = 1;
            }
        }
    } while (loop_added_a_set);
}
void reverse_order_of_exercises() {

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

void update_routine_workouts()
{
    // Get workout rules based on fitness level (for example max weekly sets).
    update_workout_rules();

    // Reset routine (it's a global variable) and add general warmups.
    reset_routine_workouts();

    // Find which days must be resistance training days, aerobic training days, or both.
    update_resistance_days();
    update_aerobic_days();

    // Add exercises (and specific warmups), and fill with sets.
    // (Resistance training is given priority over aerobic training
    // because resistance training is less flexible to schedule due to
    // greater recovery times.)
    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();

    // Make aerobic exercises come before resistance exercises in the workouts.
    // (This ensures that the trainee is always warmed up for HIIT-exercises
    // since doing resistance training first could risk cooling the trainee down.)
    reverse_order_of_exercises(routine_workouts, routine_workouts_count);

    //TODO: Remove. Only for testing purposes.
    // for (int i_test = 0; i_test < routine_workouts_count; i_test++) {
    //     printf("\n----------------------");
    //     printf("\n  Routine day: %d", routine_workouts[i_test].day);
    //     printf("\n  Duration: %lf", routine_workouts[i_test].duration);
    //     printf("\n  Max duration: %lf", routine_workouts[i_test].max_duration);
    //     for (int j_test = 0; j_test < routine_workouts[i_test].muscles_count; j_test++) {
    //         printf("\n      Included muscle [%d], name: %s, parent.name: %s",
    //             j_test,
    //             naming_muscle_group(routine_workouts[i_test].muscles[j_test].name),
    //             naming_muscle_group(routine_workouts[i_test].muscles[j_test].parent->name));
    //     }
    //     printf("\n      ----------");
    //     for (int j_test = 0; j_test < routine_workouts[i_test].exercises_count; j_test++) {
    //         printf("\n      Included exercise [%d], name: %s, sets: %d",
    //             j_test,
    //             naming_exercises(routine_workouts[i_test].exercises[j_test].name),
    //             routine_workouts[i_test].exercises[j_test].sets);
    //         for (int k_test = 0; k_test < routine_workouts[i_test].exercises[j_test].muscles_count; k_test++) {
    //             printf("\n              Included muscle [%d], name: %s, parent.name: %s, parent.sets: %d, parent != NULL: %d",
    //                 k_test,
    //                 naming_muscle_group(routine_workouts[i_test].exercises[j_test].muscles[k_test].name),
    //                 naming_muscle_group(routine_workouts[i_test].exercises[j_test].muscles[k_test].parent->name),
    //                 routine_workouts[i_test].exercises[j_test].muscles[k_test].parent->sets,
    //                 routine_workouts[i_test].exercises[j_test].muscles[k_test].parent != NULL);
    //         }
    //     }
    // }
}
