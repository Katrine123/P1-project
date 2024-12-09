#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "evaluation_questionnaire.h"


// returns a int depending on answer from 1 to 5, can easily be changed with enum if thy want :3
int evaluation_questionnaire(questionnaire* user,FILE *file) {
    printf("Welcome back!\n"
            "Your save file has been successfully loaded\n"
            "How has you're workout been going?\n"
            "__________________________________________________________________________\n\n"
            "Would you like to continue increasing your workout level?:   ***press 1***\n\n"
            "Would you like to stay on your current workout level?:       ***press 2***\n\n"
            "Would you like to decrease your workout level?:              ***press 3***\n\n"
            "If you like to retake the questionnaire?                     ***press 4***\n\n"
            "To exit program immediately :                                ***press 5***\n"
            "__________________________________________________________________________\n");

    int answer=0;

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
            break;
            case 3:
                printf("Registered 3 pressed workout will decrease!");
            //increasedifficulty();
            break;
            case 4:
                printf("Registered 4 pressed questionnaire will appear!");
            break;
            case 5:
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
    has_answer=0;
    while(has_answer==0) {
        scanf("%d", &answer);
        has_answer++;
        switch (answer) {
            case 1:
                printf("Registered 1 pressed: Workoutdays will remain the same");
            break;
            case 2:
                printf("Registered 2 pressed: ");
            get_user_days(user,file);
            default: ;
        }
    }
    return answer;

    return answer;
}

