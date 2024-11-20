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
    double duration;
    enum day_of_the_week day;
} workout;




/// WARNING: Allocates memory using malloc(). Remember to dispose of the memory.
/// SUMMARY: Creates an array of workouts.
/// Takes into account:
/// 1) available time per workout.
/// 2) available workouts per week.
/// 3) junk volume
/// todo: Find information about HIIT max sets.
/// (resistance training: no more than 6 sets per muscle group per workout).
/// 4) recovery time
/// (resistance training: 72 hours per muscle group for beginners, 48 hours for more advanced trainees).
/// todo: Find information about HIIT recovery time.
/// @param questionaire the used questionaire.
/// @param resistance array of resistance training exercises to be used.
/// @param aerobic array of aerobic training exercises to be used.
workout *create_workouts(questionaire questionaire, exercise resistance[], int resistance_length, exercise aerobic[], int aerobic_length) {

    /* Ideas:
     * - Look at each muscle group and add an exercise that does that (only one set)
     * - When the workout array has been filled out with these, increase reps until max workout time is reached
     *
     */

    //My idea is that, for resistance training, you must warm up for each exercise (do a warmup set),
    //because resistance training puts a lot of strain on specific muscle groups,
    //whereas aerobic training is more focused on straining the respiratory system,
    //so a general warmup is good enough for it.
    //So, I should find information about this on the internet.

    //todo: implement changes based on fitness level
    int weekly_sets_limit = 20; //todo: add explanation in report
    int daily_sets_limit = 6;
    int resistance_recovery_time_in_days = 2;
    int aerobic_recovery_time_in_days = ?; //todo: HIIT recovery time
    if (questionaire.fitness_level >= advanced_beginner) { // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
        weekly_sets_limit = 10;  //todo: add explanation in report
        daily_sets_limit = 5; //todo: add explanation in report
        resistance_recovery_time_in_days = 3;
        aerobic_recovery_time_in_days = ?; //todo: HIIT recovery time
    }
    if (questionaire.fitness_level >= novice) {
        daily_sets_limit = 4; //todo: add explanation in report
    }

    // Set workouts per week
    int workouts_per_week = sizeof(questionaire.available_workout_days) / sizeof(questionaire.available_workout_days[0]); //todo is enum day_of_the_week
    workout* workouts = malloc(sizeof(workout) * workouts_per_week);
    for (int i = 0; i < workouts_per_week; i++ ) {
        workouts[i].duration = 0;
        workouts[i].day = questionaire.available_workout_days[0];
    }

    // Add exercises to workouts
    //todo: do stuff

    return workouts;
}


