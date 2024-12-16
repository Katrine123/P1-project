#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h"
#include "references.h"

#pragma region questionnaire
TEST_CASE(questionnaire_test1,{
    //Making "User inputs"
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67\n72 \n6 \n8 \n1 \n4 \n-1 \n120\nYes\n3\n-1\n-1");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    update_questionnaire();
    fclose(test_file);
    CHECK_EQ_INT(_questionnaire.age,67);
    CHECK_EQ_DOUBLE(_questionnaire.weight,72,0.001);
    CHECK_EQ_INT(_questionnaire.pushups,6);
    CHECK_EQ_INT(_questionnaire.squats,8);
    CHECK_EQ_INT(_questionnaire._fitness_level,1);
    CHECK_EQ_INT(_questionnaire.training_days[0].day_week,thursday);
    CHECK_EQ_DOUBLE(_questionnaire.training_days[0].available_time,120,0.001);
    for(int i = 0; i<length_of_equipment_enum;i++) {
        CHECK_EQ_INT(_questionnaire.available_equipment[i],1);
    }
    CHECK_EQ_INT(user_test.ignored_muscle_group_names[0],2);
})

//IS SUPPOSED TO SUCCEED
TEST_CASE(questionnaire_test2,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"age\n67\n0\n58\n-1\n25\n5000000\n-1\n6\n3\n-5\n999\n2\n3\n-1\n3000\n68\n-23\nNo\n-5\n0\n800\n4\n3\n-1\n-5\n0\n1\n1\n-1\n-1");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    questionnaire user_test = create_and_answer_questionnaire(test_file);
    fclose(test_file);
    CHECK_EQ_INT(user_test.age,67);
    CHECK_EQ_DOUBLE(user_test.weight,58,0.001);
    CHECK_EQ_INT(user_test.pushups,25);
    CHECK_EQ_INT(user_test.squats,5000000);
    CHECK_EQ_INT(user_test.fitness_level,3);
    CHECK_EQ_INT(user_test.training_days[0].day_week,tuesday);
    CHECK_EQ_INT(user_test.training_days[1].day_week,wednesday);
    CHECK_EQ_DOUBLE(user_test.training_days[0].available_time,68,0.001);
    CHECK_EQ_DOUBLE(user_test.training_days[1].available_time,-23,0.001);
    CHECK_EQ_INT(user_test.available_equipment[0],0);
    CHECK_EQ_INT(user_test.available_equipment[1],0);
    CHECK_EQ_INT(user_test.available_equipment[2],1);
    CHECK_EQ_INT(user_test.available_equipment[3],1);
    CHECK_EQ_INT(user_test.available_equipment[4],0);
    CHECK_EQ_INT(user_test.ignored_muscle_group_names[0],0);
})

#pragma endregion

#pragma region homemade_scan
TEST_CASE(homemade_scan_test,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"\n45 \nh \nhej \n87.5 \n");
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
    CHECK_EQ_STRING(string_test,"hej");
    double double_test;
    homemade_scan(long_float,&double_test,test_file);
    CHECK_EQ_DOUBLE(double_test,87.5,0.001);
    fclose(test_file);
})

//THIS TEST WHAT HAPPENS IF YOU INPUT THE WRONG DATATYPE
//IT SHOULD SUCCEED BUT SHOULD ALSO PRINT SOME THINGS
TEST_CASE(homemade_scan_test2,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"\nhej \n45 \n45 \nh \n45 \nhej \nhej \n87.5 \n");
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
    CHECK_EQ_STRING(string_test,"hej");
    double double_test;
    homemade_scan(long_float,&double_test,test_file);
    CHECK_EQ_DOUBLE(double_test,87.5,0.001);
})
#pragma endregion

#pragma region sorting_exercises
//TEST THAT YOU ONLY GET THE EXERCISES NEEDING NO EQUIPMENT - IS SUPPOSED TO SUCCEED
TEST_CASE(sorting_exercises_test,{
    questionnaire test = {67,72,7,12,1,{monday,67},{0,0,0,0,0}};
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
    questionnaire test = {67,72,7,12,1,{monday,67},{1,1,1,1,1}};
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
    questionnaire test = {67,72,7,12,1,{monday,67},{-1,1,1,1,1}};
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
    test.weight = 20;
    test.pushups = 5;
    double test_value = base_weight_bench_press(test);
    CHECK_EQ_DOUBLE(test_value,10,0.001);
})

//TESTS FOR THE HIGHEST POSSIBLE WEIGHT - SHOULD SUCCEED
TEST_CASE(calculations3,{
     questionnaire test;
     test.weight = 300;
     test.pushups = 5;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,162.5,0.001);
})

//TESTS FOR A LOT OF PUSHUPS - SHOULD SUCCEED
TEST_CASE(calculations4,{
     questionnaire test;
     test.weight = 65;
     test.pushups = 5000000;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,55,0.001);
})

//TESTS FOR THE LOWEST AMOUNT OF PUSHUPS - SHOULD SUCCEED
TEST_CASE(calculations5,{
     questionnaire test;
     test.weight = 65;
     test.pushups = 0;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,30,0.001);
})

//TESTS FOR -1 - SHOULD SUCCEED
TEST_CASE(calculations6,{
     questionnaire test;
     test.weight = -1;
     test.pushups = -1;
     double test_value = base_weight_bench_press(test);
     CHECK_EQ_DOUBLE(test_value,-1,0.001);
})

#pragma endregion

#pragma region upgrade
TEST_CASE(upgrade_test,{
    questionnaire user_test = {67,65,5,12,1,{monday,67},{1,1,1,1,1}};
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

#pragma endregion

#pragma region workouts
TEST_CASE(workouts_test,{
    //update_routine_workouts(exercises, user_questionnaire);
})
#pragma endregion

// X SUPPOSED TO FAIL - X SUPPOSED TO SUCCEED
//MAIN_RUN_TESTS(questionnaire_test1,questionnaire_test2)
MAIN_RUN_TESTS(homemade_scan_test,homemade_scan_test2);
//MAIN_RUN_TESTS(sorting_exercises_test,sorting_exercises_test2,sorting_exercises_test3)
//MAIN_RUN_TESTS(calculations,calculations2,calculations3,calculations4,calculations5,calculations6)
//MAIN_RUN_TESTS(upgrade_test)

