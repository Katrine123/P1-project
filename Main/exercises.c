#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "references.h"

#define MAX_REPS 15

int check_eq[length_of_equipment_enum] = {barbell, bench, pull_up_bar, pull_down_machine, resistance_bands};

//  All exercises funktion:
void resistance_exercises_list(exercise* exercise_list, questionnaire user)
{
    //  With equipment
    //  Bench press
    exercise bench_press = {"Bench press", {1, 1, 0, 0, 0}, 2.5, base_weight_bench_press(user), 12, 0};
    exercise_list[0] = bench_press;

    //  Weighted squats
    exercise weighted_squats = {"Weighted squats", {1, 0, 0, 0, 0}, 2.5, base_weight_weighted_squats(user), 12, 0};
    exercise_list[1] = weighted_squats;

    //  Air squats
    exercise air_squats = {"Air squats", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_air_squats(user), 1};
    exercise_list[2] = air_squats;

    //  Pushups
    exercise pushups = {"Pushups", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_pushups(user), 1};
    exercise_list[3] = pushups;

    //  Elevated Pushups
    exercise elevated_pushups = {"Elevated pushups", {0, 0, 0, 0, 0}, 1, user.weight, base_amount_elevated_pushups(user), 1};
    exercise_list[4] = elevated_pushups;
}


void aerobic_exercises_list(exercise* exercise_list, questionnaire user){
    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise burpees = {"Burpees", {0, 0, 0, 0, 0}, 2, user.weight, base_amount_burpees(user), 1};
    exercise_list[5] = burpees;

    //  find endnu en øvelse af HIIT der er mere aerobic
    exercise jumping_jacks = {"Jumping jacks", {0, 0, 0, 0, 0}, 2, user.weight, base_amount_jumping_jacks(user), 1};
    exercise_list[6] = jumping_jacks;
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

//  Base_weight functions:
///  Calculating base weight for bench press from pushups
double base_weight_bench_press(questionnaire user) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = user.weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*user.pushups)));
    //  Calculating the height the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_bench_press * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}

double base_weight_weighted_squats(questionnaire user) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.66 since that is the percentage of bodyweigth lifted during an air squat
    double body_weight_squats = user.weight* 0.66;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_weighted_squat = (100 * body_weight_squats)/(52.2+41.9*pow(M_E,(-0.055*user.squats)));

    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_weighted_squat * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}

// Air squats should be the exercise if the perosn can take less than 15 consecutive air squats
int base_amount_air_squats(questionnaire user) {
    int reps_amount_squats = MAX_REPS - user.fitness_level;
    return reps_amount_squats;
}

//Split squats should be the printed exercise if the person can take more than 15 consecutive air squats
int base_amount_split_squats(questionnaire user) {
    int reps_amount_split_squats = MAX_REPS - user.fitness_level;
    return reps_amount_split_squats;
}

//Elevated pushups should be the printed exercise if the person can take more than 15 consecutive pushups
int base_amount_elevated_pushups(questionnaire user) {
        int reps_amount_elevated_pushups = MAX_REPS - user.fitness_level;
        return reps_amount_elevated_pushups;
}

//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups(questionnaire user) {
        int reps_amount_pushups = MAX_REPS - user.fitness_level;
        return reps_amount_pushups;
}

int base_amount_burpees(questionnaire user) {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    int reps_amount_burpees = MAX_REPS - (user.fitness_level*2);
    return reps_amount_burpees;
}

int base_amount_jumping_jacks(questionnaire user) {
    int reps_amount_jumping_jacks = MAX_REPS - (user.fitness_level);
    return reps_amount_jumping_jacks;
}

// Print function to display the viable exercises
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user, exercise exercises_list[]) {
    printf("Viable Exercises:\n");
    printf("SE HER: %d", count);
    for (int i = 0; i < count; i++) {
        printf("\n_____________________________\n");
        printf("Exercise %d:\n", i + 1);
        printf("Name: %s\n", sorted_exercise_list[i].name);
        printf("Addition: %.2lf\n", sorted_exercise_list[i].addition);
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
