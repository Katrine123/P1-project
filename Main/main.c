#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "routine.h"
#include "savesystem.h"



int main(void) {
    questionnaire test = create_and_answer_questionnaire(stdin);
    print_quiestionnare(test);
    /*//OUTLINE FOR PROGRAM:
    questionnaire user_data;
    system("cls");
    //Checks if there is any saved data
    if (check_for_save()==0) {
        //If no saved data, then ask questionnaire and print
        user_data = create_and_answer_questionnaire(stdin);
        print_quiestionnare(user_data);
        //Initialize exercises based on users data
        exercise excercises[];
        resistance_exercises_list(excercises,user_data);
        aerobic_exercises_list(excercises,user_data);
        //Sort through exercises and remove unavailable ones
        int user_exercises_count;
        exercise* user_exercises = create_available_exercises(excercises,user_data,user_exercises_count);
        //Create workout routine and print
        update_routine_workouts();
        print_routine();
    }else {
        //If there is saved data then get it
        user_data = saved_data;
        //Initialize exercises with users data
        exercise excercises[];
        resistance_exercises_list(excercises,user_data);
        aerobic_exercises_list(excercises,user_data);
        //Sort through exercises and remove unavailable ones
        int user_exercises_count;
        exercise* user_exercises = create_available_exercises(excercises,user_data,user_exercises_count);
        //Ask evaluation questionnaire
        //Evaluation returns 1, if they want to upgrade
        if(evaluation_questionnaire(&user_data,stdin)==1) {
            //Upgrade completed exercises
            int exercises_count;
            upgrade_downgrade(user_exercises,user_data,exercises_count);
        }else if(evaluation_questionnaire(&user_data,stdin)==4) {
            //Evaluation returns 4, if they want to take the questionnaire again
            create_and_answer_questionnaire(stdin);
        }
    }*/

    return 0;
}