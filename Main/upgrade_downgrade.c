#include <stdio.h>
#include "references.h"
void upgrade_function(int i);
void downgrade_function(int i);

void load_saved_upgrades() {
    int saved_data[possible_exercises_count];
    load_upgr_dogr(saved_data);
    for (int i = 0; i < possible_exercises_count; i++) {
        if (0<saved_data) {
            for (int j = 0; j < saved_data[i]; j++) {
                upgrade_function(i);
            }
        } else {
            for (int j = 0; j > saved_data[i] ; j--) {
                downgrade_function(i);
            }
        }
    }
}

void check_if_body_weight_exercise_and_print(int i) {
    if(possible_exercises[i].is_body_weight_exercise == 1) {
        printf("Your current amount of repetitions are: %d repetitions \n", possible_exercises[i].reps);
    } else {
        printf("Your current weight is: %lf kg \n", possible_exercises[i].base_weight);
    }
}

void upgrade_function(int i) {
    if(possible_exercises[i].is_body_weight_exercise == 1) {
        possible_exercises[i].reps += possible_exercises[i].addition;
    } else {
        possible_exercises[i].base_weight += possible_exercises[i].addition;
    }
    upgr_dogr(i, 1);
}

void downgrade_function(int i) {
    if (possible_exercises[i].is_body_weight_exercise == 1) {
        // Ensure reps cannot go below 0
        if (possible_exercises[i].reps > possible_exercises[i].addition) {
            possible_exercises[i].reps -= possible_exercises[i].addition;
        } else {
            possible_exercises[i].reps = 0;
            printf("Repetitions cannot be reduced further!\n");
        }
    } else {
        // Ensure weight cannot go below 0
        if (possible_exercises[i].base_weight > possible_exercises[i].addition) {
            possible_exercises[i].base_weight -= possible_exercises[i].addition;
        } else {
            possible_exercises[i].base_weight = 0;
            printf("Weight cannot be reduced further!\n");
        }
    }
}

void upgrade_downgrade() {
    char first_answer;
    do{
        //  first question
        printf("Would you like to change the difficulty of your exercises? (y/n)");
        scanf(" %c", &first_answer);
        if(first_answer == 'y') {
            //  Creating for loop, since we have to evaluate each exercise one-by-one.
            for(int i = 0; i < possible_exercises_count; i++) {
                printf("\nExercise %d: %s \n", i + 1, naming_exercises(possible_exercises[i].name));

                //  Printing exercise. Checking if it increments repetitions or weight
                check_if_body_weight_exercise_and_print(i);

                //  Asking second question
                char second_answer;
                do {
                    printf("Would you like to upgrade, downgrade or stay? (u/d/s) \n");
                    scanf(" %c", &second_answer);
                    //  Checking answer
                        if(second_answer == 'u') {
                            upgrade_function(i);
                            //  printing the altered exercise:
                            check_if_body_weight_exercise_and_print(i);
                            possible_exercises[i].counter_upgrade_downgrade++;
                        } else if(second_answer == 'd') {
                            downgrade_function(i);
                            //  printing the altered exercise:
                            check_if_body_weight_exercise_and_print(i);
                            possible_exercises[i].counter_upgrade_downgrade--;
                        } else if(second_answer == 's') {
                            //  printing the unaltered exercise:
                            check_if_body_weight_exercise_and_print(i);
                            break;
                            // do nothing
                        } else {
                            printf("Type either (u/d/s), please try again. ");
                        }
                } while (second_answer != 'u' || second_answer != 'd' || second_answer == 's');
            }
        } else if (first_answer == 'n') {
            // do nothing
        }
    } while (first_answer != 'y' && first_answer != 'n');
}

