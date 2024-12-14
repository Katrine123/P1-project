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
workout routine_workouts[7];
int routine_workouts_count = 0; // Max 7 workouts per week (1 per day).

#pragma endregion