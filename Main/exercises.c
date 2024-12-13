#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "references.h"

#define MAX_REPS 15

// Helper functions

///function for rounding down to the nearest number divisible by 2.5
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
//Pushups should be the printed exercise if the person can take less than 15 consecutive pushups
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

// Exercise array update functions

int is_equipment_available(enum equipment _equipment) {

    // Foreach available piece of equipment
    for (int i = 0; i < _questionnaire.available_equipment_count; i++) {

        // Return true if the target equipment is found
        if (_questionnaire.available_equipment[i] == _equipment) {
            return 1;
        }
    }

    // Return false if the target equipment is not found
    return 0;
}
void update_array_of_possible_resistance_exercises()
{
    // Reset array of valid aerobic exercises
    possible_resistance_exercises_count = 0;

    //  With equipment
    //  Bench press
    exercise _bench_press = {
        .muscles_count = 0,
        .name = bench_press,
        .addition = 2.5,
        .base_weight = base_weight_bench_press(),
        .reps = 12,
        .is_body_weight_exercise = 0,
        .set_duration = 0.5,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    if (is_equipment_available(bench) && is_equipment_available(barbell)) {
        _bench_press.muscles[_bench_press.muscles_count++] = { chest };
        _bench_press.muscles[_bench_press.muscles_count++] = { triceps };
        _bench_press.muscles[_bench_press.muscles_count++] = { shoulders };
        possible_resistance_exercises[possible_resistance_exercises_count++] = _bench_press;
    }

    //  Weighted squats
    exercise _weighted_squat = {
        .muscles_count = 0,
        .name = weighted_squat,
        .addition = 2.5,
        .base_weight = base_weight_weighted_squats(),
        .reps = 12,
        .is_body_weight_exercise = 0,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    if (is_equipment_available(barbell)) {
        _weighted_squat.muscles[_weighted_squat.muscles_count++] = { quads };
        _weighted_squat.muscles[_weighted_squat.muscles_count++] = { hamstrings };
        possible_resistance_exercises[possible_resistance_exercises_count++] = _weighted_squat;
    }

    //  Air squats
    exercise _air_squat = {
        .muscles_count = 0,
        .name = air_squat,
        .addition = 1,
        .reps = base_amount_air_squats(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _air_squat.muscles[_air_squat.muscles_count++] = { quads };
    _air_squat.muscles[_air_squat.muscles_count++] = { hamstrings };
    possible_resistance_exercises[possible_resistance_exercises_count++] = _air_squat;

    //  Pushups
    exercise _pushup = {
        .muscles_count = 0,
        .name = pushup,
        .addition = 1,
        .reps = base_amount_pushups(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _pushup.muscles[_pushup.muscles_count++] = { chest };
    _pushup.muscles[_pushup.muscles_count++] = { triceps };
    _pushup.muscles[_pushup.muscles_count++] = { shoulders };
    possible_resistance_exercises[possible_resistance_exercises_count++] = _pushup;

    //  Elevated Pushups
    exercise _elevated_pushup = {
        .muscles_count = 0,
        .name = elevated_pushup,
        .addition = 1,
        .reps = base_amount_elevated_pushups(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++] = { chest };
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++] = { triceps };
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++] = { shoulders };
    possible_resistance_exercises[possible_resistance_exercises_count++] = _elevated_pushup;
}
void update_array_of_possible_aerobic_exercises() {

    // Reset array of valid aerobic exercises
    possible_aerobic_exercises_count = 0;

    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise _burpees = {
        .muscles_count = 0,
        .name = burpee,
        .addition = 2,
        .reps = base_amount_burpees(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
    };
    // No equipment required
    possible_aerobic_exercises[possible_aerobic_exercises_count++] = _burpees;

    //  find endnu en øvelse af HIIT der er mere aerobic
    exercise _jumping_jacks = {
        .muscles_count = 0,
        .name = jumping_jacks,
        .addition = 2,
        .reps = base_amount_jumping_jacks(),
        .is_body_weight_exercise = 1,
        .set_duration = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
    };
    // No equipment required
    possible_aerobic_exercises[possible_aerobic_exercises_count++] = _jumping_jacks;
}

