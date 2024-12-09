#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtest.h" //HUSK KILDE
#include "tools.h"

TEST_CASE(questionnaire_test1,{
    FILE *test_file = fopen("user_input.txt","r");
        if (test_file == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    questionnaire user_test = create_and_answer_questionnaire(test_file);
    fclose(test_file);
})

TEST_CASE(questionnaire_test2,{
    FILE *test_file2 = fopen("user_input2.txt","r");
        if (test_file2 == NULL) {
            printf("The file couldn't be opened");
            exit(-1);
        }
    questionnaire user_test = create_and_answer_questionnaire(test_file2);
    fclose(test_file2);
})

MAIN_RUN_TESTS(questionnaire_test1,questionnaire_test2)

/*int main(void) {
    FILE *test_file = fopen("user_input.txt","w");
    if (test_file == NULL) {
        printf("The file couldn't be opened");
        exit(-1);
    }
    fprintf(test_file, "67 male 72 183 6 8 1 4 -1 120 Yes\n");
    fclose(test_file);
    test_file = fopen("user_input.txt","r");
    if (test_file == NULL) {
        printf("The file couldn't be opened");
        exit(-1);
    }

    questionnaire user_test = create_and_answer_questionnaire(test_file);
    //Shit works, so now actually test stuff
    assert(user_test.age == 67);
    assert(strcmp(user_test.gender,"male")==0);
    assert(user_test.weight == 72);
    assert(user_test.height == 183);
    assert(user_test.pushups == 6);
    assert(user_test.squats == 8);
    assert(user_test.fitness_level == 1);
    assert(user_test.training_days->day_week == thursday);
    assert(user_test.training_days->available_time == 120);

    assert(test(4,5)==9);
    fclose(test_file);
    return 0;
}*/

/*Anything with scanf is hard af to test*/

/*What to test:
 * Sorting algoritm
 * Upgrade/Downgrade
 * Calculations for exercises?
 * Print questionnaire?
 */


