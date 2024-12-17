#include <stdio.h>
#include <stdlib.h>
#include "references.h"

// Miscellaneous functions

void update_and_print_routine(user_data *user) {

    // Create list of exercises
    update_possible_exercises(user);

    all_possible_exercises(user);

    // Create routine workouts
    update_routine_workouts(user);

    // Print routine
    print_routine(user);
}

// Main function

int main(void) {

    // Clear terminal screen
    system("cls");

    user_data user;

    // Try to load save data
    // TODO: Implement this.

    // Does save data exist?
    // if (found_save) {   // TODO: found_save is a boolean int updated when loading save data

        // Evaluation questionnaire
        // TODO: Implement this.

    // } else {

        // New user questionnaire
        update_questionnaire(&user);

    // Create routine
    update_and_print_routine(&user);

    // Evaluation questionnaire (recursion)
    // TODO: Implement this.

    return 0;
}