#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h"
#include "tools.h"

#pragma region questionnaire
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

#pragma endregion

#pragma region homemade_scan
TEST_CASE(homemade_scan_test,{//OPLEVER FEJL HVIS ANDEN COMPUTER. DONT KNOW WHY :]
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
#pragma endregion

#pragma region sorting_exercises
//TEST THAT YOU ONLY GET THE EXERCISES NEEDING NO EQUIPMENT - IS SUPPOSED TO SUCCEED
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

//TESTS THAT YOU GET ALL EXERCISES IF YOU HAVE ALL EQUIPMENT - IS SUPPOSED TO SUCCEED
TEST_CASE(sorting_exercises_test2,{
    questionnaire test = {67,"male",72,183,7,12,1,{monday,67},{1,1,1,1,1}};
    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, test);
    aerobic_exercises_list(ex_test,test);
    int sorted_count = 0;
    exercise* exercise_list_sorted = create_available_exercises(ex_test, test, &sorted_count);
    CHECK_EQ_STRING(exercise_list_sorted[0].name,"Bench press");
    CHECK_EQ_STRING(exercise_list_sorted[1].name,"Weighted squats");
    CHECK_EQ_STRING(exercise_list_sorted[2].name,"Air squats");
    CHECK_EQ_STRING(exercise_list_sorted[3].name,"Pushups");
    CHECK_EQ_STRING(exercise_list_sorted[4].name,"Elevated pushups");
    CHECK_EQ_STRING(exercise_list_sorted[5].name,"Burpees");
    CHECK_EQ_STRING(exercise_list_sorted[6].name,"Jumping jacks");

    // Free the dynamically allocated memory for the sorted list
    free(exercise_list_sorted);
})

//TESTS FOR -1 - IS SUPPOSED TO FAIL
TEST_CASE(sorting_exercises_test3,{
    questionnaire test = {67,"male",72,183,7,12,1,{monday,67},{-1,1,1,1,1}};
    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, test);
    aerobic_exercises_list(ex_test,test);
    int sorted_count = 0;
    exercise* exercise_list_sorted = create_available_exercises(ex_test, test, &sorted_count);
    CHECK_EQ_STRING(exercise_list_sorted[0].name,"Bench press");
    CHECK_EQ_STRING(exercise_list_sorted[1].name,"Weighted squats");
    CHECK_EQ_STRING(exercise_list_sorted[2].name,"Air squats");
    CHECK_EQ_STRING(exercise_list_sorted[3].name,"Pushups");
    CHECK_EQ_STRING(exercise_list_sorted[4].name,"Elevated pushups");
    CHECK_EQ_STRING(exercise_list_sorted[5].name,"Burpees");
    CHECK_EQ_STRING(exercise_list_sorted[6].name,"Jumping jacks");

    // Free the dynamically allocated memory for the sorted list
    free(exercise_list_sorted);
})
#pragma endregion

#pragma region calculations

TEST_CASE(calculations,{
    questionnaire test;
    test.weight = 65;
    test.pushups = 5;
    double test_value = base_weight_bench_press(test);
    CHECK_EQ_DOUBLE(test_value,35,0.001);
})

//IS SUPPOSED TO FAIL - THE QUESTIONNAIRE STOPS ANY ZEROS FOR WEIGHT
TEST_CASE(calculations2,{
    questionnaire test;
    test.weight = 0;
    test.pushups = 5;
    double test_value = base_weight_bench_press(test);
    CHECK_EQ_DOUBLE(test_value,30,0.001);
})

//TESTS FOR THE HIGHEST POSSIBLE WEIGHT - SHOULD SUCCEED
TEST_CASE(calculations3,{
     questionnaire test;
     test.weight = 300;
     test.pushups = 5;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,162.5,0.001);
})

//TESTS FOR THE HIGHEST POSSIBLE WEIGHT - SHOULD SUCCEED
TEST_CASE(calculations4,{
     questionnaire test;
     test.weight = 65;
     test.pushups = 5000000;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,55,0.001);
})
//EDGECASES!

#pragma endregion

TEST_CASE(upgrade_test,{
    questionnaire user_test = {67,"male",65,183,5,12,1,{monday,67},{1,1,1,1,1}};
    exercise ex_test[length_of_exercises_list];
    resistance_exercises_list(ex_test, user_test);
    aerobic_exercises_list(ex_test,user_test);
    print_exercises_2(ex_test,7,user_test,ex_test);
    int input[] = {1,1,0,0,1,0,1};
    CHECK_EQ_DOUBLE(ex_test[0].base_weight,35,0.001);
    CHECK_EQ_DOUBLE(ex_test[1].base_weight,40,0.001);
    CHECK_EQ_DOUBLE(ex_test[2].amount_of_reps,14,0.001);
    CHECK_EQ_DOUBLE(ex_test[3].amount_of_reps,14,0.001);
    CHECK_EQ_DOUBLE(ex_test[4].amount_of_reps,14,0.001);
    CHECK_EQ_DOUBLE(ex_test[5].amount_of_reps,13,0.001);
    CHECK_EQ_DOUBLE(ex_test[6].amount_of_reps,14,0.001);

    upgrade_function(ex_test,user_test,length_of_exercises_list,input);

    CHECK_EQ_DOUBLE(ex_test[0].base_weight,37.5,0.001);
    CHECK_EQ_DOUBLE(ex_test[1].base_weight,42.5,0.001);
    CHECK_EQ_DOUBLE(ex_test[2].amount_of_reps,14,0.001);
    CHECK_EQ_DOUBLE(ex_test[3].amount_of_reps,14,0.001);
    CHECK_EQ_DOUBLE(ex_test[4].amount_of_reps,15,0.001);
    CHECK_EQ_DOUBLE(ex_test[5].amount_of_reps,13,0.001);
    CHECK_EQ_DOUBLE(ex_test[6].amount_of_reps,16,0.001);
})

MAIN_RUN_TESTS(calculations,calculations2,calculations3,calculations4)

/*Testing af Jespers ting*/
/*Update routine workout*/

