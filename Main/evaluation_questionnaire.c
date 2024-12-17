#include <stdio.h>
#include <stdlib.h>

#include "references.h"

// returns an int depending on answer from 1 to 5, can easily be changed with enum if thy want :3
void evaluation_questionnaire(user_data *user) {

    //  Creating a struct array in order to collect all exercises in one array
    int answer=0;
    while(1) { // Continues looping until the user quits the program
        printf("\n\nWhat would you like to do?"
        "\n_______________________________________________________________________________"
        "\nWould you like to retake the questionnaire?                      ***press 1***"
        "\nWould yuu like to reevaluate the difficulty of your exercises?   ***press 2***"
        "\nWould you like to change your workout schedule?                  ***press 3***"
        "\nWould you like to print your fitness routine?                    ***press 4***"
        "\nWould you like to quit the program?                              ***press 5***"
        "\n_______________________________________________________________________________");
        homemade_scan(integer, &answer);
        switch (answer) {
            case 1: // Retake questionnaire
                answer_new_user_questionnaire(user);
                break;
            case 2: // Upgrade/downgrade
                start_upgrade_downgrade_questionnaire(user);
                break;
            case 3: // Update schedule (training days)
                update_available_training_days(user);
                save_user_data(user);
                break;
            case 4: // Print routine
                update_possible_exercises(user);
                load_saved_upgrades_onto_possible_exercises(user);
                update_routine_workouts(user);
                print_routine(user);
                break;
            case 5: // Exit program
                printf("Exiting..");
                exit(EXIT_SUCCESS);
            default: // Continues while loop if answer defaults.
                printf("invalid input\n");
                break;
        }
    }
}