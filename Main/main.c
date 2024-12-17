#include <stdio.h>
#include <stdlib.h>
#include "references.h"

int main(void) {

    // Clear terminal screen
    system("cls");

    // Try to load save data
    // TODO: Implement this.

    // Does save data exist?
    // if (found_save) {   // TODO: found_save is a boolean int updated when loading save data

        // Evaluation questionnaire
        // TODO: Implement this.

    // } else {

        // New user questionnaire
        // update_questionnaire();

    get_user_data();
    // }

    // Create routine
    update_and_print_routine();

    // Evaluation questionnaire (recursion)
    int input[possible_exercises_count];

    evaluation_questionnaire(input);

    update_and_print_routine();



    return 0;
}