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

void upgrade_downgrade(user_data *user) {
    load_saved_upgrades(user);
    char first_answer;
    do{
        //  first question
        printf("Would you like to change the difficulty of your exercises? (y/n)");
        scanf(" %c", &first_answer);
        if(first_answer == 'y') {
            //  Creating for loop, since we have to evaluate each exercise one-by-one.
            printf("\n fuck: %d ", user->possible_exercises_count);
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
                            upgr_dogr(user, i, 1);
                        } else if(second_answer == 'd') {
                            downgrade_function(user, i);
                            //  printing the altered exercise:
                            check_if_body_weight_exercise_and_print(user, i);
                            user->possible_exercises[i]->counter_upgrade_downgrade--;
                            upgr_dogr(user, i, -1);
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
        } else if (first_answer == 'n') {
            // do nothing
        }
    } while (first_answer != 'y' && first_answer != 'n');
}

void load_saved_upgrades(user_data *user) {
    int saved_data[user->possible_exercises_count];
    load_upgr_dogr(user, saved_data);
    for (int i = 0; i < user->possible_exercises_count-1; i++) {
        int upgrade_counter = 0; 
        if (saved_data[i]>0) {
            for (int j = 0; j < saved_data[i]-100; j++) {
                upgrade_function(user, i);
                upgrade_counter++;
            }
        }
        if (saved_data[i]<0) {
            for (int j = 0; j > saved_data[i]-100; j--) {
                downgrade_function(user, i);
                upgrade_counter--;
            }
        }
        printf("exercise %d was upgraded %d\n", i, upgrade_counter);
    }
}

