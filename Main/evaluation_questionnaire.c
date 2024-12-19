#include <stdio.h>
#include <stdlib.h>

#include "references.h"


void start_evaluation_questionnaire(user_data *user,FILE* file) {
    // Continues looping until the user quits the program
    while(1) {
        printf("\n\n\nWhat would you like to do?"
        "\n_______________________________________________________________________________"
        "\nWould you like to retake the questionnaire?                      ***press 1***"
        "\nWould yuu like to reevaluate the difficulty of your exercises?   ***press 2***"
        "\nWould you like to change your workout schedule?                  ***press 3***"
        "\nWould you like to print your fitness routine?                    ***press 4***"
        "\nWould you like to quit the program?                              ***press 5***"
        "\n_______________________________________________________________________________");
        int answer = 0;
        homemade_scan(integer, &answer,file);
        switch (answer) {
            case 1: // Retake questionnaire
                start_new_user_questionnaire(user,file);
                break;
            case 2: // Upgrade/downgrade
                start_upgrade_downgrade_questionnaire(user);
                break;
            case 3: // Update schedule (training days)
                update_available_training_days(user,file);
                save_user_data_save(user); // because update_available_training_days does not save by itself.
                break;
            case 4: // Print routine
                update_possible_exercises(user);
                load_saved_upgrades_onto_possible_exercises(user);
                update_routine_workouts(user);
                print_routine(user);
                break;
            case 5: // Exit program
                printf("Exiting program...");
                exit(EXIT_SUCCESS);
            default: // Continues while loop if answer defaults.
                printf("Invalid input. Please try again.\n");
                break;
        }
    }
}