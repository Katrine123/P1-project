#include "tools.h"

typedef struct {
    int age;
    char gender[20];
    double weight;
    double height;
    int pushups;
    int fitness_level;
    double time_available_week;
    enum equipment available_equipment[5];
} questionnaire;


questionnaire create_and_answer_questionnaire();

void print_quiestionnare(questionnaire user);


