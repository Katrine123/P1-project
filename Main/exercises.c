#include "exercises.h"
#include <stdio.h>
#include <math.h>
//  Test placeholders - dette kommer fra questionnaire
double body_weight = 74;
double rep_max_pushup = 30;
double rep_max_squats =

//  All exercises funktion:
int main(void) {

    //  With equipment
    //  Bench press
    check_equipment bench_press_equipment =
        {0, 1, 1, 0, 0, 0};

    exercise bench_press = {"Bench press", bench_press_equipment, 2.5, base_weight_bench_press(body_weight,rep_max_pushup)};

    //  Weighted squats
    check_equipment weighted_squats_equipment =
    {0, 1, 0, 0, 0, 0};
    exercise weighted_squats = {"Weighted squats", weighted_squats_equipment, 2.5, base_weight_weighted_squats(body_weight,rep_max_pushup)};

    print_exercise(bench_press);
}



double base_weight_bench_press(double body_weight, double rep_max_pushup) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = body_weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*rep_max_pushup)));

    //  Returning modified calculation
    /*
    if(calculation_1rm_bench_press % 2 == 0) {

    }*/
    return calculation_1rm_bench_press * rep_factor_12;
}

double base_weight_weighted_squats(double body_weight, double rep_max_pushup) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor_12 = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    double body_weight_pushup = body_weight* 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm_bench_press = (100 * body_weight_pushup)/(52.2+41.9*pow(M_E,(-0.055*rep_max_pushup)));

    //  Returning modified calculation
    /*
    if(calculation_1rm_bench_press % 2 == 0) {

    }*/
    return calculation_1rm_bench_press * rep_factor_12;
}

void print_exercise(exercise exercise) {
    //få værdierne i struct ud
    char *name = exercise.name;
    //int equipment_required = exercise.necessary_equipment;
    double addition = exercise.addition;
    double base_weight = exercise.base_weight;

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
    printf("base weight: %lf\n", base_weight);
    printf("\n");

}


/*
*
exercise* create_all_exercises(){
    //  Creating exercise for bench press.
}
 */