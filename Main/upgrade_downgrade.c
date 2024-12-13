#include <stdio.h>
#include "tools.h"

void check_if_body_weight_exercise_and_print(exercise *exercise_list_sorted, int i) {
    if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
        printf("Your current amount of repetitions are: %lf repetitions \n", exercise_list_sorted[i].amount_of_reps);
    } else {
        printf("Your current weight is: %lf kg \n", exercise_list_sorted[i].base_weight);
    }
}

void upgrade_downgrade(exercise *exercise_list_sorted, int sorted_count, int *input) {
    char first_answer;
    do{
        //  first question
        printf("Would you like to change the difficulty of your exercises? (y/n)");
        scanf(" %c", &first_answer);
        if(first_answer == 'y') {
            //  Creating for loop, since we have to evaluate each exercise one-by-one.
            for(int i = 0; i < sorted_count; i++) {
                *input = i;
                printf("\nExercise %d: %s \n", i + 1, exercise_list_sorted[i].name);

                //  Printing exercise. Checking if it increments repetitions or weight
                check_if_body_weight_exercise_and_print(exercise_list_sorted, i);

                //  Asking second question
                char second_answer;
                do {
                    printf("Would you like to upgrade, downgrade or stay? (u/d/s) \n");
                    scanf(" %c", &second_answer);
                    //  Checking answer
                        if(second_answer == 'u') {
                            upgrade_function(exercise_list_sorted, *input);
                            //  printing the altered exercise:
                            check_if_body_weight_exercise_and_print(exercise_list_sorted, i);

                        } else if(second_answer == 'd') {
                            downgrade_function(exercise_list_sorted, *input);
                            //  printing the altered exercise:
                            check_if_body_weight_exercise_and_print(exercise_list_sorted, i);

                        } else if(second_answer == 's') {
                            //  printing the unaltered exercise:
                            check_if_body_weight_exercise_and_print(exercise_list_sorted, i);
                            break;
                            // do nothing
                        } else {
                            printf("Type either (u/d/s), please try again. ");
                        }
                } while(second_answer != 'u' || second_answer != 'd' || second_answer == 's');
            }
        } else if (first_answer == 'n') {
            // do nothing
        }
    } while (first_answer != 'y' && first_answer != 'n');
}

void upgrade_function(exercise *exercise_list_sorted, int input) {
    if(exercise_list_sorted[input].is_body_weight_exercise == 1) {
        exercise_list_sorted[input].amount_of_reps += exercise_list_sorted[input].addition;
    } else {
        exercise_list_sorted[input].base_weight += exercise_list_sorted[input].addition;
    }


}

void downgrade_function(exercise *exercise_list_sorted, int input) {
    if (exercise_list_sorted[input].is_body_weight_exercise == 1) {
        // Ensure reps cannot go below 0
        if (exercise_list_sorted[input].amount_of_reps > exercise_list_sorted[input].addition) {
            exercise_list_sorted[input].amount_of_reps -= exercise_list_sorted[input].addition;
        } else {
            exercise_list_sorted[input].amount_of_reps = 0;
            printf("Repetitions cannot be reduced further!\n");
        }
    } else {
        // Ensure weight cannot go below 0
        if (exercise_list_sorted[input].base_weight > exercise_list_sorted[input].addition) {
            exercise_list_sorted[input].base_weight -= exercise_list_sorted[input].addition;
        } else {
            exercise_list_sorted[input].base_weight = 0;
            printf("Weight cannot be reduced further!\n");
        }
    }
}