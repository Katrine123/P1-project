#include <stdio.h>
#include <stdlib.h>

#include "tools.h"


void upgrade_downgrade(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int *input) {
    for (int i = 0; i < sorted_count; i++) {
        input[i] = 0;
    }
    char answer;
    printf("Did you complete all assigned exercises? (y/n)");
    scanf(" %c", &answer);

    if (answer == 'y') {
        for (int i = 0; i < sorted_count; i++) {
            input[i] = 1;
            //  Call upgrade function
        }
        upgrade_function(exercise_list_sorted,user,sorted_count,input);

    } else if (answer == 'n') {
        printf("Which exercises did you complete?\n");
        // print all the exercises available to the user
        for (int i = 0; i < sorted_count; i++) {
            //  Exercises are listed as 0-6, if they were listed from 1-7 it would provide issues..
            printf("Exercise %d: %s\n", i, exercise_list_sorted[i].name);
        }
        int i = 0;
        int input_temp;
        do{
            //TAGER IKKE HØJDE FOR -1 ELLER MIN MAX

            scanf("%d", &input_temp);
            if(input_temp < -1 || input_temp > sorted_count) {
                printf("Please type values between 0 and %d. Unless you are done, then type -1. Enter values again! \n", sorted_count);
                //  If condition is met restart the loop:
                continue;
            }
            if(input_temp!=-1) {
                //  input_temp - 1
                input[input_temp] = 1;
                i++;
            }

        } while (input_temp != -1);
        printf("TEST");
        upgrade_function(exercise_list_sorted,user,sorted_count,input);
    }
}

void upgrade_function(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int input[]) {
    printf("TEST3");
    for (int i = 0; i < sorted_count; i++) {
        if (input[i] == 1) {
            //  What if the user weight is equal to bench press weight?
                //  This has to be for body_weight_exercises
            if(exercise_list_sorted[i].is_body_weight_exercise == 1) {
                exercise_list_sorted[i].amount_of_reps += exercise_list_sorted[i].addition;
            } else {
                exercise_list_sorted[i].base_weight += exercise_list_sorted[i].addition;
            }
        }
    }
}