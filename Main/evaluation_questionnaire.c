#include "evaluation_questionnaire.h"

void print_evaluation_questionnaire() {
    // then upgrade (upgrade function not implemented yet)

    // then downgrade (downgrade function not implemented yet)

    // then it's alright, so quit

}

void sorting_valid_excersises(char user_equipment[100]) {
    int valid_excersise_list[100];
    int n=0;
    for (int i = 0; i < amount_of_exercises; i++) { //amount_of_exercises needs change depending on final name
        if (exercise_database[i].type_equipment == user_equipment ) { //exercise_database needs change depending on final name
            valid_excersise_list[n] = i;
            n++;
        }
    }
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Welcome back!\n"
            "Your save file has been successfully loaded\n"
            "How has you're workout been going?\n"
            "__________________________________________________________________________\n\n"
            "Would you like to continue increasing your workout level:    ***press 1***\n\n"
            "Would you like to stay on your current workout level:        ***press 2***\n\n"
            "Would you like to decrease your workout level:               ***press 3***\n\n"
            "To exit program immediately:                                 ***press 4***\n"
            "__________________________________________________________________________\n");

    int answer=0; //used to get

    int has_answer=0; //used for while loop to define when 2 break.

    while(has_answer==0) {
        scanf("%d", &answer);
        has_answer++;
        switch (answer) {
            case 1:
                printf("Registered 1 pressed workout will intensify!");
            //increasedifficulty();
            break;
            case 2:
                printf("Registered 2 pressed workout wont change!");
            //increasedifficulty();
            break;
            case 3:
                printf("Registered 3 pressed workout will decrease!");
            //increasedifficulty();
            break;
            case 4:
                printf("Program exiting");
            _Exit(0);
            default:;
            printf("invalid input\n");
            has_answer--;
            //Continues while loop if answer defaults.
        }

    }
    return answer;
}

int main() {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "r"))) {   // attempts to open file
        printf("read operation successful\n");
        // insert read code
        // char str[500];
        // printf("%s", fgets(str, 50, file));

        fclose(file);
    }
    else {printf("No previous answers saved\n");
        //user_questionnaire(); // opens first time user questionnaire as file opening attempt failed
    }
}

