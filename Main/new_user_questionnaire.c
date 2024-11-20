#include <stdio.h>
#include <stdlib.h>
#include "new_user_questionnaire.h"
#include <string.h>

questionnaire create_and_answer_questionnaire() {


    questionnaire user;

    printf("Welcome to your personalized fitness trainer, please answer this questionnaire to create your person workout routine");
    printf("\n");
    printf("What is your age in years?");

    homemade_scan(integer,&user.age);
    //scanf("%d", &user.age);
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
        homemade_scan(string,&user.gender);
        //scanf("%s", &user.gender);
    }while(strcmp(user.gender,"male")!=0&& strcmp(user.gender,"female")!=0);



    while(user.weight < 20 || user.weight > 300) {
        printf("What is your weight in kg");
        homemade_scan(long_float,&user.weight);
        //scanf("%lf", &user.weight);
        if(user.weight < 20 || user.weight > 300) {
            printf("I don't think that is correct!");
            printf("\n");
        }
    }


    while(user.height < 50 || user.height > 300) {
        printf("What is your height in cm?");
        homemade_scan(long_float,&user.height);
        //scanf("%lf", &user.height);
        if(user.height < 50 || user.height > 300) {
            printf("I don't think that is correct!");
            printf("\n");
        }
    }


    do {
        printf("How many push-ups, can you do?");
        homemade_scan(integer,&user.pushups);
        //scanf("%d", &user.pushups);
        if(user.pushups < 0) {
            printf("Please enter 0 or more!");
            printf("\n");
        }
    } while(user.pushups < 0);



    do {
        printf("What is your fitness level/experience level in a scale of 1-5?\n");

        printf("fitness level 1: No experience with exercising \n"
               "fitness level 2: A little experience with exercising\n"
               "fitness level 3: intermediate experience with exercising\n"
               "fitness level 4: advanced experience with exercising\n"
               "fitness level 5: expert experience with exercising\n");


        homemade_scan(integer,&user.fitness_level);
        //scanf("%d", &user.fitness_level);
        if(user.fitness_level < 1 || user.fitness_level > 5) {
            printf("It has to be between 1-5!");
            printf("\n");
        }
    }while(user.fitness_level < 1 || user.fitness_level > 5);


    do {
        printf("What is your weekly time available in hours?");
        homemade_scan(long_float,&user.time_available_week);
        //scanf("%lf", &user.time_available_week);
        if(user.time_available_week > 168) {
            printf("You do not have more hours than there is in a week!");
            printf("\n");
        }
        if(user.time_available_week < 1) {
            printf("If you have no time available we cannot help you!");
            exit(-1);
        }
    }while(user.time_available_week > 168);

    char gym[5];

    printf("Do you have access to a gym?");
    homemade_scan(string,gym);
    //scanf("%s", gym);

    if(strcmp(gym,"Yes")==0) {
        for(int i=0; i<EQUIP_LEN; i++) {
            user.available_equipment[i]=i;
        }
    } else if(strcmp(gym, "No")==0) {
        printf("Of these options what equipment do you have? Please enter the number and when you are done press -1");
        printf("\n");
        for(int i=0; i<EQUIP_LEN; i++) {
            printf("%d: %s \n", i, naming_equipment(i));
        }
        int answer[EQUIP_LEN];
        int i = 0;
        do {
            homemade_scan(integer,&answer[i]);
            //scanf("%d", &answer[i]);
            if(answer[i]> EQUIP_LEN || answer[i] < -1) {
                printf("please enter a number that is in the equipment list!");
            } else {
                i++;
            }

        }while(answer[i-1] != -1);//Lav til liste af 1'er og 0'er
        for(int j = 0; answer[j]!=-1; j++) {
            user.available_equipment[j] = answer[j];
        }
    }


    return user;
}

void print_quiestionnare(questionnaire user) {
    printf("Age:%d\n",user.age);
    printf("Gender: %s\n",user.gender);
    printf("Weight: %lf\n",user.weight);
    printf("Height: %lf\n",user.height);
    printf("Amount of pushups: %d\n",user.pushups);
    printf("Fitness level: %d\n",user.fitness_level);
    printf("Time in week: %lf\n",user.time_available_week);
    int len = sizeof(user.available_equipment)/sizeof(user.available_equipment[0]);
    printf("%d",len);
    printf("Available equipment: ");
    /*if(len == 0) {
        printf("Nothing");
    }else {
        for(int i = 0; i<len;i++) {
            printf("%s, ",naming_equipment(user.available_equipment[i]));
        }
    }*/
}

