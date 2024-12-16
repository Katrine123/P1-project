#include <stdio.h>
#include <stdlib.h>
#include "references.c"

int main(void) {

    // Clear terminal screen
    system("cls");

    //TODO: If the following line of code isn't there, we get errors.
    // This has most likely to do with the ordering of the .c files.
    // If we do not use a function from tools.c here, it will not
    // be loaded before everything else and thus the other .c files
    // that make use of tools.c will not be able to make a reference to it
    // (because tools.c does not exist yet).
    // I do not know how to fix this, so I'll just leave this here
    // as it does not interfere with the rest of the program.
    naming_equipment(0);

    // Try to load save data
    // TODO: Implement this.

    // Does save data exist?
    // if (found_save) {   // TODO: found_save is a boolean int updated when loading save data

        // Evaluation questionnaire
        // TODO: Implement this.

    // } else {

        // New user questionnaire
        update_questionnaire();

    // }

    // Create routine
    update_and_print_routine();

    // Evaluation questionnaire (recursion)
    int input[possible_exercises_count];
    evaluation_questionnaire(input);

    return 0;
}