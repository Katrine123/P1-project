#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "references.h"

// Functions for debugging
void print_questionnaire(user_data *user) {
    printf("\nWeight: %lf",user->weight);
    printf("\nAmount of pushups: %d",user->pushups);
    printf("\nFitness level: %d",user->_fitness_level);
    printf("\nTime a week:");
    for (int i = 0; i < user->available_training_days_count; i++) {
        printf("\n%s: %lf minutes",
            naming_days(user->available_training_days[i].day),
            user->available_training_days[i].max_duration);
    }
    printf("\nAvailable equipment: ");
    for(int i = 0; i < user->available_equipment_count; i++) {
        printf("\n%s, ", naming_equipment(user->available_equipment[i]));
    }
    printf("\nIgnored muscle groups: ");
    for(int i = 0; i< user->ignored_muscle_group_names_count; i++) {
        printf("%s, ", naming_muscle_group(user->ignored_muscle_group_names[i]));
    }
}

// Helper functions
void get_multiple_answers_to_enum_list(int* answers, int* answers_count, int input_list_max,FILE* file) {

    // Reset
    *answers_count = 0;

    // Loop until input is -1 or the max amount of answers has been reached
    int input;
    do {
        printf("\nEnter answer:");
        homemade_scan(integer, &input,file);

        // Quit
        if (input == -1) {
            break;
        }

        // Has answer already been given?
        int is_input_duplicate = 0;
        for (int j = 0; j < *answers_count; j++) {
            if (answers[j] == input) {
                is_input_duplicate = 1;
                break;
            }
        }
        //Is input duplicate?
        if (is_input_duplicate) {
            printf("\nYou have already selected this item. Please try again.");
            continue;
        }

        // Is input invalid?
        if (input >= input_list_max || input < -1) {
            printf("\nYou have entered a number that is not in the list of items. Please try again.");
            continue;
        }

        // Store answer, if all checks pass
        answers[(*answers_count)++] = input;
    } while(*answers_count < input_list_max);
}

int qsort_compare_training_day_in_ascending_order(const void* a, const void* b) {
    training_day* day_a = (training_day*)a;
    training_day* day_b = (training_day*)b;
    return (day_a->day - day_b->day);
}

// Update functions
void update_available_equipment(user_data *user, FILE* file) {

    // Reset
    user->available_equipment_count = 0;

    // Ask the user if they have access to a gym.
    char access_to_gym[5];
    printf("\nDo you have access to a gym? (Enter 'yes' or 'no'.)");
    homemade_scan(string, access_to_gym,file);

    // We assume that if the user has access to a gym, they have access to all the equipment in the array.
    if (strcmp(access_to_gym, "Yes") == 0 || strcmp(access_to_gym, "yes") == 0) {
        for (int i = 0; i < equipment_enum_length; i++) {
            user->available_equipment[user->available_equipment_count++] = i;
        }
    }
    // If the user does not have access to a gym, they will be asked to enter the equipment available.
    else if (strcmp(access_to_gym, "No") == 0 || strcmp(access_to_gym, "no") == 0 ) {

        // Print a list of possible pieces of equipment
        printf("\nDo you have access to equipment? "
               "If so, enter one or more of the corresponding numbers. When you are done enter '-1'.");
        for (int i = 0; i < equipment_enum_length; i++) {
            printf("\n%d = %s", i, naming_equipment(i));
        }

        // Get answers
        int answers[equipment_enum_length];
        int answers_count = 0;
        get_multiple_answers_to_enum_list(answers, &answers_count, equipment_enum_length,file);

        // Add to available equipment
        for (int i = 0; i < answers_count; i++) {
            user->available_equipment[user->available_equipment_count++] = answers[i];
        }
    }
    else {
        // Recursion
        printf("\nYou have not entered either 'yes' or 'no'. Please try again.");
        update_available_equipment(user,file);
    }
}

