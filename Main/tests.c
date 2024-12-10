#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h" //HUSK KILDE
#include "tools.h"

TEST_CASE(questionnaire_test1,{
    //Making "User inputs"
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67 male 72 183 6 8 1 4 -1 120 Yes");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    questionnaire user_test = create_and_answer_questionnaire(test_file);
    fclose(test_file);
    CHECK_EQ_INT(user_test.age,67);
    CHECK_EQ_STRING(user_test.gender,"male");
    CHECK_EQ_DOUBLE(user_test.weight,72,0.001);
    CHECK_EQ_DOUBLE(user_test.height,183,0.001);
    CHECK_EQ_INT(user_test.pushups,6);
    CHECK_EQ_INT(user_test.squats,8);
    CHECK_EQ_INT(user_test.fitness_level,1);
    CHECK_EQ_INT(user_test.training_days[0].day_week,thursday);
    CHECK_EQ_DOUBLE(user_test.training_days[0].available_time,120,0.001);
    for(int i = 0; i<length_of_equipment_enum;i++) {
        CHECK_EQ_INT(user_test.available_equipment[i],1);
    }
})

//CHANGE SO THAT USER INPUT IS DIFFERENT
TEST_CASE(questionnaire_test2,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67 male 72 183 6 8 1 4 -1 120 Yes");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    questionnaire user_test = create_and_answer_questionnaire(test_file);
    fclose(test_file);
})


TEST_CASE(homemade_scan_test,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"45 hej 34");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    int int_test;
    homemade_scan(integer,&int_test,test_file);
    CHECK_EQ_INT(int_test,45);
    char char_test;
    homemade_scan(character,&char_test,test_file);
    CHECK_EQ_CHAR(char_test,'h');
    char string_test[10];
    homemade_scan(string,&string_test,test_file);
    CHECK_EQ_STRING(string_test,"ej");
    double double_test;
    homemade_scan(long_float,&double_test,test_file);
    CHECK_EQ_DOUBLE(double_test,34,0.001);
    fclose(test_file);
})

TEST_CASE(sorting_exercises_test,{
    questionnaire test = {67,"male",72,183,7,12,1,{monday,67},{0,0,0,0,0}};
    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, test);
    aerobic_exercises_list(ex_test,test);
    int sorted_count = 0;
    exercise* exercise_list_sorted = create_available_exercises(ex_test, test, &sorted_count);

    CHECK_EQ_STRING(exercise_list_sorted[0].name,"Air squats");
    CHECK_EQ_STRING(exercise_list_sorted[1].name,"Pushups");
    CHECK_EQ_STRING(exercise_list_sorted[2].name,"Elevated pushups");
    CHECK_EQ_STRING(exercise_list_sorted[3].name,"Burpees");
    CHECK_EQ_STRING(exercise_list_sorted[4].name,"Jumping jacks");

    // Free the dynamically allocated memory for the sorted list
    free(exercise_list_sorted);
})

TEST_CASE(calculations,{
    questionnaire test = {67,"male",65,183,5,12,1,{monday,67},{0,0,0,0,0}};
    double test_value = base_weight_bench_press(test);
    CHECK_EQ_DOUBLE(test_value,35,0.001);
})
//EDGECASES!

TEST_CASE(upgrade_test,{
    questionnaire test = {67,"male",65,183,5,12,1,{monday,67},{0,0,0,0,0}};
})

MAIN_RUN_TESTS(/*questionnaire_test1,questionnaire_test2,*/homemade_scan_test/*, sorting_exercises_test, calculations*/)

/*What to test:
 * Upgrade/Downgrade
 */


