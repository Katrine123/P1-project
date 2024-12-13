#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "references.h"

void print_questionnaire() {
    printf("Age:%d\n",_questionnaire.age);
    printf("Gender: %s\n",_questionnaire.gender);
    printf("Weight: %lf\n",_questionnaire.weight);
    printf("Height: %lf\n",_questionnaire.height);
    printf("Amount of pushups: %d\n",_questionnaire.pushups);
    printf("Fitness level: %d\n",_questionnaire._fitness_level);
    printf("Time a week:\n");
    for(int i = 0;strcmp(naming_days(_questionnaire.available_training_days[i].day),"Error")!=0;i++) {
        printf("%s: %lf minutes\n",naming_days(_questionnaire.available_training_days[i].day),_questionnaire.available_training_days[i].max_duration);
    }
    int len = sizeof(_questionnaire.available_equipment)/sizeof(_questionnaire.available_equipment[0]);
    printf("Available equipment: ");
    if(len == 0) {
        printf("Nothing"); 
    }else {
        for(int i = 0; i<len;i++) {
            if(_questionnaire.available_equipment[i]==1) {
                printf("%s, ",naming_equipment(i));
            }
        }
    }
}

void update_available_training_days() {

    // Reset
    _questionnaire.available_training_days_count = 0;

    // Get available training days
    printf("What days a week do you have time? Please write numbers matching the days and enter '-1' when you're done\n");
    printf("1 = Monday\n2 = Tuesday\n3 = Wednesday\n4 = Thursday\n5 = Friday\n6 = Saturday\n7 = Sunday"); // This numbering is in accordance with the global enum day_of_the_week
    int input;
    do {

        homemade_scan(integer, &input);

        // Has day already been chosen?
        int is_input_duplicate = 0;
        for(int i = 0; i < _questionnaire.available_training_days_count; i++) {
            if (_questionnaire.available_training_days[i].day == input) {
                is_input_duplicate = 1;
                break;
            }
        }
        if (is_input_duplicate) {
            printf("This day has already been chosen. Please try another.");
            continue;
        }

        // Invalid number?
        if (input > 7 || input == 0 || input < -1 ) {
            printf("Invalid input. Please choose one of the numbers available.");
            continue;
        }

        // Done, but no days selected?
        if (input == -1 && _questionnaire.available_training_days_count == 0) {
            printf("You have not yet selected any day you can train. Please do so.");
            continue;
        }

        // Add day, if all checks pass
        _questionnaire.available_training_days[_questionnaire.available_training_days_count++].day = input;
    } while (input != -1 || _questionnaire.available_training_days_count < 7);

    // Foreach training day
    for (int i = 0; i < _questionnaire.available_training_days_count; i++) {

        printf("How much time (in minutes) do you have %s?", naming_days(_questionnaire.available_training_days[i].day));

        // Get available time
        int valid_input = 1;
        do {

            homemade_scan(long_float, &input);

            if (input > 1440) {
                printf("Invalid input. That is more minutes than there is in a day. Please try again.");
                valid_input = 0;
            } else if (input <= 0) {
                printf("Invalid input. Please enter a positive amount of time. Please try again.");
                valid_input = 0;
            }
        } while (valid_input == 0);

        _questionnaire.available_training_days[i].max_duration = input;
    }
}

void update_available_equipment() {

    // Reset
    _questionnaire.available_equipment_count = 0;

    // Ask the user if they have access to a gym.
    char access_to_gym[5];
    printf("Do you have access to a gym? (Enter 'yes' or 'no'.)");
    homemade_scan(string, access_to_gym);

    // We assume that if the user has access to a gym, they have access to all the equipment in the array.
    if (strcmp(access_to_gym, "Yes") == 0 || strcmp(access_to_gym, "yes") == 0) {
        for (int i = 0; i < all_equipment_count; i++) {
            _questionnaire.available_equipment[_questionnaire.available_equipment_count++] = all_equipment[i];
        }
    }
    // If the user does not have access to a gym, they will be asked to enter the equipment available.
    else if (strcmp(access_to_gym, "No") == 0 || strcmp(access_to_gym, "no") == 0 ) {

        // Print a list of possible pieces of equipment
        printf("Of these options what equipment do you have? Please enter the number and when you are done enter '-1'.\n");
        for (int i = 0; i < all_equipment_count; i++) {
            printf("%d = %s \n", i, naming_equipment(i));
        }

        // Loops to gather the equipment selected by the user
        int answers[all_equipment_count];
        int answers_count = 0;
        int input;
        do {
            homemade_scan(integer, &input);

            // Quit
            if (input == -1) {
                break;
            }

            // Has answer already been given?
            int is_input_duplicate = 0;
            for (int j = 0; j < answers_count; j++) {
                if (answers[j] == input) {
                    is_input_duplicate = 1;
                    break;
                }
            }
            if (is_input_duplicate) {
                printf("You have already selected this piece of equipment. Please try again.");
                continue;
            }

            // Is input invalid?
            if (input >= all_equipment_count || input < -1) {
                printf("You have entered a number that is not in the list of equipment. Please try again.");
                continue;
            }

            // Store answer, if all checks pass
            answers[answers_count++] = input;
        } while(answers_count < all_equipment_count);

        // Add answers to array of available equipment
        for (int i = 0; i < answers_count; i++) {
            _questionnaire.available_equipment[_questionnaire.available_equipment_count++] = answers[i];
        }
    }
    else {
        // Recursion
        printf("You have not entered either 'yes' or 'no'. Please try again.");
        update_available_equipment();
    }
}

