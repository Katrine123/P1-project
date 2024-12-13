#include "tools.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_REPS 15

enum training_goal_e { MUSCULAR_ENDURANCE = 1, HYPERTROPHY = 2, STRENGTH = 3, I_DONT_KNOW = 4 };
int check_eq[length_of_equipment_enum] = {barbell, bench, pull_up_bar, pull_down_machine, resistance_bands};
int check_muscle_groups[length_of_muscle_groups_list] = {chest, triceps, shoulders, hamstrings, quads};

int training_goal_reps(questionnaire user) {
    int training_goal_reps = 0;
    if(user.training_goal == MUSCULAR_ENDURANCE) {
        training_goal_reps = 15;
    } else if(user.training_goal == HYPERTROPHY || user.training_goal == I_DONT_KNOW) {
        training_goal_reps = 12;
    } else {
        training_goal_reps = 5;
    }
    return training_goal_reps;
}

double training_goal_converter(questionnaire user) {
    double training_goal_converter = 0;
    if(user.training_goal == MUSCULAR_ENDURANCE) {
        training_goal_converter = 0.65;
    } else if(user.training_goal == HYPERTROPHY || user.training_goal == I_DONT_KNOW) {
        training_goal_converter = 0.75;
    } else {
        training_goal_converter = 0.85;
    }
    return training_goal_converter;
}

double fitness_level(questionnaire user) {
    double fitness_level = 0;
    if (user.fitness_level == novice) {
        fitness_level = 0.5;
    } else if (user.fitness_level == advanced_beginner) {
        fitness_level = 0.6;
    } else if (user.fitness_level == competent) {
        fitness_level = 0.7;
    } else if (user.fitness_level == proficient) {
        fitness_level = 0.8;
    } else {
        fitness_level = 0.9;
    }
    return fitness_level;
}

void resistance_exercises_list(exercise* exercise_list, questionnaire user) {
    //  Bench press
    exercise bench_press = {"Bench press", {1, 1, 0, 0, 0}, 2.5, base_weight_bench_press(user), training_goal_reps(user), 0, NULL, {1, 1, 1, 0, 0}};
    exercise_list[0] = bench_press;

    //  Weighted squats
    exercise weighted_squats = {"Weighted squats", {1, 0, 0, 0, 0}, 2.5, base_weight_weighted_squats(user), training_goal_reps(user), 0, NULL, {0, 0, 0, 1, 1}};
    exercise_list[1] = weighted_squats;

    // Split squats (harder version of squats)
    exercise split_squats = {"Split squats", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_split_squats(user), 1, NULL, {0, 0, 0, 1, 1}};
    exercise_list[2] = split_squats;

    // Air squats
    exercise air_squats = {"Air squats", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_air_squats(user), 1, &exercise_list[2], {0, 0, 0, 1, 1}};
    exercise_list[3] = air_squats;

    // Elevated pushups (harder version of pushups)
    exercise elevated_pushups = {"Elevated pushups", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_elevated_pushups(user), 1, NULL, {1, 1, 1, 0, 0}};
    exercise_list[4] = elevated_pushups;

    // Pushups
    exercise pushups = {"Pushups", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_pushups(user), 1, &exercise_list[4], {1, 1, 1, 0, 0}};
    exercise_list[5] = pushups;

}


void aerobic_exercises_list(exercise* exercise_list, questionnaire user){
    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise burpees = {"Burpees", {0, 0, 0, 0, 0}, 2, user.weight, base_amount_burpees(user), 1, NULL};
    exercise_list[6] = burpees;

    //  find endnu en Ã¸velse af HIIT der er mere aerobic
    exercise jumping_jacks = {"Jumping jacks", {0, 0, 0, 0, 0}, 2, user.weight, base_amount_jumping_jacks(user), 1, NULL};
    exercise_list[7] = jumping_jacks;
    //  Create array
    //  Return this array !
    //exercise exercises_list[length_of_exercises_list] = {bench_press, weighted_squats, air_squats, pushups, elevated_pushups, burpees, jumping_jacks};
    //print_exercise(exercises_list);
    //return exercises_list[length_of_exercises_list];
}

///function for rounding down to the nearest number divisbl by 2.5
double round_down_to_nearest (double number, double divisor) {
    return floor(number / divisor) * divisor;
}

int base_amount_calculation(questionnaire user, int user_1rm_exercise) {
    return (int)user_1rm_exercise * fitness_level(user);
}

//  Base_weight functions:
///  Calculating base weight for bench press from pushups
double base_weight_bench_press(questionnaire user) {
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = user.weight * 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*user.pushups)));
    //  Calculating the height the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_bench_press * training_goal_converter(user);
    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}

double base_weight_weighted_squats(questionnaire user) {
    //  Multiply by 0.66 since that is the percentage of bodyweigth lifted during an air squat
    double body_weight_squats = user.weight * 0.66;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_weighted_squat = (100 * body_weight_squats)/(52.2+41.9*pow(M_E,(-0.055*user.squats)));

    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_weighted_squat * training_goal_converter(user);

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}

// Air squats should be the exercise if the perosn can take less than 15 consecutive air squats
int base_amount_air_squats(questionnaire user) {
    //  The calculation takes into account the users 1rm, fitness_level and training goal when calculating reps.
    return base_amount_calculation(user, user.squats);
}

//Split squats should be the printed exercise if the person can take more than 15 consecutive air squats
int base_amount_split_squats(questionnaire user) {
    return base_amount_calculation(user, user.squats);
}

//Elevated pushups should be the printed exercise if the person can take more than 15 consecutive pushups
int base_amount_elevated_pushups(questionnaire user) {
        return base_amount_calculation(user, user.pushups);
}

//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups(questionnaire user) {
        return base_amount_calculation(user, user.pushups);
}

int base_amount_burpees(questionnaire user) {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    return base_amount_calculation(user, (user.pushups+user.squats));
}

int base_amount_jumping_jacks(questionnaire user) {
    return base_amount_calculation(user, user.squats);
}

// Print function to display the viable exercises
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user) {
    printf("Viable Exercises:\n");
    for (int i = 0; i < count; i++) {
        printf("\n_____________________________\n");
        printf("Exercise %d:\n", i);
        printf("Name: %s\n", sorted_exercise_list[i].name);
        printf("Addition: %.2lf\n", sorted_exercise_list[i].addition);
        printf("Harder exercise: %s\n", sorted_exercise_list[i].harder_version->name);
        if(sorted_exercise_list[i].base_weight != user.weight) {
            printf("Base weight: %.2lf\n", sorted_exercise_list[i].base_weight);
        }
        printf("Reps: %.2lf\n", sorted_exercise_list[i].amount_of_reps);
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
