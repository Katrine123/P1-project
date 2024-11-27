#include "workouts.h"
#include <stdlib.h>

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
    exercise exercises[32]; // Length of 32 simply because it is big enough.
    // TODO: Implement this struct.
    double duration; // In minutes.
    enum day_of_the_week day;
} workout;

typedef struct {
    workout* workout;
    muscle_group missing_muscle_groups[32]; // The muscle groups the workout is currently missing. Length of 32 simply because it is big enough.
    // TODO: Implement this enum.
} resistance_workout;


/// WARNING: Allocates memory using malloc(). Remember to dispose of the memory.
/// SUMMARY: Creates an array of workouts to be used as the final fitness routine.
/// @param questionaire - the used questionaire.
/// @param resistance - array of resistance training exercises to be used.
/// @param aerobic - array of aerobic training exercises to be used.
workout *create_workouts(questionaire questionaire, exercise resistance[], int resistance_length, exercise aerobic[], int aerobic_length) {

    // Get workout rules (general)
    int resistance_weekly_sets_limit;
    int resistance_daily_sets_limit = 6; // Any more sets are junk volume.
    int resistance_recovery_time_in_days;
    int max_hiit_sessions_per_week;
    int aerobic_set_rest_multiplier;
    int general_warmup_duration = 5; // In minutes.
    enum fitness_level level = questionaire.fitness_level;

    // Get workout rules (depending on fitness level)
    if (level >= novice) { // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
        resistance_weekly_sets_limit = 10; // To make it easier to get into the habit of fitness.
        resistance_recovery_time_in_days = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_hiit_sessions_per_week = 3; // Limited, because beginners are recommended 1-3 sessions per week.
        aerobic_set_rest_multiplier = 3; // 1:3 work-to-rest ratio.
    } else if (level >= advanced_beginner) {
        resistance_weekly_sets_limit = 10; // To make it easier to get into the habit of fitness.
        resistance_recovery_time_in_days = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_hiit_sessions_per_week = 7; // No limit, because recovery time is 24 hours.
        aerobic_set_rest_multiplier = 2; // 1:2 work-to-rest ratio.
    } else {
        resistance_weekly_sets_limit = 20; // todo: add explanation (I should research what the max volume should be)
        resistance_recovery_time_in_days = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        max_hiit_sessions_per_week = 7; // No limit, because recovery time is 24 hours.
        aerobic_set_rest_multiplier = 1; // 1:1 work-to-rest ratio.
    }

    // Allocate amount of workouts per week.
    // TODO: I don't know if the workouts_per_week calculation will work because questionaire is a parameter.
    int workouts_per_week = sizeof(questionaire.available_workout_days) / sizeof(questionaire.available_workout_days[0]);
    workout* workouts = malloc(sizeof(workout) * workouts_per_week);
    for (int i = 0; i < workouts_per_week; i++) {
        workouts[i].day = questionaire.available_workout_days[0];
        // Add general warm-up to workout duration
        workouts[i].duration = general_warmup_duration;
    }

    // Get resistance training days.
    resistance_workout resistance_workouts[3] = {NULL, NULL, NULL}; // Can max be 3 (48-72 hours of recovery).
    int last_res_workout_index = 0;
    // Loop through the week of workouts.
    for (int i_work = 0; i_work < workouts_per_week; i_work++ ) {
        int is_valid = 1;
        // In case no resistance training days exist, the day must be valid.
        if (last_res_workout_index != 0) {
            // Loop through resistance training days.
            for (int i_res = 0; i_res <= last_res_workout_index; i_res++) {
                int days_between = workouts[i_work].day - resistance_workouts[last_res_workout_index];
                // Account for if the check day is in next week (e.g. the days between Sunday and Monday).
                if (days_between < 0) {
                    days_between += 7;
                }
                // Mark day as invalid, if recovery rules are not met.
                if (days_between < resistance_recovery_time_in_days) {
                    is_valid = 0;
                    break;
                }
            }
        }
        // Add valid days to the list of resistance training workouts.
        if (is_valid) {
            resistance_workouts[last_res_workout_index].workout = workouts[i_work];
            // Add muscle groups that must be targeted in the workout.
            resistance_workouts[last_res_workout_index].missing_muscle_groups = get_required_muscle_groups(); // TODO: Implement this function.
            last_res_workout_index++;
        }
    }

    // Add resistance training exercises.
    // TODO: This could be a recursive function instead of a while loop
    int continue_looping;
    do {
        continue_looping = 0;
        // Loop through all resistance training days.
        for (int i = 0; i <= last_res_workout_index; i++ ) {
            // Check if not all required muscle groups have been targeted that day.
            // TODO
            // Break, if workout duration limit is exceeded by adding an exercise.
            // TODO
            // Add an exercise for the missing muscle group
            // TODO
            continue_looping = 1;
        }
    } while (continue_looping == 1);

    // Add aerobic training exercises


    // Fill workouts with sets


    // Reverse order of exercises (makes aerobic exercises come first)




    return workouts;
}


