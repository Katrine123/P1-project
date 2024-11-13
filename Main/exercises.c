#include "exercises.h"
#include <stdio.h>
#include <math.h>
//  Test placeholders - dette kommer fra questionnaire
double body_weight = 74;
double rep_max_pushup = 30;

//  All exercises funktion:
int main(void) {

    //  With equipment
    equipment_2 bench_press_equipment;
    bench_press_equipment.bench = 1;
    bench_press_equipment.barbell = 1;

    exercise bench_press = {"Bench press", bench_press_equipment, 2.5, base_weight(body_weight,rep_max_pushup)};
    exercise weighted_squats = {"Weighted squats", barbell, 2.5, base_weight(body_weight,rep_max_pushup)};
    exercise lateral_pulldown = {"Bench press", barbell, 2.5, base_weight(body_weight,rep_max_pushup)};
    //  Without equipment
    exercise push_ups = {"Bench press", barbell, 2.5, base_weight(body_weight,rep_max_pushup)};
    exercise squats = {"Bench press", barbell, 2.5, base_weight(body_weight,rep_max_pushup)};
    //  What should be an unweighted exercise for the back?
    exercise back_push_ups = {"Bench press", barbell, 2.5, base_weight(body_weight,rep_max_pushup)};

    print_exercise(bench_press);
}



double base_weight(double body_weight, double rep_max_pushup) {
    //  Multiplying by a factor so amount of weight based on 12 reps is found
    double rep_factor = 0.71;
    //  Multiply by 0.65 since that is the percentage of bodyweigth lifted during a pushup
    body_weight *= 0.65;
    //  Mayhews calculation for 1rm:
    double calculation_1rm = (100 * body_weight)/(52.2+41.9*pow(M_E,(-0.055*rep_max_pushup)));

    //  Returning modified calculation
    if(calculation_1rm % 2 == 0) {

    }
    return calculation_1rm * rep_factor;
}

void print_exercise(exercise exercise) {
    //få værdierne i struct ud
    char *name = exercise.name;
    int needed_equipment = exercise.needed_equipment;
    double addition = exercise.addition;
    double base_weight = exercise.base_weight;

    //print værdierne
    printf("Name: %s\n", name);
    printf("Needed equipment: %d\n", needed_equipment);
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