#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "references.h"

#define MAX_REPS 15

// Helper functions

///function for rounding down to the nearest number divisbl by 2.5
double round_down_to_nearest (double number, double divisor) {
    return floor(number / divisor) * divisor;
}

// Base_weight functions

///  Calculating base weight for bench press from pushups
double base_weight_bench_press() {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = _questionnaire.weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*_questionnaire.pushups)));
    //  Calculating the height the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_bench_press * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}
double base_weight_weighted_squats() {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.66 since that is the percentage of bodyweigth lifted during an air squat
    double body_weight_squats = _questionnaire.weight* 0.66;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_weighted_squat = (100 * body_weight_squats)/(52.2+41.9*pow(M_E,(-0.055*_questionnaire.squats)));

    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_weighted_squat * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}
// Air squats should be the exercise if the perosn can take less than 15 consecutive air squats
int base_amount_air_squats() {
    int reps_amount_squats = MAX_REPS - _questionnaire._fitness_level;
    return reps_amount_squats;
}
//Split squats should be the printed exercise if the person can take more than 15 consecutive air squats
int base_amount_split_squats() {
    int reps_amount_split_squats = MAX_REPS - _questionnaire._fitness_level;
    return reps_amount_split_squats;
}
//Elevated pushups should be the printed exercise if the person can take more than 15 consecutive pushups
int base_amount_elevated_pushups() {
        int reps_amount_elevated_pushups = MAX_REPS - _questionnaire._fitness_level;
        return reps_amount_elevated_pushups;
}
//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups() {
        int reps_amount_pushups = MAX_REPS - _questionnaire._fitness_level;
        return reps_amount_pushups;
}
int base_amount_burpees() {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    int reps_amount_burpees = MAX_REPS - (_questionnaire._fitness_level*2);
    return reps_amount_burpees;
}
int base_amount_jumping_jacks() {
    int reps_amount_jumping_jacks = MAX_REPS - (_questionnaire._fitness_level);
    return reps_amount_jumping_jacks;
}

// TODO: Remove this?
// Print function to display the viable exercises
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user, exercise exercises_list[]) {
    printf("Viable Exercises:\n");
    printf("SE HER: %d", count);
    for (int i = 0; i < count; i++) {
        printf("\n_____________________________\n");
        printf("Exercise %d:\n", i + 1);
        printf("Name: %d\n", sorted_exercise_list[i].name);
        printf("Addition: %.2lf\n", sorted_exercise_list[i].addition);
        if(sorted_exercise_list[i].base_weight != user.weight) {
            printf("Base weight: %.2lf\n", sorted_exercise_list[i].base_weight);
        }
        printf("Reps: %.2lf\n", sorted_exercise_list[i].reps);
        if (sorted_exercise_list[i].check_eq[0] == 1) {
            printf(" - Barbell\n");
        }
        if (sorted_exercise_list[i].check_eq[1] == 1) {
            printf(" - Bench\n");
        }
        if (sorted_exercise_list[i].check_eq[2] == 1) {
            printf(" - Pull up bar\n");
        }
        if (sorted_exercise_list[i].check_eq[3] == 1) {
            printf(" - Pull down machine\n");
        }
        if (sorted_exercise_list[i].check_eq[4] == 1) {
            printf(" - Resistance bands\n");
        }


        // Add more details as needed, e.g., equipment, difficulty, etc.
    }
}

// Exercise array update functions

// TODO: Old method:
// exercise* create_available_exercises(exercise exercises_list[], questionnaire user_questionnaire, int *count) {
//     // Sorter de exercises fra, som brugeren ikke kan udføre pga. udstyr
//     exercise* sorted_exercise_list = (exercise *)malloc(sizeof(exercise) * length_of_exercises_list);
//
//     *count = 0;
//
//     for (int n=0; n<(length_of_exercises_list); n++) { // loop to cycle through exercise list
//         int fail_switch = 0;
//         for (int i=0; i<length_of_equipment_enum; i++) { // Loop to cycle through exercise equipment also "length_of_equipment_enumn" instead of 4
//             if (exercises_list[n].check_eq[i]>user_questionnaire.available_equipment[i]) { // Checks all exercises equipment against user equipment, user.equipment might not be correct name
//                 fail_switch = 1;
//                 break;
//             }
//         }
//         if (fail_switch==0) { // checks if fail_switch fails if not exercise is added to new list of viable exercises
//             sorted_exercise_list[*count] = exercises_list[n]; // creates new list of sorted_exercise list
//             (*count)++;
//         }
//     }
//     return sorted_exercise_list;
// }

