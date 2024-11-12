
enum equipment { nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands };

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

questionnaire create_and_answer_questionaire();


