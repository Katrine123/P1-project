#include <stdio.h>

#include "references.h"

void print_routine() {

    printf("\n\n\n\n================================");
    printf("\nYOUR FITNESS ROUTINE:");
    printf("\n================================");

    // Information about user
    printf("\n\nInformation about you which has been used, but might change as you progress:");
    printf("\n    Weight:           %.2lf kg", _questionnaire.weight);
    printf("\n    Fitness level:    %s", naming_fitness_level(_questionnaire._fitness_level));

    // Foreach available equipment
    printf("\n\nEquipment available to you:");
    for (int i = 0; i < _questionnaire.available_equipment_count; i++) {
        printf("\n    [%d] %s", i, naming_equipment(_questionnaire.available_equipment[i]));
    }
    if (_questionnaire.available_equipment_count == 0) {
        printf("\n    No equipment available");
    }

    // Foreach ignored muscle group
    printf("\n\nMuscle groups you have chosen to ignore:");
    for (int i = 0; i < _questionnaire.ignored_muscle_group_names_count; i++) {
        printf("\n    [%d] %s", i, naming_muscle_group(_questionnaire.ignored_muscle_group_names[i]));
    }
    if (_questionnaire.ignored_muscle_group_names_count == 0) {
        printf("\n    No muscle groups ignored");
    }

    // Established workout rules
    printf("\n\nWorkout rules based on your fitness level:");
    printf("\n    Assumed max daily resistance training sets per muscle group:      %d set(s)", max_daily_sets);
    printf("\n    Assumed max weekly resistance training sets per muscle group:     %d set(s)", max_weekly_sets);
    printf("\n    Assumed max weekly aerobic (HIIT) workouts:                       %d workout(s)", max_weekly_aerobic_workouts);
    printf("\n    Assumed rest between sets for resistance exercises:               %.2lf minute(s)", rest_between_sets_resistance);
    printf("\n    Assumed aerobic (HIIT) rest-to-work ratio:                        %.2lf:1", aerobic_rest_multiplier);
    printf("\n    Assumed recovery time of resistance training days:                %d day(s)", resistance_recovery);
    printf("\n    Assumed recovery time of aerobic (HIIT) training days:            %d day(s)", 1);

    // Foreach workout day
    for (int i = 0; i < routine_workouts_count; i++) {

        printf("\n\nDay: %s", naming_days(routine_workouts[i].day));
        printf("\n--------------------------");
        printf("\nAvailable time):              %.2lf minute(s)", _questionnaire.available_training_days[i].max_duration);

        // Edge case where the trainee has not even got time to do the full general warmup
        if (_questionnaire.available_training_days[i].max_duration < general_warmup_duration) {
            printf("\nEstimated workout duration:  %.2lf minute(s)", _questionnaire.available_training_days[i].max_duration);
            printf("\n--------------------------");
            printf("\nGeneral warmup (%.2lf minute(s))", _questionnaire.available_training_days[i].max_duration);
            break;
        } else if (_questionnaire.available_training_days[i].max_duration < 1) {
            printf("\nYou do not have time to train.");
            break;
        }

        printf("\nEstimated workout duration:  %.2lf minute(s)", routine_workouts[i].duration);
        printf("\n--------------------------");
        printf("\n[0] %d minute(s) general warmup", general_warmup_duration);

        // Foreach exercise
        for (int j = 0; j < routine_workouts[i].exercises_count; j++) {

            exercise _exercise = routine_workouts[i].exercises[j];

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

