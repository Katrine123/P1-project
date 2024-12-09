#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

questionnaire create_and_answer_questionnaire(FILE *file) {


    questionnaire user;

    // Welcome message to new users.
    printf("Welcome to your personalized fitness trainer, please answer this questionnaire to create your own personal workout routine \n");

    ////////////////////////////////////////////////////////////////////

    // Ask's about the users age.
    printf("What is your age in years?");
    homemade_scan(integer,&user.age,file);

    // Checks if the user is too old. If user is above 100 years program will exit.
    if(user.age > 100) {
        printf("You are too old to exercise!");
        exit(-1);
    }

    // Checks if the user is too young. If user is below 14 years program will exit.
    if(user.age < 14) {
        printf("You are too young for this fitness trainer!");
        exit(-1);
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter there gender, and validate it to only accept input "male" or "female".
    do{
        printf("Are you a male or female");
        homemade_scan(string, user.gender,file);
    }while(strcmp(user.gender,"male")!=0&& strcmp(user.gender,"female")!=0);

    ////////////////////////////////////////////////////////////////////

    // Ask's what users weight is, and loops through the input to make sure the weight is in a reasonable range (20-300 kg).
    while(user.weight < 20 || user.weight > 300) {
        printf("What is your weight in kg");
        homemade_scan(long_float, &user.weight,file);
        if(user.weight < 20 || user.weight > 300) {
            printf("I don't think that is correct!\n");
        }
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's what users height is and loops through the input, to make sure the height is in a reasonable range (50-300 cm).
    while(user.height < 50 || user.height > 300) {
        printf("What is your height in cm?");
        homemade_scan(long_float, &user.height,file);
        if(user.height < 50 || user.height > 300) {
            printf("I don't think that is correct!\n");
        }
    }
    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter how many push-ups they can perform, ensuring only non-negative numbers.
    do {
        printf("How many push-ups, can you do?");
        homemade_scan(integer, &user.pushups,file);
        if(user.pushups < 0) {
            printf("Please enter 0 or more!\n");
        }
    } while(user.pushups < 0);

    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter how many squats they can perform, ensuring only non-negative numbers.
    do {
        printf("How many squats, can you do?");
        homemade_scan(integer, &user.squats,file);
        if(user.squats < 0) {
            printf("Please enter 0 or more!\n");
        }
    } while(user.squats < 0);

    ////////////////////////////////////////////////////////////////////

    // Ask's user to enter there fitness level.
    do {
        printf("What is your fitness level/experience level in a scale of 1-5?\n");

        printf("fitness level 1: No experience with exercising \n"
               "fitness level 2: A little experience with exercising\n"
               "fitness level 3: intermediate experience with exercising\n"
               "fitness level 4: advanced experience with exercising\n"
               "fitness level 5: expert experience with exercising\n");

        // Validates that fitness level is between 1-5.
        homemade_scan(integer, &user.fitness_level,file);
        if(user.fitness_level < 1 || user.fitness_level > 5) {
            printf("It has to be between 1-5!\n");
        }
    }while(user.fitness_level < 1 || user.fitness_level > 5);

    ////////////////////////////////////////////////////////////////////
    //Function for getting the days the user can train
    get_user_days(&user,file);
    ////////////////////////////////////////////////////////////////////



    char gym[5];

    // ask's the user if they have access to a gym.
    printf("Do you have access to a gym?");
    homemade_scan(string, gym, file);

    // If user have access to a gym, they have access to all the equipment in the array.
    if(strcmp(gym,"Yes")==0||strcmp(gym,"yes")==0) {
        for(int i=0; i<5; i++) {
            user.available_equipment[i]=1;
        }
        // If the user do not have access to a gym, they will be asked to enter the equipment available based on a defined list.
    } else if(strcmp(gym, "No")==0||strcmp(gym, "no")==0) {
        printf("Of these options what equipment do you have? Please enter the number and when you are done press -1\n");
        for(int i=0; i<5; i++) {
            printf("%d: %s \n", i, naming_equipment(i));
        }
        // Array to store equipment option selected by user.
        int answer[5];
        int i = 0;
        // Loops to gather the equipment selected by the user, stopping at -1.
        do {
            homemade_scan(integer, &answer[i],file);
            if(answer[i]> 5 || answer[i] < -1) {
                printf("please enter a number that is in the equipment list!");
            } else {
                i++;
            }
        }while(answer[i-1] != -1);

        for(int n = 0; n < 5; n++) {
            user.available_equipment[n] = 0;
        }
        // Transfer selected equipment to the user struct "questionnaire".
        for(int j = 0; answer[j]!=-1; j++) {
            user.available_equipment[answer[j]] = 1;
        }
    }

    ////////////////////////////////////////////////////////////////////

    return user;
}

void print_quiestionnare(questionnaire user) {
    printf("Age:%d\n",user.age);
    printf("Gender: %s\n",user.gender);
    printf("Weight: %lf\n",user.weight);
    printf("Height: %lf\n",user.height);
    printf("Amount of pushups: %d\n",user.pushups);
    printf("Fitness level: %d\n",user.fitness_level);
    printf("Time a week:\n");
    for(int i = 0;strcmp(naming_days(user.training_days[i].day_week),"Error")!=0;i++) {
        printf("%s: %lf minutes\n",naming_days(user.training_days[i].day_week),user.training_days[i].available_time);
    }
    int len = sizeof(user.available_equipment)/sizeof(user.available_equipment[0]);
    printf("Available equipment: ");
    if(len == 0) {
        printf("Nothing"); 
    }else {
        for(int i = 0; i<len;i++) {
            if(user.available_equipment[i]==1) {
                printf("%s, ",naming_equipment(i));
            }
        }
    }
}


int get_user_days(questionnaire* user,FILE *file) {
    printf("What days a week do you have time? Please write numbers matching the days and type -1 when you're done\n");
    printf("1. Monday\n2. Tuesday\n3. Wednesday\n4.Thursday\n5.Friday\n6. Saturday\n7.Sunday");
    //Array to store users answer
    int days[7];
    int i = 0;
    do {
        int add = 1;
        homemade_scan(integer, &days[i],file);

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
        user->training_days[i].day_week = days[i];
        homemade_scan(long_float,&user->training_days[i].available_time,file);
        if(user->training_days[i].available_time > 1440) {
            printf("That's more than there is in a day");
            add =0;
        }else if(user->training_days[i].available_time < 0) {
            printf("If you have no time this day then don't write that you have");
            //FJERN DAG FRA ARRAY EVT?
        }
        i+=add;
    }while(days[i]!=-1);
}

