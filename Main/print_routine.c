#include <stdio.h>

#include "references.h"

void print_routine(user_data *user) {

    printf("\n\n\n\n================================");
    printf("\nYOUR FITNESS ROUTINE:");
    printf("\n================================");

    // Information about user
    printf("\n\nInformation about you which has been used, but might change as you progress:");
    printf("\n    Weight:           %.2lf kg", user->weight);
    printf("\n    Fitness level:    %s", naming_fitness_level(user->_fitness_level));
    printf("\n    Training Goal:    %s", naming_training_goal(user->training_goal));


    // Foreach available equipment
    printf("\n\nEquipment available to you:");
    for (int i = 0; i < user->available_equipment_count; i++) {
        printf("\n    [%d] %s", i, naming_equipment(user->available_equipment[i]));
    }
    if (user->available_equipment_count == 0) {
        printf("\n    No equipment available");
    }

    // Foreach ignored muscle group
    printf("\n\nMuscle groups you have chosen to ignore:");
    for (int i = 0; i < user->ignored_muscle_group_names_count; i++) {
        printf("\n    [%d] %s", i, naming_muscle_group(user->ignored_muscle_group_names[i]));
    }
    if (user->ignored_muscle_group_names_count == 0) {
        printf("\n    No muscle groups ignored");
    }

    // Show workout rules for everyone other than complete beginners (we don't want to confuse them)
    if (user->_fitness_level < novice) {
        printf("\n\nWorkout rules based on your fitness level:");
        printf("\n    Assumed max daily resistance training sets per muscle group:      %d set(s)", user->max_daily_sets);
        printf("\n    Assumed max weekly resistance training sets per muscle group:     %d set(s)", user->max_weekly_sets);
        printf("\n    Assumed max weekly aerobic (HIIT) workouts:                       %d workout(s)", user->max_weekly_aerobic_workouts);
        printf("\n    Assumed rest between sets for resistance exercises:               %.2lf minute(s)", user->rest_between_sets_resistance);
        printf("\n    Assumed aerobic (HIIT) rest-to-work ratio:                        %.2lf:1", user->aerobic_rest_multiplier);
        printf("\n    Assumed recovery time of resistance training days:                %d day(s)", user->resistance_recovery);
        printf("\n    Assumed recovery time of aerobic (HIIT) training days:            %d day(s)", 1);
    }

    // Foreach workout day
    for (int i = 0; i < user->routine_workouts_count; i++) {

        printf("\n\nDay: %s", naming_days(user->routine_workouts[i].day));
        printf("\n--------------------------");
        printf("\nAvailable time):                  %.2lf minute(s)", user->available_training_days[i].max_duration);

        // Edge case where the trainee has not even got time to do the full general warmup.
        // NOTE: Warm-ups are always added to a workout, even if that day's available time
        // is less than the duration of the workout. For example, on a day with 3 minutes of available
        // workout time, the workout duration will still be 5 minutes if the general_warmup_duration is 5 minutes.
        double new_workout_duration = user->routine_workouts[i].duration;
        double new_general_warmup_duration = user->general_warmup_duration;
        if (user->available_training_days[i].max_duration < user->general_warmup_duration) {
            new_workout_duration = user->available_training_days[i].max_duration;
            new_general_warmup_duration = user->available_training_days[i].max_duration;
        } else if (user->available_training_days[i].max_duration < 1) {
            printf("\nYou do not have time to train.");
            break;
        }

        printf("\nEstimated workout duration:       %.2lf minute(s)", new_workout_duration);
        printf("\n--------------------------");
        printf("\n[0] %.2lf minute(s) general warmup", new_general_warmup_duration);

        // Foreach exercise in the workout
        for (int j = 0; j < user->routine_workouts[i].exercises_count; j++) {

            exercise _exercise = user->routine_workouts[i].exercises[j];

            printf("\n[%d] %s: %d set(s) of %d rep(s)",
                j+1, //+1 to make room for the general warmup
                naming_exercises(_exercise.name),
                _exercise.sets,
                _exercise.reps);

            if (!_exercise.is_body_weight_exercise) {
                printf(", %.2lf kg", _exercise.base_weight);
            }

            if (!_exercise.is_aerobic) {
                printf(" (remember to do an exercise-specific warm-up)");
            }

            printf(".");
        }
    }
}

