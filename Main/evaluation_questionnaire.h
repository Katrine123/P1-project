#include "tools.h"

typedef struct {
    enum equipment available_equipment[5];

    int age;
    char gender[20];
    double weight;
    double height;
    int pushups;
    int fitness_level;
    double time_available_week;
} questionnaire;




questionnaire create_and_answer_questionnaire();