#include "workouts.h"
#include <stdlib.h>
#include "lists.h"

//TODO:
// Workouts use lists. Both workouts (and resistance_workouts) and lists are put on the heap.
// Workouts are freed.
// But does the freeing of workouts also free the lists?
// fuck: https://stackoverflow.com/questions/71988582/freeing-a-struct-within-a-struct-in-c

// TODO: Remember to always free any list that is created.

// TODO: Maybe use lists everywhere instead of arrays? (E.g. in create_workouts).

// TODO: Implement supersets (will decrease time spent + will need information about opposing muscle groups).

// TODO: Place this inside the questionaire.c
enum day_of_the_week {
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6,
    sunday = 7
};

typedef struct {
    list exercises;
    double duration_in_minutes;
    double max_duration_in_minutes;
    enum day_of_the_week day;
} workout;

typedef struct {
    workout* workout;
    list missing_muscle_groups; // The muscle groups that the workout is currently missing.
} resistance_workout;

typedef struct {
    const int general_warmup_duration_in_minutes = 5;
    const int resistance_daily_sets_limit = 6; // Any more sets are junk volume.
    int resistance_weekly_sets_limit;
    int resistance_recovery_time_in_days;
    int max_hiit_sessions_per_week;
    int aerobic_set_rest_multiplier;
} workout_rules;

workout_rules get_workout_rules(questionaire q) {
    workout_rules rules;
    enum fitness_level level = q.fitness_level;
    if (level >= novice) { // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
        rules.resistance_weekly_sets_limit = 10; // To make it easier to get into the habit of fitness.
        rules.resistance_recovery_time_in_days = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_hiit_sessions_per_week = 3; // Limited, because beginners are recommended 1-3 sessions per week.
        rules.aerobic_set_rest_multiplier = 3; // 1:3 work-to-rest ratio.
    } else if (level >= advanced_beginner) {
        rules.resistance_weekly_sets_limit = 10; // To make it easier to get into the habit of fitness.
        rules.resistance_recovery_time_in_days = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_hiit_sessions_per_week = 7; // No limit, because recovery time is 24 hours.
        rules.aerobic_set_rest_multiplier = 2; // 1:2 work-to-rest ratio.
    } else {
        rules.resistance_weekly_sets_limit = 20; // todo: add explanation (I should research what the max volume should be)
        rules.resistance_recovery_time_in_days = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_hiit_sessions_per_week = 7; // No limit, because recovery time is 24 hours.
        rules.aerobic_set_rest_multiplier = 1; // 1:1 work-to-rest ratio.
    }
    return rules;
}

/// WARNING: Allocates memory using malloc(). Remember to dispose of the memory.
workout* initialize_workouts(questionaire q, workout_rules rules, int *output_workouts_per_week) {
    // TODO: Use lists instead

    // TODO: I don't know if the workouts_per_week calculation will work because questionaire is a parameter.
    *output_workouts_per_week = sizeof(q.available_workout_days) / sizeof(q.available_workout_days[0]);
    workout* workouts = malloc(sizeof(workout) * *output_workouts_per_week);
    // Assign stat variables for the workout structs
    for (int i = 0; i < *output_workouts_per_week; i++) {
        workouts[i].day = q.available_workout_days[i].week_day; //todo available_workout_days is a struct workout_day with an enum week_day and an int max_duration_in_minutes.
        workouts[i].max_duration_in_minutes = q.available_workout_days[i].max_duration_in_minutes;
        // Add general warm-up to workout duration
        workouts[i].duration_in_minutes = rules.general_warmup_duration_in_minutes;
    }
    return workouts;
}

resistance_workout* create_resistance_training_days(workout_rules rules, workout* workouts, int workouts_per_week) {
    resistance_workout resistance_workouts[3] = {NULL, NULL, NULL}; // Can max be 3 (48-72 hours of recovery).
    int last_resistance_workout_index = 0;
    // Loop through workout days.
    for (int i_workout = 0; i_workout < workouts_per_week; i_workout++ ) {
        int is_valid = 1;
        // In case no resistance training days exist, the day must be valid.
        if (last_resistance_workout_index == 1) {
            break;
        }
        // Loop through resistance training days.
        for (int i_resistance = 0; i_resistance <= last_resistance_workout_index; i_resistance++) {
            int days_between = workouts[i_workout].day - resistance_workouts[i_resistance].workout->day;
            // Account for if the check day is in next week (e.g. the days between Sunday and Monday).
            if (days_between < 0) {
                days_between += 7;
            }
            // Mark day as invalid, if recovery rules are not met.
            if (days_between < rules.resistance_recovery_time_in_days) {
                is_valid = 0;
                break;
            }
        }
        // Add valid days to the list of resistance training workouts.
        if (is_valid) {
            resistance_workouts[last_resistance_workout_index].workout = &workouts[i_workout];
            // Add muscle groups that must be targeted in the workout.
            resistance_workouts[last_resistance_workout_index].missing_muscle_groups = get_required_muscle_groups(); // TODO: Implement this function (it should return a List with an enum muscle_group as the data type).
            last_resistance_workout_index++;
        }
    }
    return resistance_workouts;
}

exercise get_resistance_exercise_candidate() {

}

void add_resistance_exercises(questionaire q, resistance_workout* resistance_workouts, int resistance_workouts_count) {
    // Loop until no modifications are made to the workouts.
    int modified_a_day_this_loop;
    do {
        modified_a_day_this_loop = 0;
        // Loop through the resistance training days.
        for (int i = 0; i < resistance_workouts_count; i++) {
            resistance_workout *target_workout = &resistance_workouts[i];
            list_node *missing_muscle_group = get_last_node(target_workout->missing_muscle_groups);
            // Continue, if all muscle groups are already included in the workout.
            if (missing_muscle_group == NULL) {
                continue;
            }
            exercise exercise_candidate = get_resistance_exercise_candidate();
            // Continue, if you cannot find a suiting exercise candidate.
            if (exercise_candidate == NULL) {
                continue;
            }
            // Add exercise and specific warm-up
            //TODO Redo this to use lists

            resistance_workouts->workout->exercises[resistance_workouts->workout->last_exercise_index] = exercise_candidate;
            delete_node(missing_muscle_group); //
            resistance_workouts->workout->last_exercise_index++;
            resistance_workouts->workout->duration_in_minutes += exercise_candidate.duration;
            modified_a_day_this_loop = 1;
        }
    } while (modified_a_day_this_loop == 1);
}

void add_aerobic_exercises(workout* workouts) {

}

void fill_workouts_with_sets(workout* workouts) {

}

void reverse_order_of_exercises(workout* workouts) {

}


/// WARNING: Allocates memory using malloc(). Remember to dispose of the memory.
/// SUMMARY: Creates an array of workouts to be used as the final fitness routine.
/// @param q - the used questionaire.
/// @param resistance - array of resistance training exercises to be used.
/// @param aerobic - array of aerobic training exercises to be used.
workout *create_workouts(questionaire q, exercise resistance[], int resistance_length, exercise aerobic[], int aerobic_length) {
    workout_rules rules = get_workout_rules();
    int workouts_per_week;
    workout* workouts = initialize_workouts();
    resistance_workout* resistance_workouts = create_resistance_training_days();

    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();
    reverse_order_of_exercises(); // Makes aerobic exercises come before resistance exercises.

    return workouts;
}

