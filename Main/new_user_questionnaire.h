#include "tools.h"

typedef struct {
    int age;
    char gender[20];
    double weight;
    double height;
    int pushups;
    int fitness_level;
    double time_available_week;
    int available_equipment[5]; //Array for deciding what exercises they can do
} questionnaire;


questionnaire create_and_answer_questionnaire();

void print_quiestionnare(questionnaire user);


