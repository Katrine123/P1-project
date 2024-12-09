#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h" //HUSK KILDE
#include "tools.h"

TEST_CASE(questionnaire_test1,{
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

MAIN_RUN_TESTS(questionnaire_test1,questionnaire_test2)

/*What to test:
 * Sorting algoritm
 * Upgrade/Downgrade
 * Calculations for exercises?
 * Print questionnaire?
 */


