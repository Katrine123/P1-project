#include <stdio.h>
#include <stdlib.h>
#include "new_user_questionnaire.h"

#include <string.h>


questionnaire create_and_answer_questionaire() {
    questionnaire user;

    printf("Welcome to your personolized fitness trainer, please answer this questionaire to create your person workout routine");
    printf("\n");
    printf("What is your age in years?");
    scanf("%d", &user.age);

    if(user.age > 100) {
        printf("You are too old to exercise!");
        exit(-1);
    }

    if(user.age < 14) {
        printf("You are too young for this fitness trainer!");
        exit(-1);
    }

    do{
        printf("Are you a male or female");
        scanf("%s", &user.gender);
    }while(strcmp(user.gender,"male")!=0&& strcmp(user.gender,"female")!=0);



    while(user.weight < 20 || user.weight > 300) {
        printf("What is your weight in kg");
        scanf("%lf", &user.weight);
        if(user.weight < 20 || user.weight > 300) {
            printf("I don't think that is correct!");
            printf("\n");
        }
    }


    while(user.height < 50 || user.height > 300) {
        printf("What is your height in cm?");
        scanf("%lf", &user.height);
        if(user.height < 50 || user.height > 300) {
            printf("I don't think that is correct!");
            printf("\n");
        }
    }


    do {
        printf("How many push-ups, can you do?");
        scanf("%d", &user.pushups);
        if(user.pushups < 0) {
            printf("Please enter 0 or more!");
            printf("\n");
        }
    } while(user.pushups < 0);



    do {
        printf("What is your fitness level/experience level in a scale of 1-5?");
        scanf("%d", &user.fitness_level);
        if(user.fitness_level < 1 || user.fitness_level > 5) {
            printf("It has to be between 1-5!");
            printf("\n");
        }
    }while(user.fitness_level < 1 || user.fitness_level > 5);


    do {
        printf("What is your weekly time available on a weekly basis?");
        scanf("%lf", &user.time_available_week);
        if(user.time_available_week > 168) {
            printf("You do not have more hours than there is in a week!");
            printf("\n");
        }
        if(user.time_available_week < 1) {
            printf("If you have no time available we cannot help you!");
            exit(-1);
        }
    }while(user.time_available_week > 168);

    return user;
}

