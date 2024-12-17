#include <stdio.h>
#include <stdlib.h>
#include "references.h"

// Main function

int main(void) {

    // Clear terminal screen
    system("cls");

    user_data user;

    // Does save data exist?
    if (check_for_save()) {   // TODO: found_save is a boolean int updated when loading save data
        // Evaluation questionnaire
        get_user_data(&user); // get user_data from user_save_file
        update_possible_exercises(&user); // because possible exercises are used in the upgrade/downgrade function
        evaluation_questionnaire(&user);
        update_routine_workouts(&user);
        print_routine(&user);
    } else {
        // New user questionnaire
        update_questionnaire(&user);
        update_possible_exercises(&user);
        update_routine_workouts(&user);
        print_routine(&user);
        initialize_upgr_dogr(&user); // create user_upgrades save file
    }
    return 0;
}