#include <stdio.h>
#include <stdlib.h>
#include "new_user_questionnaire.h"
#include <ctype.h> //https://www.tutorialspoint.com/c_standard_library/ctype_h.htm

#include <string.h>

int homemade_scan(char type, int antal_inputs, char* input) {//FIKS SÅ DEN OGSÅ KAN TAGE INTEGERS?
    if(type == 'i') {
        scanf("%c",input);
        while ((getchar()) != '\n'); //(https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/)
        if(isdigit(*input)!=0) {
            printf("YAH");
            return 1;
        }else {
            printf("NAH");
            return 0;
        }
        //Sørg for at man kun kan få integers
    }else if(type == 'c') {
        scanf("%c",input);
        printf("Is a letter? %d ",isalpha(*input));
    }else if(type == 'd') {
        //kun doubles
    }else if(type == 's') {
        //Kun string
    }
}

/*KUN INT
 *  - Man skal kun bruge antal inputs (ex. kig på første tal, og fjern resten fra memory) - brug fflush
 *  - Matcher input med den datatype vi vil have?
 *  - Hvis ja, så output 1
 *  - Hvis nej så output 0
 */



char* naming_equipment(enum equipment eq) {
    switch(eq) {
        case nothing: return "Nothing";
        break;
        case barbell: return "Barbell";
        break;
        case bench: return "Bench";
        break;
        case pull_up_bar: return "Pull up bar";
        break;
        case pull_down_machine: return "Pull down machine";
        break;
        case resistance_bands: return "Resistance bands";
        break;
    }
}


questionnaire create_and_answer_questionaire() {
    char test;
    homemade_scan('i',1,&test);


    questionnaire user;

    printf("Welcome to your personalized fitness trainer, please answer this questionnaire to create your person workout routine");
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
       /* if (scanf("%lf", &user.weight)==0) {
            printf("Please enter a number");
            user.weight = 0;
        } else*/ if(user.weight < 20 || user.weight > 300) {
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
        printf("What is your fitness level/experience level in a scale of 1-5?\n");

        printf("fitness level 1: No experience with exercising \n"
               "fitness level 2: A little experience with exercising\n"
               "fitness level 3: intermediate experience with exercising\n"
               "fitness level 4: advanced experience with exercising\n"
               "fitness level 5: expert experience with exercising\n");


        scanf("%d", &user.fitness_level);
        if(user.fitness_level < 1 || user.fitness_level > 5) {
            printf("It has to be between 1-5!");
            printf("\n");
        }
    }while(user.fitness_level < 1 || user.fitness_level > 5);


    do {
        printf("What is your weekly time available on a weekly basis in hours?");
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

    char gym[5];

    printf("Do you have access to a gym?");
    scanf("%s", gym);

    if(strcmp(gym,"Yes")==0) {
        for(int i=0; i<6; i++) {
            user.available_equipment[i]=i+1;
        }
    } else if(strcmp(gym, "No")==0) {
        printf("Of these options what equipment do you have? Please enter the number and when you are done press -1");
        printf("\n");
        for(int i=0; i<6; i++) {
            printf("%d: %s \n", i, naming_equipment(i));
        }
        int answer[6];
        int i = 0;
        do {
            scanf("%d", &answer[i]);
            if(answer[i]> 5 || answer[i] < -1) {
                printf("please enter a number that is in the equipment list!");
            } else {
                i++;
            }

        }while(answer[i-1] != -1);
        for(int j = 0; answer[j]!=-1; j++) {
            user.available_equipment[j] = answer[j];
        }
    }


    return user;
}