void update_available_training_days(user_data *user, FILE* file) {

    // Reset
    user->available_training_days_count = 0;

    // Print a list of possible training days
    printf("\nWhat days a week do you have time? Please write numbers matching the days and enter '-1' when you are done.");
    printf("\n0 = Monday\n1 = Tuesday\n2 = Wednesday\n3 = Thursday\n4 = Friday\n5 = Saturday\n6 = Sunday");
    // NOTE: This numbering is displaced by -1 relative to the global enum day_of_the_week
    // which starts with 1 = monday, 2 = tuesday, and so on. This is because the function
    // "get_multiple_answers_to_enum_list()" only works with enums starting at 0.

    // Get answers
    int answers[7];
    int answers_count = 0;
    get_multiple_answers_to_enum_list(answers, &answers_count, 7,file);

    // No days selected?
    if (answers_count == 0) {
        printf("\nYou have to select at least one day to train. Please do so.");
        update_available_training_days(user,file); // Recursion.
        return;
    }

    // Add to training days
    for (int i = 0; i < answers_count; i++) {
        // The enum day_of_the_week start with monday = 1, tuesday = 2, wednesday = 3, and so on,
        // but our answers assume that monday = 0, tuesday = 1, wednesday = 4, and so on
        // which is why we must add +1 to each answer to make it be in accordance with the
        // numbering of the day_of_the_week enum.
        answers[i] += 1;
        user->available_training_days[user->available_training_days_count++].day = answers[i];
    }

    // Sort training days, so that Monday comes first, then Tuesday, and so on.
    qsort(user->available_training_days,
        user->available_training_days_count,
        sizeof(training_day),
        qsort_compare_training_day_in_ascending_order);

    // Get available time per each day
    // Foreach training day
    for (int i = 0; i < user->available_training_days_count; i++) {

        printf("\nHow much time (in minutes) do you have %s?", naming_days(user->available_training_days[i].day));

        // Get available time
        double input;
        int valid_input;
        do {
            valid_input = 1;
            homemade_scan(long_float, &input,file);
            printf("%lf",input);

            if (input > 1440) {
                printf("\nInvalid input. That is more minutes than there is in a day. Please try again.");
                valid_input = 0;
            } else if (input <= 0) {
                printf("\nInvalid input. Please enter a positive amount of time. Please try again.");
                valid_input = 0;
            }
        } while (valid_input == 0);

        user->available_training_days[i].max_duration = input;
    }
}
void update_ignored_muscle_groups(user_data *user,FILE* file) {

    // Reset
    user->ignored_muscle_group_names_count = 0;

    // Print a list of possible muscle groups to ignore
    printf("\nDo you wish to ignore exercises targeting a specific muscle group? "
           "If so, enter one or more of the corresponding numbers. "
           "Enter '-1' when you are done.");
    for (int i = 0; i < muscle_group_name_enum_length; i++) {
        printf("\n%d = %s", i, naming_muscle_group(i));
    }

    // Get answers
    int answers[muscle_group_name_enum_length];
    int answers_count = 0;
    get_multiple_answers_to_enum_list(answers, &answers_count, muscle_group_name_enum_length,file);

    // Add to ignored muscle groups
    for (int i = 0; i < answers_count; i++) {
        user->ignored_muscle_group_names[user->ignored_muscle_group_names_count++] = answers[i];
    }
}

void update_date(enum months* month, int *day, FILE* file) {
    //Finds the current date - Is used for streak
    printf("\nWhat is the current date? Please write the month:");
    //Is valid month?
    do {
        homemade_scan(integer,month,file);
        if(*month > 12 || *month <1) {
            printf("\nPlease enter a valid month");
        }
    }while(*month>12 || *month <1);

    printf("\nNow please enter the day");
    int right;
    //Is valid day? Based on month
    do {
        right = 1;
        homemade_scan(integer,day,file);
        if(*day <1) {
            printf("\nPlease enter a valid day");
            right = 0;
        }else if(*day>28) {
            if(*month == feb) {
                printf("\nPlease enter a valid day");
                right = 0;
            }else if(*day>30 && (*month == apr ||*month ==  jun || *month ==  sep || *month ==  nov)) {
                printf("\nPlease enter a valid day");
                right = 0;
            }else if(*day>31) {
                printf("\nPlease enter a valid day");
                right = 0;
            }
        }
    }while(right == 0);
}

