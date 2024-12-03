#include "evaluation_questionnaire.h"
#include "new_user_questionnaire.h"
#include <stdio.h>
#include <stdlib.h>

int get_user_days(void);

// returns a int depending on answer from 1 to 5, can easily be changed with enum if thy want :3
int evaluation_questionnaire() {
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
            //increasedifficulty();
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
                printf("Registered 1 pressed workout will intensify!");
            break;
            case 2:
                printf("Registered 2 pressed workout wont change!");
            get_user_days();
            default: ;
        }
    }
    return answer;
}

int get_user_days(void) {

    printf("What days a week do you have time? Please write numbers matching the days and type -1 when you're done\n");
    printf("1. Monday\n2. Tuesday\n3. Wednesday\n4.Thursday\n5.Friday\n6. Saturday\n7.Sunday");
    //Array to store users answer
    int days[7];
    int i = 0;
    do {
        int add = 1;
        homemade_scan(integer, &days[i]);

        //Check if the same day is chosen twice
        for(int j = 0; j<i;j++) {
            if(days[i]==days[j]) {
                printf("This day has already been chosen");
                add = 0;
                break;
            }
        }

        if(days[i]>7 || days[i]<-1||days[i]==0) {
            printf("Please choose one of the numbers available");
            add = 0;
        }
        //If they have no days availabe then close program
        if(i == 0 && days[i]==-1) {
            printf("If you have no time available we cannot help you!");
            exit(-1);
        }

        i += add;
    }while(i<7&&days[i-1]!=-1);

    i = 0;

    do {
        int add = 1;
        printf("How much time(in minutes) do you have %s?",naming_days(days[i]));
        user.training_days[i].day_week = days[i];
        homemade_scan(long_float,&user.training_days[i].available_time);
        if(user.training_days[i].available_time > 1440) {
            printf("That's more than there is in a day");
            add =0;
        }else if(user.training_days[i].available_time < 0) {
            printf("If you have no time this day then don't write that you have");
            //FJERN DAG FRA ARRAY EVT?
        }
        i+=add;
    }while(days[i]!=-1);
}
