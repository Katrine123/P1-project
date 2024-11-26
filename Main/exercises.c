#include "exercises.h"
#include <stdio.h>
#include <math.h>
#include "tools.h"

#define MAX_REPS 15

//  Test placeholders - dette kommer fra questionnaire
double body_weight = 74;
double rep_max_pushup = 90;
double rep_max_squats = 40;
int stage_of_exercise = novice;

int check_eq[length_of_equipment_enum - 1] = {barbell, bench, pull_up_bar, pull_down_machine, resistance_bands};


//  All exercises funktion:
//  Ændr til en struct array hvor den returnerer en exercise i arrayet for hver gange der skabes en
int main(void) {
    //  With equipment
    //  Bench press
    exercise bench_press = {"Bench press", {0, 1, 1, 0, 0}, 2.5, base_weight_bench_press(body_weight,rep_max_pushup), 12};

    //  Weighted squats
    exercise weighted_squats = {"Weighted squats", {0, 1, 0, 0, 0}, 2.5, base_weight_weighted_squats(body_weight,rep_max_squats), 12};

    //  Air squats
    exercise air_squats = {"Air squats", {0, 0, 0, 0, 0}, 1, body_weight, base_amount_air_squats(rep_max_squats)};

    //  Pushups
    exercise pushups = {"Pushups", {0, 0, 0, 0, 0}, 1, body_weight, base_amount_pushups(rep_max_pushup)};

    //  Elevated Pushups
    exercise elevated_pushups = {"Elevated pushups", {0, 0, 0, 0, 0}, 1, body_weight, base_amount_elevated_pushups(rep_max_pushup)};

    //  HIIT
    //  Burpees
    //  Potential lowest bound is 5 reps pr. set. The exercise is more suitable to an increase in additions, therefore 2 instead of 1.
    exercise burpees = {"Burpees", {0, 0, 0, 0, 0}, 2, body_weight, base_amount_burpees(MAX_REPS)};

    //  find endnu en øvelse af HIIT der er mere aerobic
    exercise jumping_jacks = {"Jumping jacks", {0, 0, 0, 0, 0}, 2, body_weight, base_amount_jumping_jacks(MAX_REPS)};

    //  Create array
    exercise exercises_list[] = {bench_press, weighted_squats, air_squats, pushups, elevated_pushups, burpees, jumping_jacks};
    print_exercise(exercises_list);
}

///function for rounding down to the nearest number divisbl by 2.5
double round_down_to_nearest (double number, double divisor) {
    return floor(number / divisor) * divisor;
}

//  Base_weight functions:
///  Calculating base weight for bench press from pushups
double base_weight_bench_press(double body_weight, double rep_max_pushup) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = body_weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*rep_max_pushup)));
    //  Calculating the height the person can lift in sets of 12
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
        rep_max_pushup = MAX_REPS;
        int reps_amount_elevated_pushups = rep_max_pushup - stage_of_exercise;
        return reps_amount_elevated_pushups;
}

//Pushups should be the printed exercise if the person can tak less than 15 consecutive pushups
int base_amount_pushups(double rep_max_pushup) {
        int reps_amount_pushups = rep_max_pushup - stage_of_exercise;
        return reps_amount_pushups;
}

double base_amount_burpees(double rep_max_squats) {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    int reps_amount_burpees = MAX_REPS - (stage_of_exercise*2);
    return reps_amount_burpees;
}

double base_amount_jumping_jacks(double rep_max_squats) {
    /*  We are taking into account that this exercise is more difficult than others
     *  Level of exercise should be amplified by a factor of 2
     */
    int reps_amount_burpees = MAX_REPS - (stage_of_exercise*2);
    return reps_amount_burpees;
}


void print_exercise(exercise exercises_list[]) {
    for(int i = 0; i < length_of_exercises_list; i++) {
        //få værdierne i struct ud
        char *name = exercises_list[i].name;
        //int equipment_required = exercise.necessary_equipment;
        double addition = exercises_list[i].addition;
        double base_weight = exercises_list[i].base_weight;
        int amount_of_reps = exercises_list[i].amount_of_reps;

        //print værdierne
        printf("Name: %s\n", name);
        printf("Needed equipment: \n");
        if (exercises_list[i].check_eq[0] == 1) {
            printf(" - Barbell\n");
        }
        if (exercises_list[i].check_eq[1] == 1) {
            printf(" - Bench\n");
        }
        if (exercises_list[i].check_eq[2] == 1) {
            printf(" - Pull up bar\n");
        }
        if (exercises_list[i].check_eq[3] == 1) {
            printf(" - Pull down machine\n");
        }
        if (exercises_list[i].check_eq[4] == 1) {
            printf(" - Resistance bands\n");
        }
        printf("Addition: %.2lf\n", addition);
        if(base_weight == body_weight) {
            // do nothing
        } else {
            printf("Base weight: %.2lf\n", base_weight);
        }
        printf("Amount of Repititions: %d\n", amount_of_reps);
        printf("\n");
    }
}


/*
*
exercise* create_all_exercises(){
    //  Creating exercise for bench press.
}
 */