void start_new_user_questionnaire(user_data *user, FILE* file) {

     // Welcome message to new users.
     printf("\nWelcome to your personalized fitness trainer, "
            "please answer this questionnaire to create your own personal workout routine.");
    update_date(&user->last_date.month,&user->last_date.day,file);
    user->streak =0;

    // Asks the user's age (our program does not work with children)
    int age;
    printf("\nWhat is your age?");
    homemade_scan(integer, &age,file);
    if (age < 18) {
        printf("\nSorry, our program is designed for adults. You are too young.");
        exit(EXIT_FAILURE);
    } else if (age > 100) {
        printf("\nSorry, but our program is not designed for people who are more than 100 years old.");
        exit(EXIT_FAILURE);
    }


    // Asks what user's weight is, and loops through the input to make sure the weight is in a reasonable range (20-300 kg).
    do  {
        printf("\nWhat is your weight in kg?");
        homemade_scan(long_float, &user->weight,file);
        if(user->weight < 20 || user->weight > 300) {
            printf("\nInvalid weight. Try again.");
        }
    } while(user->weight < 20 || user->weight > 300);

    // Asks user to enter how many push-ups they can perform, ensuring only non-negative numbers.
    do {
        printf("\nHow many push-ups can you do?");
        homemade_scan(integer, &user->pushups,file);
        if(user->pushups < 0) {
            printf("\nPlease enter 0 or more!");
        }
    } while(user->pushups < 0);

    // Asks user to enter how many squats they can perform, ensuring only non-negative numbers.
    do {
        printf("\nHow many squats can you do?");
        homemade_scan(integer, &user->squats,file);
        if(user->squats < 0) {
            printf("\nPlease enter 0 or more!");
        }
    } while(user->squats < 0);

    // Asks user to enter their fitness level.
    do {
        printf("\nWhat is your fitness level/experience level in a scale of 1-5?");
        printf("\nfitness rank 1 (expert): expert experience with exercising"
               "\nfitness rank 2 (proficient): advanced experience with exercising"
               "\nfitness rank 3 (competent): intermediate experience with exercising"
               "\nfitness rank 4 (advanced beginner): A little experience with exercising"
               "\nfitness rank 5 (novice): No experience with exercising");

        // Validates that fitness level is between 1-5.
        homemade_scan(integer, &user->_fitness_level,file);
        if(user->_fitness_level < expert || user->_fitness_level > novice) {
            printf("\nIt has to be between 1-5!\n");
        }
    } while(user->_fitness_level < expert || user->_fitness_level > novice);

    // ask about fitness goal.
    do {
        printf("\nWhat goal would you like to accomplish with your training?\n");

        printf("fitness goal 1 (Muscular endurance): Building stamina and the ability to perform a large number of repetitions. \n"
               "fitness rank 2 (Hypertrophy): Building muscle size\n"
               "fitness rank 3 (Strength): Increasing the amount of weight you can lift.\n"
               "fitness goal 4: I have not thought about this. I just want to get started! \n");

        // Validates that fitness level is between 1-5.
        homemade_scan(long_float, &user->training_goal,file);
        //  Defining bounds based on print statement. Not variable so could create issues!
        if(user->training_goal < 1 || user->training_goal > 4) {
            printf("It has to be between 1-4!\n");
        }
    } while(user->training_goal < 1 || user->training_goal > 4);

    update_available_training_days(user,file);
    update_available_equipment(user,file);
    update_ignored_muscle_groups(user,file);
    user->time_when_questionnaire_answered = time(NULL);

    // Save answers and reset upgrades save file
    save_user_data_save(user);
    reset_user_upgrades_save(user); // create user_upgrades save file
}


