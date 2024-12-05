#include <stdio.h>
#include <stdlib.h>

#include "tools.h"


void upgrade_downgrade(exercise *exercise_list_sorted, int sorted_count, int *input) {
    for (int i = 0; i < sorted_count; i++) {
        input[i] = 0;
    }
    char answer;
    printf("Did you complete all assigned exercises? (y/n)");
    scanf(" %c", &answer);

    if (answer == 'y') {
        for (int i = 0; i < sorted_count; i++) {
            input[i] = 1;
        }
        //upgrade(exercise_list_sorted, input);

    } else if (answer == 'n') {
        printf("Which exercises did you complete?\n");
        // print all the exercises available to the user
        for (int i = 0; i < sorted_count; i++) {
            printf("Exercise %d: %s\n", i + 1, exercise_list_sorted[i].name);
        }
        int i = 0;
        int input_temp;
        do{
            scanf("%d", &input_temp);
            input[input_temp] = 1;
            i++;
        } while(i < sorted_count && input_temp != -1);

    }
}

exercise* upgrade_function(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int input[]) {
    exercise* sorted_exercise_list_upgrade = (exercise *)malloc(sizeof(exercise) * length_of_exercises_list);

    for (int i = 0; i < sorted_count; i++) {
        if (input[i] == 1) {
            if(user.weight == exercise_list_sorted[i].base_weight) {
                exercise_list_sorted[i].amount_of_reps += exercise_list_sorted[i].addition;
            } else {
                exercise_list_sorted[i].base_weight += exercise_list_sorted[i].addition;
            }
        }
    }
    return sorted_exercise_list_upgrade;
}