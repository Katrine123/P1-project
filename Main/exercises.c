#include "exercises.h"

#include <iso646.h>
#include <stdio.h>
#include <math.h>
//  Test placeholders - dette kommer fra questionnaire
double body_weight = 74;
double rep_max_pushup = 90;
double rep_max_squats = 40;
int stage_of_exercise = advanced_beginner;

//  All exercises funktion:
//  Ændr til en struct array hvor den returnerer en exercise i arrayet for hver gange der skabes en
int main(void) {

    //  With equipment
    //  Bench press
    check_equipment bench_press_equipment =
        {0, 1, 1, 0, 0, 0};
    //  Ændr til at initialisere dem til

    exercise bench_press = {"Bench press", bench_press_equipment, 2.5, base_weight_bench_press(body_weight,rep_max_pushup), 12};

    print_exercise(bench_press);

    //  Weighted squats
    check_equipment weighted_squats_equipment =
    {0, 1, 0, 0, 0, 0};
    exercise weighted_squats = {"Weighted squats", weighted_squats_equipment, 2.5, base_weight_weighted_squats(body_weight,rep_max_squats), 12};

    print_exercise(weighted_squats);

    //  Air squats
    check_equipment air_squats_equipment = {1, 0, 0, 0, 0, 0, };
    exercise air_squats = {"Air squats", air_squats_equipment, 1, body_weight, base_amount_air_squats(rep_max_squats)};
    print_exercise(air_squats);

    //  Pushups
    check_equipment pushups_equipment = {1, 0, 0, 0, 0, 0, };
    exercise pushups = {"Pushups", pushups_equipment, 1, body_weight, base_amount_pushups(rep_max_pushup)};
    print_exercise(pushups);

    //  Elevated Pushups
    check_equipment elevated_pushups_equipment = {1, 0, 0, 0, 0, 0, };
    exercise elevated_pushups = {"Elevated pushups", elevated_pushups_equipment, 1, body_weight, base_amount_elevated_pushups(rep_max_pushup)};
    print_exercise(elevated_pushups);
}

//function for rounding down to the nearest number divisbl by 2.5

double round_down_to_nearest (double number, double divisor) {
    return floor(number / divisor) * divisor;
}

//  Base_weight functions:
//  Calculating base weight for bench press from pushups
double base_weight_bench_press(double body_weight, double rep_max_pushup) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = body_weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*rep_max_pushup)));
    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_bench_press * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase
    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);
    return weight_to_lift_rounded;
}

double base_weight_weighted_squats(double body_weight, double rep_max_squats) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.66 since that is the percentage of bodyweigth lifted during an air squat
    double body_weight_squats = body_weight* 0.66;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_weighted_squat = (100 * body_weight_squats)/(52.2+41.9*pow(M_E,(-0.055*rep_max_squats)));

    //  Calculating the wheight the person can lift in sets of 12
    double weight_to_lift_unrounded = calculation_1rm_weighted_squat * rep_factor_12;

    //rounding the number down to a number that is divisble by 2.5 because thats the minimun to increase

    double weight_to_lift_rounded = round_down_to_nearest(weight_to_lift_unrounded, 2.5);

    return weight_to_lift_rounded;
}

// Function if a person is over 15 reps in the harder calestenic exercise a self chosen exercise in lower body
// An alternative to this would be creating a database with 100+ exercises they can choose from
double base_amount_own_exercise_lower_body(double rep_max_squats) {
    int reps_amount_lower_body = rep_max_squats - stage_of_exercise;
    return reps_amount_lower_body;
}

// Function if a person is over 15 reps in the harder calestenic exercise a self chosen exercise in upper front body
// An alternative to this would be creating a database with 100+ exercises they can choose from
double base_amount_own_exercise_upper_front_body(double rep_max_pushups) {
    int reps_amount_upper_front_body = rep_max_pushups - stage_of_exercise;
    return reps_amount_upper_front_body;
}

// Air squats should be the exercise if the perosn can take less than 15 consecutive air squats
double base_amount_air_squats(double rep_max_squats) {
    int reps_amount_squats = rep_max_squats - stage_of_exercise;
    return reps_amount_squats;
}

//Split squats should be the printed exercise if the person can take more than 15 consecutive air squats
double base_amount_split_squats(double rep_max_squats) {
    int reps_amount_split_squats = rep_max_squats - stage_of_exercise;
    return reps_amount_split_squats;
}

//Elevated pushups should be the printed exercise if the person can take more than 15 consecutive pushups
int base_amount_elevated_pushups(double rep_max_pushup) {
        rep_max_pushup = 15;
        int reps_amount_elevated_pushups = rep_max_pushup - stage_of_exercise;
        return reps_amount_elevated_pushups;
}

//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups(double rep_max_pushup) {
        int reps_amount_pushups = rep_max_pushup - stage_of_exercise;
        return reps_amount_pushups;
}



void print_exercise(exercise exercise) {
    //få værdierne i struct ud
    char *name = exercise.name;
    //int equipment_required = exercise.necessary_equipment;
    double addition = exercise.addition;
    double base_weight = exercise.base_weight;
    int amount_of_reps = exercise.amount_of_reps;

    //print værdierne
    printf("Name: %s\n", name);
    printf("Needed equipment: \n");
    if (exercise.necessary_equipment.nothing == 1) {
        printf(" - Nothing\n");
    }
    if (exercise.necessary_equipment.barbell == 1) {
        printf(" - Barbell\n");
    }
    if (exercise.necessary_equipment.bench == 1) {
        printf(" - Bench\n");
    }
    if (exercise.necessary_equipment.pull_up_bar == 1) {
        printf(" - Pull up bar\n");
    }
    if (exercise.necessary_equipment.pull_down_machine == 1) {
        printf(" - Pull down machine\n");
    }
    if (exercise.necessary_equipment.resistance_bands == 1) {
        printf(" - Resistance bands\n");
    }
    printf("Addition: %lf\n", addition);
    if(base_weight == body_weight) {
        // do nothing
    } else {
        printf("Base weight: %lf\n", base_weight);
    }
    printf("Amount of Repititions: %d\n", amount_of_reps);
    printf("\n");

}


/*
*
exercise* create_all_exercises(){
    //  Creating exercise for bench press.
}
 */