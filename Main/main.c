#include <stdio.h>
#include <stdlib.h>
#include "references.c"


void create_routine() {

    // Create list of exercises
    update_possible_exercises();

    // Create routine
    update_routine_workouts();

    // Print routine
    // TODO: Implement this.
}

int main(void) {

    // Clear terminal screen
    // system("cls"); // TODO: What is the purpose of this?

    //TODO: Test. Remove this.
    printf("\n%s", naming_equipment(2)); //TODO: Why does this need to be here for me not to get errors? Probably has to do with the order of .c files.

    // Try to load save data

    // Does save data exist?
    // if (found_save) {   // TODO: found_save is a boolean int updated when loading save data

        // Evaluation questionnaire
        // TODO: Implement this.

    // } else {

        // New user questionnaire
        update_questionnaire();

    // }

    create_routine();

    // Evaluation questionnaire (recursion)
    // TODO: Implement this.


    return 0;
}