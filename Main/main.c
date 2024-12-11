#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "routine.h"
#include "savesystem.h"


int main(void) {

    check_for_save();
    questionnaire user = load_data();
    printf("%d", user.age);


    return 0;

    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/

    return 0;
}