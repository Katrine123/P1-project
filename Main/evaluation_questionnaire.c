#include <stdio.h>
#include <stdlib.h>

#include "references.h"

// returns an int depending on answer from 1 to 5, can easily be changed with enum if thy want :3
void evaluation_questionnaire(user_data *user, int *input) {
    //  Creating a struct array in order to collect all exercises in one array
    printf("\n\nWelcome back!\n"
            "Your save file has been successfully loaded\n"
            "How has you're workout been going?\n"
            "__________________________________________________________________________\n\n"
            "Would you like to retake the questionnaire?                  ***press 1***\n\n"
            "Reevaluate the difficulty of your exercises?                 ***press 2***\n\n"
            "None of the above. I would like to move on:                  ***press 3***\n"
            "__________________________________________________________________________\n");

    int answer=0;

    int has_answer=0; //used for while loop to define when 2 break.

    while(has_answer==0) {
        has_answer++;
        homemade_scan(integer, &answer);
        switch (answer) {
            case 1:
                printf("Registered 1, questionnaire will appear!");
                //update_questionnaire();
                evaluation_questionnaire(user, input);
            break;
            case 2:
                update_possible_exercises(user);
                printf("Registered 2, proceeding to reevaluate exercises:");
            //  Retrieving sorted exercise list
                upgrade_downgrade(user, input);
                update_routine_workouts(user);
                print_routine(user);
            break;
            case 3:
                printf("Moving on..\n");
                break;
            default:;
            printf("invalid input\n ");
            has_answer--;
            break;
            //Continues while loop if answer defaults.
        }
    }

        printf("How would you like to schedule this week's workouts?\n"
            "____________________________________________________________________________________\n\n"
            "If you want your workouts on the same days and the same times as last week   ***press 1***\n"
            "If you would like to change your workout schedule                            ***press 2***\n"
            "To exit program immediately :                                                ***press 3***\n"
            "____________________________________________________________________________________\n");

        int second_answer = 0;
        int has_answer_2 = 0; //used for while loop to define when 2 break.

        while(has_answer_2 == 0) {
            has_answer_2++;
            homemade_scan(integer, &second_answer);
            switch (second_answer) {
                case 1:
                    printf("Registered 1, you chose the same days.");

                break;
                case 2:
                    printf("Registered 2, proceeding to reevaluate training days:");
                    // update_available_training_days();
                break;
                case 3:
                    printf("Exiting..");
                    exit(0);
                default:;
                printf("invalid input\n");
                has_answer_2--;
                //Continues while loop if answer defaults.
            }
        }

    save_all_data(user);
}