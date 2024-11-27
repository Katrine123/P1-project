#include "workout_session.h"
#include <stdlib.h>

// Todo: Implement supersets (will decrease time spent + will need information about opposing muscle groups).

//todo place this inside the questionaire.c
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
    exercise exercises[32];
    muscle_group fatigued_muscle_groups[32];
    double duration; // in minutes
    enum day_of_the_week day;
} workout;


/// WARNING: Allocates memory using malloc(). Remember to dispose of the memory.
/// SUMMARY: Creates an array of workouts whilst taking into account:
/// 1) Available time per workout.
/// 2) Available workouts per week.
/// 3) Junk volume.
/// 4) Recovery time.
/// @param questionaire - the used questionaire.
/// @param resistance - array of resistance training exercises to be used.
/// @param aerobic - array of aerobic training exercises to be used.
workout *create_workouts(questionaire questionaire, exercise resistance[], int resistance_length, exercise aerobic[], int aerobic_length) {

    // Get workout rules (as defined in our P1 report)
    int resistance_weekly_sets_limit;
    int resistance_daily_sets_limit = 6; // any more sets are junk volume
    int resistance_recovery_time_in_days;
    int max_hiit_sessions_per_week;
    int aerobic_set_rest_multiplier;
    int general_warmup_duration = 5; // in minutes
    enum fitness_level level = questionaire.fitness_level;
    if (level >= novice) { // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
        resistance_weekly_sets_limit = 10; // to make it easier to get into the habit of fitness
        resistance_recovery_time_in_days = 3; // recovery time ranges from 48-72 hours for 6-15 reps
        max_hiit_sessions_per_week = 3; // limited, because beginners are recommended 1-3 sessions per week
        aerobic_set_rest_multiplier = 3; // 1:3 work-to-rest ratio
    } else if (level >= advanced_beginner) {
        resistance_weekly_sets_limit = 10; // to make it easier to get into the habit of fitness
        resistance_recovery_time_in_days = 3; // recovery time ranges from 48-72 hours for 6-15 reps
        max_hiit_sessions_per_week = 7; // no limit, because recovery time is 24 hours
        aerobic_set_rest_multiplier = 2; // 1:2 work-to-rest ratio
    } else {
        resistance_weekly_sets_limit = 20; //todo: add explanation (I should research what the max volume should be)
        resistance_recovery_time_in_days = 2; // recovery time ranges from 48-72 hours for 6-15 reps
        max_hiit_sessions_per_week = 7; // no limit, because recovery time is 24 hours
        aerobic_set_rest_multiplier = 1; // 1:1 work-to-rest ratio
    }

    // Allocate amount of workouts per week
    int workouts_per_week = sizeof(questionaire.available_workout_days) / sizeof(questionaire.available_workout_days[0]); //todo: is enum day_of_the_week
    workout* workouts = malloc(sizeof(workout) * workouts_per_week);
    for (int i = 0; i < workouts_per_week; i++ ) {
        workouts[i].duration = general_warmup_duration; // there is always included a general warm up in the workout
        workouts[i].day = questionaire.available_workout_days[0];
    }


    // Get resistance training days



    // Add resistance training exercises


    // Add aerobic training exercises

    // Fill workouts with sets


    // Reverse order of exercises (makes aerobic exercises come first)




    return workouts;
}


