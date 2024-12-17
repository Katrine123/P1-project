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

int training_goal_reps(user_data *user) {
    int training_goal_reps = 0;
    if(user->training_goal == MUSCULAR_ENDURANCE) {
        training_goal_reps = 15;
    } else if(user->training_goal == HYPERTROPHY || user->training_goal == I_DONT_KNOW) {
        training_goal_reps = 12;
    } else {
        training_goal_reps = 5;
    }
    return training_goal_reps;
}

double training_goal_converter(user_data *user) {
    double training_goal_converter = 0;
    if(user->training_goal == MUSCULAR_ENDURANCE) {
        training_goal_converter = 0.65;
    } else if(user->training_goal == HYPERTROPHY || user->training_goal == I_DONT_KNOW) {
        training_goal_converter = 0.75;
    } else {
        training_goal_converter = 0.85;
    }
    return training_goal_converter;
}

double fitness_level(user_data *user) {
    double fitness_level = 0;
    if (user->_fitness_level == novice) {
        fitness_level = 0.5;
    } else if (user->_fitness_level == advanced_beginner) {
        fitness_level = 0.6;
    } else if (user->_fitness_level == competent) {
        fitness_level = 0.7;
    } else if (user->_fitness_level == proficient) {
        fitness_level = 0.8;
    } else {
        fitness_level = 0.9;
    }
    return fitness_level;
}

/// function for calculating bodyweight exercise's base reps
int base_amount_calculation(user_data *user, int user_1rm_exercise) {
    return (int)user_1rm_exercise * fitness_level(user);
}

// Base_weight functions

///  Calculating base weight for bench press from pushups
double base_weight_bench_press(user_data *user) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = user->weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*user->pushups)));
    //  Calculating the height the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_bench_press * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    if(weight_to_lift_rounded < 0) {
        weight_to_lift_rounded = -1;
    }
    return weight_to_lift_rounded;
}
double base_weight_weighted_squats(user_data *user) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.66 since that is the percentage of bodyweigth lifted during an air squat
    double body_weight_squats = user->weight* 0.66;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_weighted_squat = (100 * body_weight_squats)/(52.2+41.9*pow(M_E,(-0.055*user->squats)));

    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_weighted_squat * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    if(weight_to_lift_rounded < 0) {
        weight_to_lift_rounded = -1;
    }
    return weight_to_lift_rounded;
}
// Air squats should be the exercise if the perosn can take less than 15 consecutive air squats
int base_amount_air_squats(user_data *user) {
    //  The calculation takes into account the users 1rm, fitness_level and training goal when calculating reps.
    return base_amount_calculation(user, user->squats);
}

//Split squats should be the printed exercise if the person can take more than 15 consecutive air squats
int base_amount_split_squats(user_data *user) {
    return base_amount_calculation(user, user->squats);
}

//Elevated pushups should be the printed exercise if the person can take more than 15 consecutive pushups
int base_amount_elevated_pushups(user_data *user) {
    return base_amount_calculation(user, user->pushups);
}

//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups(user_data *user) {
    return base_amount_calculation(user, user->pushups);
}

int base_amount_burpees(user_data *user) {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    return base_amount_calculation(user, (user->pushups+user->squats));
}

int base_amount_jumping_jacks(user_data *user) {
    return base_amount_calculation(user, user->squats);
}

// Exercise array update functions

