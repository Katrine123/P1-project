#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "routine.h"
#include "savesystem.h"


int main(void) {
    questionnaire test = {67,"male",72,183,7,12,1,{monday,67},{1,0,0,0,1}};

    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, test);
    aerobic_exercises_list(ex_test,test);


    printf("\n_______________ALL EXERCISES______________\n");
    print_exercises_2(ex_test,7,test,ex_test);

    printf("\n_______________SORTED LIST______________\n");
    int sorted_count = 0;
    exercise* exercise_list_sorted = create_available_exercises(ex_test, test, &sorted_count);

    // Print the viable exercises
    print_exercises_2(exercise_list_sorted, sorted_count, test, ex_test);

    // Free the dynamically allocated memory for the sorted list
    free(exercise_list_sorted);

    questionnaire user;
    //FOR TESTING THAT EVALUATION QUEST WORKS TOGETHER WITH USER QUEST
    /*user = create_and_answer_questionnaire(stdin);
    print_quiestionnare(user);
    evaluation_questionnaire(&user,stdin);
    print_quiestionnare(user);*/

    //user start
    /*system("cls");
    if (check_for_save()==0) {
        questionnaire user = create_and_answer_questionnaire(stdin);
        print_quiestionnare(user);
    }else {
        if (evaluation_questionnaire(&user,stdin)==4) {
            create_and_answer_questionnaire(stdin);
        }
    }*/

    return 0;

    /* exercise* all_exercises = create_all_exercises();
    questionnaire user_questionnaire = create_and_answer_questionaire();
    exercise* available_exercises = create_available_exercises(all_exercises, user_questionnaire);*/

    return 0;
}