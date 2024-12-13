#include <stdio.h>
#include "tools.h"


void upgrade_downgrade(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int *input) {
    char initial_answer;
    do{
        printf("\n Would you like to change the difficulty of your exercises? (y/n) \n");
        scanf(" %c", &initial_answer);

        if(initial_answer == 'y') {
            for(int i = 0; i < sorted_count; i++) {
                char answer;
                char second_answer;
                *input = i;
                printf("\nExercise %d: %s \n", i, exercise_list_sorted[i].name);

                //  Prints reps or weight based on what the exercise increments
                if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                    printf("Your current amount of repetitions are: %lf repetitions \n", exercise_list_sorted[i].amount_of_reps);
                } else {
                    printf("Your current weight is: %lf kg \n", exercise_list_sorted[i].base_weight);
                }

                do {
                    printf("Would you like to upgrade, downgrade or stay? (u/d/s) \n");
                    scanf(" %c", &answer);
                    if(answer == 'u') {
                        do {
                            upgrade_function(exercise_list_sorted, *input);
                            if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                                printf("Are these repetitions all right? %lf (y/n) \n", exercise_list_sorted[i].amount_of_reps);
                            } else {
                                printf("Is this weight all right? %lf (y/n) \n", exercise_list_sorted[i].base_weight);
                            }
                            scanf(" %c", &second_answer);
                        } while(second_answer != 'y' && second_answer != 'n');

                    } else if (answer == 'd') {
                            if(exercise_list_sorted[i].base_weight < 1 || exercise_list_sorted[i].amount_of_reps < 1) {
                                printf("Not possible");
                                break;
                            }
                            do{
                                downgrade_function(exercise_list_sorted, *input);
                                if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                                    printf("Are these repetitions all right? %lf (y/n) \n", exercise_list_sorted[i].amount_of_reps);
                                } else {
                                    printf("Is this weight all right? %lf (y/n) \n", exercise_list_sorted[i].base_weight);
                                }
                                scanf(" %c", &second_answer);
                            } while (second_answer != 'y' && second_answer != 'n');

                    } else if (answer == 's'){
                        if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                            printf("You chose to stay at: %lf repetitions \n", exercise_list_sorted[i].amount_of_reps);
                        } else {
                            printf("You chose to stay at: %lf kg \n", exercise_list_sorted[i].base_weight);
                        }
                    }
                } while (answer != 'u' && answer != 'd' && answer != 's');
            }
        }
    } while (initial_answer != 'y' && initial_answer != 'n');
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