int is_equipment_available(user_data *user, enum equipment _equipment) {

    // Foreach available piece of equipment
    for (int i = 0; i < user->available_equipment_count; i++) {

        // Return true if the target equipment is found
        if (user->available_equipment[i] == _equipment) {
            return 1;
        }
    }

    // Return false if the target equipment is not found
    return 0;
}
int does_not_contain_ignored_muscle_group(user_data *user, exercise _exercise) {

    // Foreach muscle group that the exercise targets
    for (int i = 0; i < _exercise.muscles_count; i++) {

        // Foreach ignored muscle group
        for (int j = 0; j < user->ignored_muscle_group_names_count; j++) {

            // Return false if found
            if (_exercise.muscles[i].name == user->ignored_muscle_group_names[j]) {
                return 0;
            }
        }
    }

    // Return true if not found
    return 1;
}
void update_possible_resistance_exercises(user_data *user)
{
    // Reset array of valid aerobic exercises
    user->possible_resistance_exercises_count = 0;

    //  With equipment
    //  Bench press
    exercise _bench_press = {
        .muscles_count = 0,
        .name = bench_press,
        .addition = 2.5,
        .base_weight = base_weight_bench_press(user),
        .reps = 12,
        .rep_duration = 0.1, // 6 seconds
        .is_body_weight_exercise = 0,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    if (is_equipment_available(user, bench) && is_equipment_available(user, barbell)) {
        _bench_press.muscles[_bench_press.muscles_count++].name = chest;
        _bench_press.muscles[_bench_press.muscles_count++].name = triceps;
        _bench_press.muscles[_bench_press.muscles_count++].name = shoulders;
        if (does_not_contain_ignored_muscle_group(user, _bench_press)) {
            user->possible_resistance_exercises[user->possible_resistance_exercises_count++] = _bench_press;
        }
    }

    //  Weighted squats
    exercise _weighted_squat = {
        .muscles_count = 0,
        .name = weighted_squat,
        .addition = 2.5,
        .base_weight = base_weight_weighted_squats(user),
        .reps = 12,
        .rep_duration = 0.1, // 6 seconds
        .is_body_weight_exercise = 0,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    if (is_equipment_available(user, barbell)) {
        _weighted_squat.muscles[_weighted_squat.muscles_count++].name = quads;
        _weighted_squat.muscles[_weighted_squat.muscles_count++].name = hamstrings;
        if (does_not_contain_ignored_muscle_group(user, _weighted_squat)) {
            user->possible_resistance_exercises[user->possible_resistance_exercises_count++] = _weighted_squat;
        }
    }

    //  Air squats
    exercise _air_squat = {
        .muscles_count = 0,
        .name = air_squat,
        .addition = 1,
        .reps = base_amount_air_squats(user),
        .rep_duration = 0.05, // 3 seconds
        .is_body_weight_exercise = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _air_squat.muscles[_air_squat.muscles_count++].name = quads;
    _air_squat.muscles[_air_squat.muscles_count++].name = hamstrings;
    if (does_not_contain_ignored_muscle_group(user, _air_squat)) {
        user->possible_resistance_exercises[user->possible_resistance_exercises_count++] = _air_squat;
    }

    //  Pushups
    exercise _pushup = {
        .muscles_count = 0,
        .name = pushup,
        .addition = 1,
        .reps = base_amount_pushups(user),
        .rep_duration = 0.05, // 3 seconds
        .is_body_weight_exercise = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _pushup.muscles[_pushup.muscles_count++].name = chest;
    _pushup.muscles[_pushup.muscles_count++].name = triceps;
    _pushup.muscles[_pushup.muscles_count++].name = shoulders;
    if (does_not_contain_ignored_muscle_group(user, _pushup)) {
        user->possible_resistance_exercises[user->possible_resistance_exercises_count++] = _pushup;
    }

    //  Elevated Pushups
    exercise _elevated_pushup = {
        .muscles_count = 0,
        .name = elevated_pushup,
        .addition = 1,
        .reps = base_amount_elevated_pushups(user),
        .rep_duration = 0.05, // 3 seconds
        .is_body_weight_exercise = 1,
        .is_aerobic = 0,
        .specific_warmup_duration = 1,
    };
    // No equipment required
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++].name = chest;
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++].name = triceps;
    _elevated_pushup.muscles[_elevated_pushup.muscles_count++].name = shoulders;
    if (does_not_contain_ignored_muscle_group(user, _elevated_pushup)) {
        user->possible_resistance_exercises[user->possible_resistance_exercises_count++] = _elevated_pushup;
    }
}
void update_possible_aerobic_exercises(user_data *user) {

    // Reset array of valid aerobic exercises
    user->possible_aerobic_exercises_count = 0;

    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise _burpees = {
        .muscles_count = 0,
        .name = burpees,
        .addition = 2,
        .reps = base_amount_burpees(user),
        .rep_duration = 0.1, // 6 seconds
        .is_body_weight_exercise = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
    };
    // No equipment required
    user->possible_aerobic_exercises[user->possible_aerobic_exercises_count++] = _burpees;

    //  find endnu en øvelse af HIIT der er mere aerobic
    exercise _jumping_jacks = {
        .muscles_count = 0,
        .name = jumping_jacks,
        .addition = 2,
        .reps = base_amount_jumping_jacks(user),
        .rep_duration = 0.025, // 1.5 seconds
        .is_body_weight_exercise = 1,
        .is_aerobic = 1,
        .specific_warmup_duration = 0,
    };
    // No equipment required
    user->possible_aerobic_exercises[user->possible_aerobic_exercises_count++] = _jumping_jacks;
}

// Global functions


void update_possible_exercises(user_data *user) {
    update_possible_resistance_exercises(user);
    update_possible_aerobic_exercises(user);

    user->possible_exercises_count = 0;

    // Add resistance exercises to the unified array
    for (int i = 0; i < user->possible_resistance_exercises_count; i++) {
        user->possible_exercises[user->possible_exercises_count++] = &user->possible_resistance_exercises[i];
    }

    // Add aerobic exercises to the unified array
    for (int i = 0; i < user->possible_aerobic_exercises_count; i++) {
        user->possible_exercises[user->possible_exercises_count++] = &user->possible_aerobic_exercises[i];
    }
}

