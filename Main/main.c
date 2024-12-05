#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "exercises.h"
#include "new_user_questionnaire.h"
//#include "routine.h"



int main(void) {
    questionnaire test = create_and_answer_questionnaire();
    print_quiestionnare(test);

    //initializing the exercise list
    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, test);
    aerobic_exercises_list(ex_test,test);


    //printf("\n_______________ALL EXERCISES______________\n");
    //print_exercise(ex_test);

    printf("\n_______________SORTED LIST______________\n");
    int sorted_count = 0;
    exercise* sorted_exercise_list = create_available_exercises(ex_test, test, &sorted_count);

    // Print the viable exercises
    print_exercises_2(sorted_exercise_list, sorted_count, test, ex_test);

    //  Call upgrade_downgrade function with sorted_exercise_list
    int input[sorted_count];
    upgrade_downgrade(sorted_exercise_list, test, sorted_count, input);

    //  Print exercises again after user has upgraded, or done nothing.
    print_exercises_2(sorted_exercise_list, sorted_count, test, ex_test);

    // Free the dynamically allocated memory for the sorted list
    free(sorted_exercise_list);

    return 0;

    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/

    return 0;
}
//hep