#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h"
#include "references.c"

/*#pragma region questionnaire
TEST_CASE(questionnaire_test1,{
    //Making "User inputs"
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67\n72\n6 \n8 \n1\n2\n4 \n-1 \n120\nYes\n3\n-1\n");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    user_data user_test;
    update_questionnaire(&user_test, test_file);
    fclose(test_file);
    CHECK_EQ_DOUBLE(user_test.weight,72,0.001);
    CHECK_EQ_INT(user_test.pushups,6);
    CHECK_EQ_INT(user_test.squats,8);
    CHECK_EQ_INT(user_test._fitness_level,1);
    CHECK_EQ_INT(user_test.available_training_days[0].day,thursday); //FIKS?
    CHECK_EQ_DOUBLE(user_test.available_training_days[0].max_duration,120,0.001);
    for(int i = 0; i<user_test.available_equipment_count;i++) {
        CHECK_EQ_INT(user_test.available_equipment[i],i);
    }
    CHECK_EQ_INT(user_test.ignored_muscle_group_names[0],shoulders); //FIKS?
})

//IS SUPPOSED TO SUCCEED
TEST_CASE(questionnaire_test2,{
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"age\n67\n0\n58\n-1\n25\n5000000\n-1\n6\n3\n-2\n 8\n2\n-5\n999\n2\n3\n-1\n3000\n68\n23\nNo\n-5\n0\n800\n4\n3\n-1\n-5\n0\n1\n1\n-1\n-1");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    user_data user_test;
    update_questionnaire(&user_test,test_file);
    fclose(test_file);
    CHECK_EQ_DOUBLE(user_test.weight,58,0.001);
    CHECK_EQ_INT(user_test.pushups,25);
    CHECK_EQ_INT(user_test.squats,5000000);
    CHECK_EQ_INT(user_test._fitness_level,3);
    CHECK_EQ_INT(user_test.available_training_days[0].day,tuesday);
    CHECK_EQ_INT(user_test.available_training_days[1].day,wednesday);
    CHECK_EQ_DOUBLE(user_test.available_training_days[0].max_duration,68,0.001);
    CHECK_EQ_DOUBLE(user_test.available_training_days[1].max_duration,-23,0.001);
    CHECK_EQ_INT(user_test.available_equipment[0],0);
    CHECK_EQ_INT(user_test.available_equipment[1],0);
    CHECK_EQ_INT(user_test.available_equipment[2],1);
    CHECK_EQ_INT(user_test.available_equipment[3],1);
    CHECK_EQ_INT(user_test.available_equipment[4],0);
    CHECK_EQ_INT(user_test.ignored_muscle_group_names[0],0);
})

#pragma endregion
*/
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

#pragma region calculations

TEST_CASE(calculations,{
    user_data user_test;
    user_test.weight = 65;
    user_test.pushups = 5;
    double test_value = base_weight_bench_press(&user_test);
    CHECK_EQ_DOUBLE(test_value,35,0.001);
})

//IS SUPPOSED TO SUCCEED - LOWEST POSSIBLE WEIGHT FROM THE QUESTIONNAIRE
TEST_CASE(calculations2,{
    user_data user_test;
    user_test.weight = 20;
    user_test.pushups = 5;
    double test_value = base_weight_bench_press(&user_test);
    CHECK_EQ_DOUBLE(test_value,10,0.001);
})

//TESTS FOR THE HIGHEST POSSIBLE WEIGHT - SHOULD SUCCEED
TEST_CASE(calculations3,{
    user_data user_test;
     user_test.weight = 300;
     user_test.pushups = 5;
     double test_value = base_weight_bench_press(&user_test);
     CHECK_EQ_DOUBLE(test_value,162.5,0.001);
})

//TESTS FOR A LOT OF PUSHUPS - SHOULD SUCCEED
TEST_CASE(calculations4,{
    user_data user_test;
     user_test.weight = 65;
     user_test.pushups = 5000000;
     double test_value = base_weight_bench_press(&user_test);
     CHECK_EQ_DOUBLE(test_value,55,0.001);
})

//TESTS FOR THE LOWEST AMOUNT OF PUSHUPS - SHOULD SUCCEED
TEST_CASE(calculations5,{
    user_data user_test;
     user_test.weight = 65;
     user_test.pushups = 0;
     double test_value = base_weight_bench_press(&user_test);
     CHECK_EQ_DOUBLE(test_value,30,0.001);
})

