#include <stdio.h>
#include <stdlib.h>
#include "references.c"

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
        update_questionnaire(stdin);

    // }

    // Create routine
    update_and_print_routine();

    // Evaluation questionnaire (recursion)
    // TODO: Implement this.

    return 0;
}