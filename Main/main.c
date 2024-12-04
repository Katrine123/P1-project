#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "routine.h"
#include "savesystem.h"


int main(void) {
    //exercises_list();

    questionnaire user = create_and_answer_questionnaire();
    //FOR TESTING THAT EVALUATION QUEST WORKS TOGETHER WITH USER QUEST
    /*
    print_quiestionnare(user);
    evaluation_questionnaire(&user);
    print_quiestionnare(user);*/

    //user start
    /*system("cls");
    if (check_for_save()==0) {
        questionnaire user = create_and_answer_questionnaire();
    }else {
        if (evaluation_questionnaire(&user)==4) {
            create_and_answer_questionnaire();
        }
    }*/







    return 0;
    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/
}
//hep