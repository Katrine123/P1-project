#include <stdio.h>
#include <stdlib.h>
#include "references.h"

// Main function

int main(void) {

    system("cls"); // Clears terminal screen

    user_data user;

    // Does save data exist?
    if (check_for_user_data_save()) {
        load_user_data_save(&user);
        printf("\n\nWelcome back!\n"
            "Your save file has been successfully loaded.\n");
    } else {
        start_new_user_questionnaire(&user);
    }

    // Run evaluation questionnaire
    start_evaluation_questionnaire(&user);

    return 0;
}