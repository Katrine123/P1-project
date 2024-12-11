#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "routine.h"
#include "savesystem.h"


int main(void) {
    //exercises_list();

    questionnaire user;
    print_routine();
    //FOR TESTING THAT EVALUATION QUEST WORKS TOGETHER WITH USER QUEST
    /*
    evaluation_questionnaire(&user);
    print_quiestionnare(user);*/

    //user start
    /*system("cls");
    if (check_for_save()==0) {
        questionnaire user = create_and_answer_questionnaire();
        print_quiestionnare(user);
    }else {
        if (evaluation_questionnaire(&user)==4) {
            create_and_answer_questionnaire();
        }
    }*/
    return 0;
}