#include <stdio.h>
#include <stdlib.h>
#include "references.h"

// Main function

int main(void) {

    // Clear terminal screen
    system("cls");

    user_data user;
    // update_questionnaire(&user);
    // save_all_data(&user);

    // Does save data exist?
    if (check_for_save()) {   // TODO: found_save is a boolean int updated when loading save data

        // Evaluation questionnaire
        get_user_data(&user);
        update_possible_exercises(&user);
        initialize_upgr_dogr(&user);
        int input[user.possible_exercises_count];
        evaluation_questionnaire(&user, input);
        update_routine_workouts(&user);
        print_routine(&user);

    } else {

        // New user questionnaire
        update_questionnaire(&user);
        update_possible_exercises(&user);
        update_routine_workouts(&user);
        print_routine(&user);
        initialize_upgr_dogr(&user);

    }

    return 0;
}