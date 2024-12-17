#include <stdio.h>
#include "references.h"

void check_if_body_weight_exercise_and_print(user_data *user, int i) {
    if(user->possible_exercises[i]->is_body_weight_exercise == 1) {
        printf("Your current amount of repetitions are: %d repetitions \n",user->possible_exercises[i]->reps);
    } else {
        printf("Your current weight is: %lf kg \n", user->possible_exercises[i]->base_weight);
    }
}
void upgrade_function(user_data *user, int input) {
    if(user->possible_exercises[input]->is_body_weight_exercise == 1) {
        user->possible_exercises[input]->reps += user->possible_exercises[input]->addition;
    } else {
        user->possible_exercises[input]->base_weight += user->possible_exercises[input]->addition;
    }
}
void downgrade_function(user_data *user, int input) {
    if (user->possible_exercises[input]->is_body_weight_exercise == 1) {
        // Ensure reps cannot go below 0
        if (user->possible_exercises[input]->reps > user->possible_exercises[input]->addition) {
            user->possible_exercises[input]->reps -= user->possible_exercises[input]->addition;
        } else {
            user->possible_exercises[input]->reps = 0;
            printf("Repetitions cannot be reduced further!\n");
        }
    } else {
        // Ensure weight cannot go below 0
        if (user->possible_exercises[input]->base_weight > user->possible_exercises[input]->addition) {
            user->possible_exercises[input]->base_weight -= user->possible_exercises[input]->addition;
        } else {
            user->possible_exercises[input]->base_weight = 0;
            printf("Weight cannot be reduced further!\n");
        }
    }
}

void upgrade_or_downgrade_exercise(user_data *user, int exercise_index, int addition_to_upgrade) {
    int temp_save[user->possible_exercises_count];
    get_data_from_user_upgrades_save(user, temp_save);
    temp_save[exercise_index] = temp_save[exercise_index] + addition_to_upgrade;
    save_user_upgrades_save(user, temp_save);
}

void start_upgrade_downgrade_questionnaire(user_data *user) {
    update_possible_exercises(user); // because possible exercises are used in the upgrade/downgrade function
    load_saved_upgrades_onto_possible_exercises(user);
    //  Creating for loop, since we have to evaluate each exercise one-by-one.
    for(int i = 0; i < user->possible_exercises_count; i++) {
        printf("\nExercise %d: %s \n", i + 1, naming_exercises(user->possible_exercises[i]->name));

        //  Printing exercise. Checking if it increments repetitions or weight
        check_if_body_weight_exercise_and_print(user, i);

        //  Asking second question
        char second_answer;
        do {
            printf("Would you like to upgrade, downgrade or stay? (u/d/s) \n");
            scanf(" %c", &second_answer);
            //  Checking answer
                if(second_answer == 'u') {
                    upgrade_function(user, i);
                    //  printing the altered exercise:
                    check_if_body_weight_exercise_and_print(user, i);
                    user->possible_exercises[i]->counter_upgrade_downgrade++;
                    upgrade_or_downgrade_exercise(user, i, 1);
                } else if(second_answer == 'd') {
                    downgrade_function(user, i);
                    //  printing the altered exercise:
                    check_if_body_weight_exercise_and_print(user, i);
                    user->possible_exercises[i]->counter_upgrade_downgrade--;
                    upgrade_or_downgrade_exercise(user, i, -1);
                } else if(second_answer == 's') {
                    //  printing the unaltered exercise:
                    check_if_body_weight_exercise_and_print(user, i);
                    break;
                    // do nothing
                } else {
                    printf("Type either (u/d/s), please try again. ");
                }
        } while (second_answer != 'u' || second_answer != 'd' || second_answer == 's');
    }
}

void load_saved_upgrades_onto_possible_exercises(user_data *user) {
    int saved_data[user->possible_exercises_count];
    get_data_from_user_upgrades_save(user, saved_data);
    for (int i = 0; i < user->possible_exercises_count-1; i++) {
        if (saved_data[i]>0) {
            for (int j = 0; j < saved_data[i]; j++) {
                upgrade_function(user, i);
            }
        }
        if (saved_data[i]<0) {
            for (int j = 0; j > saved_data[i]; j--) {
                downgrade_function(user, i);
            }
        }
    }
}

