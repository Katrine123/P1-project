#include <stdio.h>
#include <stdlib.h>

#include "tools.h"


void upgrade_downgrade(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int *input) {
    printf("\n Let's evaluate the difficulty of your exercises: \n");
    for(int i = 0; i < sorted_count; i++) {
        char answer;
        char second_answer;
        *input = i;
        printf("Exercise %d: %s \n", i, exercise_list_sorted[i].name);
        printf("Would you like to upgrade or downgrade? (u/d) \n");
        scanf(" %c", &answer);
        //  Go to, initial call. Happens if the user types a wrong char.
        start:
        if(answer == 'u') {
            do {
                upgrade_function(exercise_list_sorted, *input);
                if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                    printf("Are these repetitions all right? %lf (y/n) \n", exercise_list_sorted[i].amount_of_reps);
                } else {
                    printf("Is this weight all right? %lf (y/n) \n", exercise_list_sorted[i].base_weight);
                }
                scanf(" %c", &second_answer);
            }
            while(second_answer == 'n');
        } else if (answer == 'd') {
            // Repeated code except it downgrades!
            int fail = 0;
            do {
                if(exercise_list_sorted[i].base_weight < 1 || exercise_list_sorted[i].amount_of_reps < 1) {
                    printf("Not possible");
                    break;
                }
                downgrade_function(exercise_list_sorted, *input);
                if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                    printf("Are these repetitions all right? %lf (y/n) \n", exercise_list_sorted[i].amount_of_reps);
                } else {
                    printf("Is this weight all right? %lf (y/n) \n", exercise_list_sorted[i].base_weight);
                }
                scanf(" %c", &second_answer);
            }
            while(second_answer == 'n');
        } else {
            printf("Type either 'u' or 'd' !");
            goto start;
        }
    }
}

void upgrade_function(exercise *exercise_list_sorted, int input) {
    if(exercise_list_sorted[input].is_body_weight_exercise == 1) {
        exercise_list_sorted[input].amount_of_reps += exercise_list_sorted[input].addition;
    } else {
        exercise_list_sorted[input].base_weight += exercise_list_sorted[input].addition;
    }


}

void downgrade_function(exercise *exercise_list_sorted, int input) {
    if(exercise_list_sorted[input].is_body_weight_exercise == 1) {
        exercise_list_sorted[input].amount_of_reps -= exercise_list_sorted[input].addition;
    } else {
        exercise_list_sorted[input].base_weight -= exercise_list_sorted[input].addition;
    }
}