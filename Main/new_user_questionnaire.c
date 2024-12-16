#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "references.h"

//TODO: What is function for? Should it be deleted?
void print_questionnaire() {
    printf("\nWeight: %lf",_questionnaire.weight);
    printf("\nAmount of pushups: %d",_questionnaire.pushups);
    printf("\nFitness level: %d",_questionnaire._fitness_level);
    printf("\nTime a week:");
    for (int i = 0; i < _questionnaire.available_training_days_count; i++) {
        printf("\n%s: %lf minutes",
            naming_days(_questionnaire.available_training_days[i].day),
            _questionnaire.available_training_days[i].max_duration);
    }
    printf("\nAvailable equipment: ");
    for(int i = 0; i < _questionnaire.available_equipment_count; i++) {
        printf("\n%s, ", naming_equipment(_questionnaire.available_equipment[i]));
    }
    printf("\nIgnored muscle groups: ");
    for(int i = 0; i<_questionnaire.ignored_muscle_group_names_count;i++) {
        printf("%s, ", naming_muscle_group(_questionnaire.ignored_muscle_group_names[i]));
    }
}

// Helper functions
void get_multiple_answers_to_enum_list(int* answers, int* answers_count, int input_list_max) {

    // Reset
    *answers_count = 0;

    // Loop until input is -1 or the max amount of answers has been reached
    int input;
    do {
        printf("\nEnter answer:");
        homemade_scan(integer, &input);

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
int qsort_compare_ascending_order(const void* a, const void* b) {

    training_day* day_a = (training_day*)a;
    training_day* day_b = (training_day*)b;
    return (day_a->day - day_b->day);
}

// Update functions
void update_available_training_days() {

    // Reset
    _questionnaire.available_training_days_count = 0;

    // Print a list of possible training days
    printf("\nWhat days a week do you have time? Please write numbers matching the days and enter '-1' when you are done.");
    printf("\n0 = Monday\n1 = Tuesday\n2 = Wednesday\n3 = Thursday\n4 = Friday\n5 = Saturday\n6 = Sunday");
    // NOTE: This numbering is displaced by -1 relative to the global enum day_of_the_week
    // which starts with 1 = monday, 2 = tuesday, and so on. This is because the function
    // "get_multiple_answers_to_enum_list()" only works with enums starting at 0.

    // Get answers
    int answers[7];
    int answers_count = 333;
    get_multiple_answers_to_enum_list(answers, &answers_count, 7);

    // No days selected?
    if (answers_count == 0) {
        printf("\nYou have to select at least one day to train. Please do so.");
        update_available_training_days(); // Recursion.
        return;
    }

    // Add to training days
    for (int i = 0; i < answers_count; i++) {
        // The enum day_of_the_week start with monday = 1, tuesday = 2, wednesday = 3, and so on,
        // but our answers assume that monday = 0, tuesday = 1, wednesday = 4, and so on
        // which is why we must add +1 to each answer to make it be in accordance with the
        // numbering of the day_of_the_week enum.
        answers[i] += 1;
        _questionnaire.available_training_days[_questionnaire.available_training_days_count++].day = answers[i];
    }

    // Sort training days, so that Monday comes first, then Tuesday, and so on.
    qsort(_questionnaire.available_training_days,
        _questionnaire.available_training_days_count,
        sizeof(training_day),
        qsort_compare_ascending_order);

    // Get available time per each day
    // Foreach training day
    for (int i = 0; i < _questionnaire.available_training_days_count; i++) {

        printf("\nHow much time (in minutes) do you have %s?", naming_days(_questionnaire.available_training_days[i].day));

        // Get available time
        double input;
        int valid_input = 1;
        do {
            homemade_scan(long_float, &input);

            if (input > 1440) {
                printf("\nInvalid input. That is more minutes than there is in a day. Please try again.");
                valid_input = 0;
            } else if (input <= 0) {
                printf("\nInvalid input. Please enter a positive amount of time. Please try again.");
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
    printf("\nDo you have access to a gym? (Enter 'yes' or 'no'.)");
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
        printf("\nDo you have access to equipment? "
               "If so, enter one or more of the corresponding numbers. When you are done enter '-1'.");
        for (int i = 0; i < all_equipment_count; i++) {
            printf("\n%d = %s", i, naming_equipment(i));
        }

        // Get answers
        int answers[all_equipment_count];
        int answers_count = 0;
        get_multiple_answers_to_enum_list(answers, &answers_count, all_equipment_count);

        // Add to available equipment
        for (int i = 0; i < answers_count; i++) {
            _questionnaire.available_equipment[_questionnaire.available_equipment_count++] = answers[i];
        }
    }
    else {
        // Recursion
        printf("\nYou have not entered either 'yes' or 'no'. Please try again.");
        update_available_equipment();
    }
}
void update_ignored_muscle_groups() {

    // Reset
    _questionnaire.ignored_muscle_group_names_count = 0;

    // Print a list of possible muscle groups to ignore
    printf("\nDo you wish to ignore exercises targeting a specific muscle group? "
           "If so, enter one or more of the corresponding numbers. "
           "Enter '-1' when you are done.");
    for (int i = 0; i < all_muscle_names_count; i++) {
        printf("\n%d = %s", i, naming_muscle_group(i));
    }

    // Get answers
    int answers[all_muscle_names_count];
    int answers_count = 0;
    get_multiple_answers_to_enum_list(answers, &answers_count, all_muscle_names_count);

    // Add to ignored muscle groups
    for (int i = 0; i < answers_count; i++) {
        _questionnaire.ignored_muscle_group_names[_questionnaire.ignored_muscle_group_names_count++] = answers[i];
    }
}
void update_questionnaire() {

     // Welcome message to new users.
     printf("\nWelcome to your personalized fitness trainer, "
            "please answer this questionnaire to create your own personal workout routine.");

    // Asks the user's age (our program does not work with children)
    int age;
    printf("\nWhat is your age?");
    homemade_scan(integer, &age);
    if (age < 18) {
        printf("\nSorry, our program is designed for adults. You are too young.");
        exit(EXIT_FAILURE);
    } else if (age > 100) {
        printf("\nSorry, but our program is not designed for people who are more than 100 years old.");
        exit(EXIT_FAILURE);
    }

    while(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
        printf("\nWhat is your weight in kg?");
        homemade_scan(long_float, &_questionnaire.weight);
        if(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
            printf("\nInvalid weight. Try again.");
        }
    }

    // Asks what user's weight is, and loops through the input to make sure the weight is in a reasonable range (20-300 kg).
    while(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
        printf("\nWhat is your weight in kg?");
        homemade_scan(long_float, &_questionnaire.weight);
        if(_questionnaire.weight < 20 || _questionnaire.weight > 300) {
            printf("\nInvalid weight. Try again.");
        }
    }

    // Asks user to enter how many push-ups they can perform, ensuring only non-negative numbers.
    do {
        printf("\nHow many push-ups can you do?");
        homemade_scan(integer, &_questionnaire.pushups);
        if(_questionnaire.pushups < 0) {
            printf("\nPlease enter 0 or more!");
        }
    } while(_questionnaire.pushups < 0);

    // Asks user to enter how many squats they can perform, ensuring only non-negative numbers.
    do {
        printf("\nHow many squats can you do?");
        homemade_scan(integer, &_questionnaire.squats);
        if(_questionnaire.squats < 0) {
            printf("\nPlease enter 0 or more!");
        }
    } while(_questionnaire.squats < 0);

    // Asks user to enter their fitness level.
    do {
        printf("\nWhat is your fitness level/experience level in a scale of 1-5?");
        printf("\nfitness rank 1 (expert): expert experience with exercising"
               "\nfitness rank 2 (proficient): advanced experience with exercising"
               "\nfitness rank 3 (competent): intermediate experience with exercising"
               "\nfitness rank 4 (advanced beginner): A little experience with exercising"
               "\nfitness rank 5 (novice): No experience with exercising");

        // Validates that fitness level is between 1-5.
        homemade_scan(integer, &_questionnaire._fitness_level);
        if(_questionnaire._fitness_level < expert || _questionnaire._fitness_level > novice) {
            printf("\nIt has to be between 1-5!");
        }
    } while(_questionnaire._fitness_level < expert || _questionnaire._fitness_level > novice);


    update_available_training_days();
    update_available_equipment();
    update_ignored_muscle_groups();
}