//TESTS FOR -1 - SHOULD SUCCEED
TEST_CASE(calculations6,{
    user_data user_test;
     user_test.weight = -1;
     user_test.pushups = -1;
     double test_value = base_weight_bench_press(&user_test);
     CHECK_EQ_DOUBLE(test_value,-1,0.001);
})

#pragma endregion

#pragma region base_amount

TEST_CASE(base_amount1,{
    user_data user_test;
        user_test._fitness_level = proficient;
        user_test.pushups = 25;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})

TEST_CASE(base_amount2,{
    user_data user_test;
        user_test._fitness_level = expert;
        user_test.pushups = 25;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})

TEST_CASE(base_amount3,{
    user_data user_test;
        user_test._fitness_level = novice;
        user_test.pushups = 25;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})

TEST_CASE(base_amount4,{
    user_data user_test;
        user_test._fitness_level = proficient;
        user_test.pushups = 0;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})

TEST_CASE(base_amount5,{
    user_data user_test;
        user_test._fitness_level = proficient;
        user_test.pushups = 5000000;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})

TEST_CASE(base_amount6,{
    user_data user_test;
        user_test._fitness_level = -1;
        user_test.pushups = -1;
        int test_value = base_amount_calculation(&user_test,user_test.pushups);
        CHECK_EQ_INT(test_value,58);
})


#pragma endregion
/*
#pragma region upgrade
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

#pragma endregion
*/
#pragma region workouts

//SUPPOSED TO FAIL - NOT ALL EXERCISES ARE USED
TEST_CASE(workouts_test,{
    //Making "User inputs"
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67\n72\n6 \n8 \n1\n2\n4 \n-1 \n120\nYes\n3\n-1\n");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    user_data user_test;
    update_questionnaire(&user_test,test_file);
    fclose(test_file);
    update_possible_exercises(&user_test);
    update_routine_workouts(&user_test);
    CHECK_EQ_INT(user_test.routine_workouts[0].exercises_count,5);//There should be enough time for a full workout
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles_count,3); //Is three because only three muscles are used
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[0].name,chest);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[1].name,triceps);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[2].name,shoulders);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[3].name,quads);
    CHECK_EQ_DOUBLE(user_test.routine_workouts[0].max_duration,120,0.001);
    CHECK_EQ_DOUBLE(user_test.routine_workouts[0].duration,119.9333,0.001);
    CHECK_EQ_INT(user_test.routine_workouts[0].day,friday);
})

TEST_CASE(workouts_test2,{
    //Making "User inputs"
    FILE *test_file = fopen("user_input.txt","w");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    fprintf(test_file,"67\n72\n6 \n8 \n1\n2\n4 \n-1 \n120\nYes\n3\n-1\n");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    user_data user_test;
    update_questionnaire(&user_test,test_file);
    fclose(test_file);
    update_possible_exercises(&user_test);
    update_routine_workouts(&user_test);
    CHECK_EQ_INT(user_test.routine_workouts[0].exercises_count,5);//There should be enough time for a full workout
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles_count,3); //Is three because only three muscles are used
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[0].name,chest);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[1].name,triceps);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[2].name,shoulders);
    CHECK_EQ_INT(user_test.routine_workouts[0].muscles[3].name,quads);
    CHECK_EQ_DOUBLE(user_test.routine_workouts[0].max_duration,120,0.001);
    CHECK_EQ_DOUBLE(user_test.routine_workouts[0].duration,119.9333,0.001);
    CHECK_EQ_INT(user_test.routine_workouts[0].day,friday);
})

#pragma endregion


// X SUPPOSED TO FAIL - X SUPPOSED TO SUCCEED
//MAIN_RUN_TESTS(questionnaire_test1,questionnaire_test2)
//MAIN_RUN_TESTS(homemade_scan_test,homemade_scan_test2);
//MAIN_RUN_TESTS(calculations,calculations2,calculations3,calculations4,calculations5,calculations6)
//MAIN_RUN_TESTS(upgrade_test)
//MAIN_RUN_TESTS(workouts_test,workouts_test2)
MAIN_RUN_TESTS(base_amount1, base_amount2, base_amount3, base_amount4, base_amount5, base_amount6)