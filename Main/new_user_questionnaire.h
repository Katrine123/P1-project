#include "tools.h"

typedef struct {
    enum equipment available_equipment[50];

    int age;
    char gender[20];
    double weight;
    double height;
    int pushups;
    int fitness_level;
    double time_available_week;
} questionnaire;

typedef struct {
    int barbell;
    int bench;
    int pull_up_bar;
    int pull_down_machine;
    int resistance_bands;
} check_equipment;


questionnaire create_and_answer_questionaire();


