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

#define ARRAY_MAX 32 // 32 simply because it is big enough.

// Enums

//TODO: Not implemented yet. Should contain stuff like biceps, triceps, chest, etc.
typedef enum {
    calves = 1, biceps, chest, triceps, quads
} muscle_group_name;
//TODO: Not implemented yet. Should contain stuff like, bench_press, squat, deadlift, etc.
typedef enum {
    sprint = 1, burpees, bench_press, push_up, bicep_curl, squat
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

workout routine_workouts[7]; int routine_workouts_count = 0; // Max 7 workouts per week (1 per day).
muscle_group routine_muscles[ARRAY_MAX]; int routine_muscles_count; // Muscle groups included in the routine.
int resistance_workout_indexes[3]; int resistance_workout_indexes_count; // Max 3 per week because of 48-72 hour recovery time and doing full-body exercises.
int aerobic_workout_indexes[7]; int aerobic_workout_indexes_count; // Max 7 per week (1 per day).

// Workout rules

const int general_warmup_duration = 5; // In minutes.

const int max_daily_sets = 6; // For resistance training.
const int max_daily_aerobic_exercises = 3; // 3 brings a good amount of variety without becoming overly complex.
const double rest_between_sets_resistance = 1.5; // In minutes. Equivalent to 90 seconds.
int aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.
int max_weekly_sets; // For resistance training.
int resistance_recovery;
int max_weekly_aerobic_workouts;


// Miscellaneous

static muscle_group_name valid_muscle_names_names[ARRAY_MAX]; static int valid_muscle_names_count;

// TODO: Remove. Only for testing purposes.

enum fitness_level {
    novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
};
typedef struct {
    day_of_the_week _day_of_the_week;
    double max_duration; // In minutes.
} workout_day;
typedef struct  {
    enum fitness_level fitness_level;
    muscle_group_name ignored_muscle_group_names[ARRAY_MAX]; int ignored_muscle_group_names_count;
    workout_day available_workout_days[7]; int available_workout_days_count;
} _questionnaire;
_questionnaire questionnaire;
muscle_group_name all_muscle_names[ARRAY_MAX]; int all_muscle_names_count;
exercise valid_resistance_exercises[ARRAY_MAX]; int valid_resistance_exercises_count;
exercise valid_aerobic_exercises[ARRAY_MAX]; int valid_aerobic_exercises_count;

// TODO: Remove. Only for testing purposes.

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
    double new_duration = _workout.duration + _exercise.set_duration;

    // Add duration of rest between sets and specific warm-ups (if applicable)
    if (_exercise.is_aerobic) {
        new_duration += _exercise.set_duration * aerobic_rest_multiplier;
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

    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!
    // TODO: DET HER ER HVOR JEG ER KOMMET TIL!!!!

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
        exercise _exercise = valid_resistance_exercises[i];

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
        exercise _exercise = valid_aerobic_exercises[i];

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

    enum fitness_level level = questionnaire.fitness_level;

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
        max_weekly_sets = 99; // We have not researched any max for experienced trainees.
        resistance_recovery = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        aerobic_rest_multiplier = 1; // 1:1 work-to-rest ratio.
    }
}
void update_valid_muscle_groups()
{

    // Reset array count
    valid_muscle_names_count = 0;

    // Foreach of all muscle groups
    // TODO: all_muscle_groups is a global muscle group array containing all muscle groups
    for (int i = 0; i < all_muscle_names_count; i++) {

        // Declare variables
        muscle_group_name muscle_name = all_muscle_names[i];
        int is_valid = 1;

        // Foreach ignored muscle group
        for (int j = 0; j < questionnaire.ignored_muscle_group_names_count; j++) {

            // Mark ignored groups as invalid
            if (muscle_name == questionnaire.ignored_muscle_group_names[j]) {
                is_valid = 0;
                break;
            }
        }

        // Add valid muscle groups
        if (is_valid) {
            valid_muscle_names_names[valid_muscle_names_count] = muscle_name;
            valid_muscle_names_count++;
        }
    }
}
void reset_routine_workouts() {

    // Reset array count
    routine_workouts_count = questionnaire.available_workout_days_count;

    // Foreach new workout
    for (int i = 0; i < routine_workouts_count; i++) {

        // Reset properties to defaults
        routine_workouts[i].day = questionnaire.available_workout_days[i]._day_of_the_week;
        routine_workouts[i].max_duration = questionnaire.available_workout_days[i].max_duration;
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
            int days_between = _workout.day - resistance_workout.day;
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
void update_aerobic_days() {

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
void add_resistance_exercises() {

    // NOTE: Adds 1 set of exercises.

    // Get a random start index of the valid muscle groups
    srand(time(NULL));
    int muscles_count = valid_muscle_names_count;
    int start_index = rand() % muscles_count;

    // Foreach valid muscle group
    for (int old_i = 0; old_i < muscles_count; old_i++) {

        // Get new index
        int i = start_index + old_i;
        if (i >= muscles_count) {
            i -= muscles_count;
        }

        // Declare variables
        muscle_group_name target_muscle_name = valid_muscle_names_names[i];

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

void update_workouts()
{
    // Get workout rules based on fitness level (for example max weekly sets).
    update_workout_rules();

    // Get valid muscle groups to target (those that the user does not specify to ignore).
    update_valid_muscle_groups();

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

    for (int i_test = 0; i_test < routine_workouts_count; i_test++) { // TODO: Test. Remove.
        printf("\n----------------------"); // TODO: Test. Remove
        printf("\n  Routine day: %d", routine_workouts[i_test].day); // TODO: Test. Remove
        printf("\n  Duration: %lf", routine_workouts[i_test].duration); // TODO: Test. Remove
        printf("\n  Max duration: %lf", routine_workouts[i_test].max_duration); // TODO: Test. Remove
        for (int j_test = 0; j_test < routine_workouts[i_test].muscles_count; j_test++) { // TODO: Test. Remove.
            printf("\n      Included muscle [%d], name: %d, parent.name: %d",
                j_test,
                routine_workouts[i_test].muscles[j_test].name,
                routine_workouts[i_test].muscles[j_test].parent->name); // TODO: Test. Remove.
        } // TODO: Test. Remove.
        printf("\n      ----------"); // TODO: Test. Remove
        for (int j_test = 0; j_test < routine_workouts[i_test].exercises_count; j_test++) { // TODO: Test. Remove.
            printf("\n      Included exercise [%d], name: %d, sets: %d",
                j_test,
                routine_workouts[i_test].exercises[j_test].name,
                routine_workouts[i_test].exercises[j_test].sets); // TODO: Test. Remove.
            for (int k_test = 0; k_test < routine_workouts[i_test].exercises[j_test].muscles_count; k_test++) { // TODO: Test. Remove.
                printf("\n          Included muscle [%d], name: %d, parent.name: %d, parent.sets: %d, parent != NULL: %d",
                    k_test,
                    routine_workouts[i_test].exercises[j_test].muscles[k_test].name,
                    routine_workouts[i_test].exercises[j_test].muscles[k_test].parent->name,
                    routine_workouts[i_test].exercises[j_test].muscles[k_test].parent->sets,
                    routine_workouts[i_test].exercises[j_test].muscles[k_test].parent != NULL); // TODO: Test. Remove.
            } // TODO: Test. Remove.
        } // TODO: Test. Remove.
    } // TODO: Test. Remove.
}

// TODO: Remove. Only for testing purposes.

void main() {

    // Answer questionnaire
    questionnaire.fitness_level = 5; // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
    questionnaire.ignored_muscle_group_names[0] = biceps;
    questionnaire.ignored_muscle_group_names_count = 1;
    questionnaire.available_workout_days[0]._day_of_the_week = monday;
    questionnaire.available_workout_days[0].max_duration = 50;
    questionnaire.available_workout_days[1]._day_of_the_week = tuesday;
    questionnaire.available_workout_days[1].max_duration = 30;
    questionnaire.available_workout_days[2]._day_of_the_week = wednesday;
    questionnaire.available_workout_days[2].max_duration = 20;
    questionnaire.available_workout_days[3]._day_of_the_week = friday;
    questionnaire.available_workout_days[3].max_duration = 20;
    questionnaire.available_workout_days[4]._day_of_the_week = saturday;
    questionnaire.available_workout_days[4].max_duration = 10;
    questionnaire.available_workout_days[5]._day_of_the_week = sunday;
    questionnaire.available_workout_days[5].max_duration = 30;
    questionnaire.available_workout_days_count = 5;

    // All muscle groups
    all_muscle_names[0] = chest;
    all_muscle_names[1] = triceps;
    all_muscle_names[2] = biceps;
    all_muscle_names[3] = quads;
    all_muscle_names_count = 4;

    // Valid resistance exercises
    exercise resistance_1 = {
        .is_aerobic = 0,
        .sets = 0,
        .specific_warmup_duration = 1,
        .set_duration = 1,
        .name = bench_press,
        .muscles_count = 2
        };
    muscle_group group_1_1 = {chest, NULL, 0};
    resistance_1.muscles[0] = group_1_1;
    muscle_group group_1_2 = {triceps, NULL, 0};
    resistance_1.muscles[1] = group_1_2;
    valid_resistance_exercises[0] = resistance_1;
    exercise resistance_2 = {
        .is_aerobic = 0,
        .sets = 0,
        .specific_warmup_duration = 1,
        .set_duration = 1,
        .name = push_up,
        .muscles_count = 2
        };
    muscle_group group_2_1 = {chest, NULL, 0};
    resistance_2.muscles[0] = group_2_1;
    muscle_group group_2_2 = {triceps, NULL, 0};
    resistance_2.muscles[1] = group_2_2;
    valid_resistance_exercises[1] = resistance_2;
    exercise resistance_3 = {
        .is_aerobic = 0,
        .sets = 0,
        .specific_warmup_duration = 1,
        .set_duration = 1,
        .name = bicep_curl,
        .muscles_count = 1
        };
    muscle_group group_3_1 = {biceps, NULL, 0};
    resistance_3.muscles[0] = group_3_1;
    valid_resistance_exercises[2] = resistance_3;
    exercise resistance_4 = {
        .is_aerobic = 0,
        .sets = 0,
        .specific_warmup_duration = 1,
        .set_duration = 1,
        .name = squat,
        .muscles_count = 1
        };
    muscle_group group_4_1 = {quads, NULL, 0};
    resistance_4.muscles[0] = group_4_1;
    valid_resistance_exercises[3] = resistance_4;
    valid_resistance_exercises_count = 4;

    // Valid aerobic exercises
    exercise aerobic_1 = {
        .is_aerobic = 1,
        .sets = 0,
        .set_duration = 0.5,
        .name = sprint,
        };
    valid_aerobic_exercises[0] = aerobic_1;
    exercise aerobic_2 = {
        .is_aerobic = 1,
        .sets = 0,
        .set_duration = 2,
        .name = burpees,
        };
    valid_aerobic_exercises[1] = aerobic_2;
    valid_aerobic_exercises_count = 2;

    update_workouts();


}

// TODO: Remove. Only for testing purposes.