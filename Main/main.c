#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "exercises.h"
#include "new_user_questionnaire.h"
//#include "routine.h"

void main() {
    questionnaire test = create_and_answer_questionnaire();
    print_quiestionnare(test);

    exercises_list();

    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/
}
//hep