int does_user_have_required_equipment(exercise _exercise) {

    //TODO: Not finished yet!

    int result = 0;

    // Foreach
    for (int i = 0; i < length_of_equipment_enum; i++) {



        if (_exercise.check_eq[i] > _questionnaire.available_equipment[i]) { // Checks all exercises equipment against user equipment, user.equipment might not be correct name
            fail_switch = 1;
            break;
        }
    }
    if (fail_switch==0) { // checks if fail_switch fails if not exercise is added to new list of viable exercises
        sorted_exercise_list[*count] = exercises_list[n]; // creates new list of sorted_exercise list
        (*count)++;
    }

}
void update_array_of_possible_resistance_exercises()
{
    // Reset array of valid aerobic exercises
    possible_resistance_exercises_count = 0;

    //  With equipment
    //  Bench press
    exercise _bench_press = {
        .name = bench_press,
        .check_eq = {1, 1, 0, 0, 0},
        .addition = 2.5,
        .base_weight = base_weight_bench_press(),
        .reps = 12,
        .is_body_weight_exercise = 0,
        .set_duration = 0.5,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
        .muscles_count = 3,
    };
    if (does_user_have_required_equipment) {
        _bench_press.muscles[0] = { chest };
        _bench_press.muscles[1] = { triceps };
        _bench_press.muscles[2] = { shoulders };
        possible_resistance_exercises[possible_resistance_exercises_count] = _bench_press;
        possible_resistance_exercises_count++;
    }

    //  Weighted squats
    exercise _weighted_squat = {
        .name = weighted_squat,
        .check_eq = {1, 0, 0, 0, 0},
        .addition = 2.5,
        .base_weight = base_weight_weighted_squats(),
        .reps = 12,
        .is_body_weight_exercise = 0,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
        .muscles_count = 2,
    };
    if (does_user_have_required_equipment) {
        _bench_press.muscles[0] = { quads };
        _bench_press.muscles[1] = { hamstrings };
        possible_resistance_exercises[possible_resistance_exercises_count] = _weighted_squat;
        possible_resistance_exercises_count++;
    }

    //  Air squats
    exercise _air_squat = {
        .name = air_squat,
        .check_eq = {0, 0, 0, 0, 0},
        .addition = 1,
        .base_weight = _questionnaire.weight,
        .reps = base_amount_air_squats(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
        .muscles_count = 2,
    };
    if (does_user_have_required_equipment) {
        _bench_press.muscles[0] = { quads };
        _bench_press.muscles[1] = { hamstrings };
        possible_resistance_exercises[possible_resistance_exercises_count] = _air_squat;
        possible_resistance_exercises_count++;
    }

    //  Pushups
    exercise _pushup = {
        .name = pushup,
        .check_eq = {0, 0, 0, 0, 0},
        .addition = 1,
        .base_weight = _questionnaire.weight,
        .reps = base_amount_pushups(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
        .muscles_count = 3,
    };
    if (does_user_have_required_equipment) {
        _bench_press.muscles[0] = { chest };
        _bench_press.muscles[1] = { triceps };
        _bench_press.muscles[2] = { shoulders };
        possible_resistance_exercises[possible_resistance_exercises_count] = _pushup;
        possible_resistance_exercises_count++;
    }

    //  Elevated Pushups
    exercise _elevated_pushup = {
        .name = elevated_pushup,
        .check_eq = {0, 0, 0, 0, 0},
        .addition = 1,
        .base_weight = _questionnaire.weight,
        .reps = base_amount_elevated_pushups(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
        .muscles_count = 3,
    };
    if (does_user_have_required_equipment) {
        _bench_press.muscles[0] = { chest };
        _bench_press.muscles[1] = { triceps };
        _bench_press.muscles[2] = { shoulders };
        possible_resistance_exercises[possible_resistance_exercises_count] = _elevated_pushup;
        possible_resistance_exercises_count++;
    }
}
void update_array_of_possible_aerobic_exercises() {

    // Reset array of valid aerobic exercises
    possible_aerobic_exercises_count = 0;

    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise _burpees = {
        .name = burpee,
        .check_eq = {0, 0, 0, 0, 0},
        .addition = 2,
        .base_weight = _questionnaire.weight,
        .reps = base_amount_burpees(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
        .muscles_count = 0,
    };
    if (does_user_have_required_equipment) {
        possible_aerobic_exercises[possible_aerobic_exercises_count] = _burpees;
        possible_aerobic_exercises_count++;
    }

    //  find endnu en øvelse af HIIT der er mere aerobic
    exercise _jumping_jack = {
        .name = jumping_jack,
        .check_eq = {0, 0, 0, 0, 0},
        .addition = 2,
        .base_weight = _questionnaire.weight,
        .reps = base_amount_jumping_jacks(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
        .muscles_count = 0,
    };
    if (does_user_have_required_equipment) {
        possible_aerobic_exercises[possible_aerobic_exercises_count] = _jumping_jack;
        possible_aerobic_exercises_count++;
    }
}

