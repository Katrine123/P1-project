//
// Created by mwsan on 11/14/2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "tools.h"


// returns a int depending on answer from 1 to 5, can easily be changed with enum if thy want :3
int evaluation_questionnaire(exercise sorted_exercise_list[], int sorted_count, int *input) {
    printf("Welcome back!\n"
            "Your save file has been successfully loaded\n"
            "How has you're workout been going?\n"
            "__________________________________________________________________________\n\n"
            "If you like to retake the questionnaire?                     ***press 1***\n\n"
            "Reevaluate the difficulty of your exercises?                 ***press 2***\n\n"
            "To exit program immediately :                                ***press 3***\n"
            "__________________________________________________________________________\n");

    int answer=0;

    int has_answer=0; //used for while loop to define when 2 break.

    while(has_answer==0) {
        scanf("%d", &answer);
        has_answer++;
        switch (answer) {
            case 1:
                printf("Registered 1, questionnaire will appear!");
            break;
            case 2:
                printf("Registered 2, proceeding to reevaluate exercises:");
                //  Retrieving sorted exercise list
                upgrade_downgrade(sorted_exercise_list, sorted_count, input);
            break;
            case 3:
                printf("Program exiting");
            _Exit(0);
            default:;
            printf("invalid input\n");
            has_answer--;
            //Continues while loop if answer defaults.
        }

    }
    printf("How would you like to schedule this week's workouts?\n"
        "____________________________________________________________________________________\n\n"
        "If you want your workouts on the same days and the same times as last week   press 1\n\n"
        "If you would like to change your workout schedule                            press 2\n"
        "____________________________________________________________________________________\n");


    return answer;
}

