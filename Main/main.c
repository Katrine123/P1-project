#include <stdio.h>
#include <stdlib.h>
#include "references.h"

// Main function

int main(void) {

    system("cls"); // Clears terminal screen

    user_data user;

    // Does save data exist?
    if (check_for_save()) {   // TODO: found_save is a boolean int updated when loading save data
        get_saved_user_data(&user); // get user_data from user_save_file
        printf("\n\nWelcome back!\n"
            "Your save file has been successfully loaded.\n");
    } else {
        answer_new_user_questionnaire(&user);
    }

    // Run evaluation questionnaire
    evaluation_questionnaire(&user);

    return 0;
}