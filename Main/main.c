#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "exercises.h"
#include "new_user_questionnaire.h"
//#include "routine.h"

int main(void) {
    questionnaire test = create_and_answer_questionnaire();
    print_quiestionnare(test);
    exercise ex_test[length_of_exercises_list];
    exercises_list(ex_test,test);
    print_exercise(ex_test);
    exercise* ex_test2 = create_available_exercises(ex_test, test);
    printf("_____________________________________");
    print_exercise(ex_test2);

    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/
    return 0;
}
//hep