void update_questionnaire() {

    // Welcome message to new users.
    printf("Welcome to your personalized fitness trainer, please answer this questionnaire to create your own personal workout routine \n");

    ////////////////////////////////////////////////////////////////////

    // Ask's about the users age.
    printf("What is your age in years?");
    homemade_scan(integer,&_questionnaire.age);

    // Checks if the user is too old. If user is above 100 years program will exit.
    if(_questionnaire.age > 100) {
        printf("You are too old to exercise!");
        exit(-1);
    }

    // Checks if the user is too young. If user is below 14 years program will exit.
    if(_questionnaire.age < 14) {
        printf("You are too young for this fitness trainer!");
        exit(-1);
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter there gender, and validate it to only accept input "male" or "female".
    do{
        printf("Are you a male or female");
        homemade_scan(string, _questionnaire.gender);
    }while(strcmp(_questionnaire.gender,"male")!=0&& strcmp(_questionnaire.gender,"female")!=0);

    ////////////////////////////////////////////////////////////////////

    // Ask's what users weight is, and loops through the input to make sure the weight is in a reasonable range (20-300 kg).
    while(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
        printf("What is your weight in kg");
        homemade_scan(long_float, &_questionnaire.weight);
        if(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
            printf("I don't think that is correct!\n");
        }
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's what users height is and loops through the input, to make sure the height is in a reasonable range (50-300 cm).
    while(_questionnaire.height < 50 || _questionnaire.height > 300) {
        printf("What is your height in cm?");
        homemade_scan(long_float, &_questionnaire.height);
        if(_questionnaire.height < 50 || _questionnaire.height > 300) {
            printf("I don't think that is correct!\n");
        }
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter how many push-ups they can perform, ensuring only non-negative numbers.
    do {
        printf("How many push-ups, can you do?");
        homemade_scan(integer, &_questionnaire.pushups);
        if(_questionnaire.pushups < 0) {
            printf("Please enter 0 or more!\n");
        }
    } while(_questionnaire.pushups < 0);

    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter how many squats they can perform, ensuring only non-negative numbers.
    do {
        printf("How many squats, can you do?");
        homemade_scan(integer, &_questionnaire.squats);
        if(_questionnaire.squats < 0) {
            printf("Please enter 0 or more!\n");
        }
    } while(_questionnaire.squats < 0);

    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter there fitness level.
    do {
        printf("What is your fitness level/experience level in a scale of 1-5?\n");

        printf("fitness rank 1 (expert): expert experience with exercising \n"
               "fitness rank 2 (proficient): advanced experience with exercising\n"
               "fitness rank 3 (competent): intermediate experience with exercising\n"
               "fitness rank 4 (advanced beginner): A little experience with exercising\n"
               "fitness rank 5 (novice): No experience with exercising\n");

        // Validates that fitness level is between 1-5.
        homemade_scan(integer, &_questionnaire._fitness_level);
        if(_questionnaire._fitness_level < expert || _questionnaire._fitness_level > novice) {
            printf("It has to be between 1-5!\n");
        }
    }while(_questionnaire._fitness_level < expert || _questionnaire._fitness_level > novice);

    ////////////////////////////////////////////////////////////////////
    //Function for getting the days the user can train
    update_available_training_days();
    ////////////////////////////////////////////////////////////////////

    update_available_equipment();
}


