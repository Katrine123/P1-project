#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

#define EXERCISES_ARRAY_MAX 32

//Print reps, sets vægt og navn
typedef struct {
    exercise exercises[EXERCISES_ARRAY_MAX]; //struct array of exercises for 1 day
    int exercises_count; //How many exercises in a day
    double duration; // In minutes.
    double max_duration; // In minutes.
    enum day_of_the_week day; //What day is it.
} workout;

void creating_test(workout* test_example);

void print_routine() {
    workout test_example1,test_example2,test_example3;
    creating_test(&test_example1);
    creating_test(&test_example2);
    creating_test(&test_example3);
    workout arr[3];
    arr[0] = test_example1;
    arr[1] = test_example2;
    arr[2] = test_example3;

    //ACTUAL PRINTING STARTS HERE
    printf("____________________________________________________________\n");
    printf("______________________________\n");
    for(int i = 0; i<3;i++) {
        printf("Day %d: %s\n",i+1,naming_days(arr[i].day));
        printf("Workout duration: %lf minutes\n",arr[i].duration);
        printf("Workout max duration: %lf minutes\n",arr[i].max_duration);
        for(int j = 0; j<arr[j].exercises_count;j++) {
            printf("    Exercise %d: %s\n",j+1,arr[i].exercises[j].name);
            printf("    Weight: %lf\n",j+1,arr[i].exercises[j].base_weight);
            printf("    Reps: %lf\n\n",j+1,arr[i].exercises[j].amount_of_reps);

            //Tilføj reps og vægt
            //Print instructions
        }
        printf("______________________________\n");
    }
    printf("____________________________________________________________\n");


}

void creating_test(workout* test_example) {
    //Indsætter exercises for at teste:
    exercise bench_press = {"Bench press", {0, 1, 1, 0, 0}, 2.5, 34, 12};
    exercise weighted_squats = {"Weighted squats", {0, 1, 0, 0, 0}, 2.5, 56, 12};
    //////////////////////
    test_example->day = monday;
    test_example->duration =23;
    test_example->max_duration = 30;
    test_example->exercises[0] = bench_press;
    test_example->exercises[1] = weighted_squats;
    test_example->exercises_count = 2;
}

