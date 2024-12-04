#include <stdlib.h>

#include "tools.h"
#include "routine.h"


exercise* create_available_exercises(exercise* all_exercises, questionnaire user_questionnaire) {
    // Sorter de exercises fra, som brugeren ikke kan udføre pga. udstyr
    exercise* sorted_exercise_list = (exercise *)malloc (sizeof(10*sizeof(exercise)));
    int count=0;

    for (int n=0; n<(10); n++) { // loop to cycle through exercise list
        int fail_switch = 0;
        for (int i=0; i<4; i++) { // Loop to cycle through exercise equipment also "length_of_equipment_enumn" instead of 4
            if (all_exercises[n].check_eq[i]>user_questionnaire.available_equipment[i]) { // Checks all exercises equipment against user equipment, user.equipment might not be correct name
                fail_switch = 1;
                break;
            }
        }
        if (fail_switch==0) { // checks if fail_switch fails if not exercise is added to new list of viable exercises
            sorted_exercise_list[count] = all_exercises[n]; // creates new list of sorted_exercise list
            count++;
        }
    }
    return sorted_exercise_list;
}