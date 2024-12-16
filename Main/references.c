#include "references.h"

#pragma region global variables

int all_equipment_count = 5;
enum equipment all_equipment[ARRAY_MAX] = {
    barbell, bench, pull_up_bar, pull_down_machine, resistance_bands
};
int all_muscle_names_count = 5;
muscle_group_name all_muscle_names[ARRAY_MAX] = {
    chest, triceps, shoulders, hamstrings, quads
};

questionnaire _questionnaire;
// TODO: Only implemented in exercises.c.
exercise possible_resistance_exercises[ARRAY_MAX];
int possible_resistance_exercises_count;
// TODO: Only implemented in exercises.c.
exercise possible_aerobic_exercises[ARRAY_MAX];
int possible_aerobic_exercises_count;

exercise possible_aerobic_exercises[ARRAY_MAX];
int possible_aerobic_exercises_count;

workout routine_workouts[7];
int routine_workouts_count = 0; // Max 7 workouts per week (1 per day).

// Workout rules
const int general_warmup_duration = 5; // In minutes.
const int max_daily_sets = 6; // For resistance training.
const int max_daily_aerobic_exercises = 3; // 3 brings a good amount of variety without becoming overly complex.
const double rest_between_sets_resistance = 1.5; // In minutes. Equivalent to 90 seconds.
double aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.
int max_weekly_sets; // For resistance training.
int resistance_recovery;
int max_weekly_aerobic_workouts;

#pragma endregion

// Functions

void update_and_print_routine() {

    // Create list of exercises
    update_possible_exercises();

    all_possible_exercises();

    // Create routine workouts
    update_routine_workouts();

    // Print routine
    print_routine();
}
