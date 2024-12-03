#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "exercises.h"
#include "new_user_questionnaire.h"
#include "routine.h"
#include "evaluation_questionnaire.h"
#include "savesystem.h"


void main() {
    //questionnaire test = create_and_answer_questionnaire();
    //print_quiestionnare(test);

    //exercises_list();


    //user start
    system("cls");
    if (check_for_save()==0) {
        create_and_answer_questionnaire();

    }else {
        if (evaluation_questionnaire()==4) {
            create_and_answer_questionnaire();
        }
    }








    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/
}
//hep