
enum datatype {integer, character, long_float, string};
typedef enum datatype datatype;

//  Stages from problem analysis
enum stage_base_factor { novice = 5, advanced_beginner = 4, competent = 3, proficient = 2, expert = 1 };
enum equipment {barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, length_of_equipment_enum };
enum exercises {bench_press, weighted_squats, air_squats, pushups, elevated_pushups, burpees, length_of_exercises_list};
enum day_of_the_week {
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6,
    sunday = 7
};

// nothing, barbell, bench, pull_up_bar, pull_down_machine, resistance_bands
typedef struct {
    int nothing;
    int barbell;
    int bench;
    int pull_up_bar;
    int pull_down_machine;
    int resistance_bands;
} check_equipment;

//  Exercise platform
typedef struct {
    char name[20];
    //  When calling necessary_equipment.x it searches in the check_equipment struct
    //  Kald på array her, ændr type
    int check_eq[length_of_exercises_list - 1];
    //  We assume that weight only increases by 2.5, argue for this in implementation/design
    double addition;
    double base_weight;
    int amount_of_reps;
} exercise;

typedef struct {
    enum day_of_the_week day_week;
    double available_time;
}training_day;

typedef struct {
    int age;
    char gender[20];
    double weight;
    double height;
    int pushups;
    int squats;
    int fitness_level;
    training_day training_days[7];
    int available_equipment[5]; //Array for deciding what exercises they can do
} questionnaire;

//// ALL FUNCTIONS HERE ////

//  In evaluation_questionnaire.c  //

int evaluation_questionnaire(questionnaire* user);

//  In exercises.c  //

void exercises_list();

//Skal måske ikke være her?
double base_weight_bench_press(double body_weight_pushups, double rep_max_pushup);
double base_weight_weighted_squats(double body_weight, double rep_max_pushup);
double base_amount_air_squats(double rep_max_squats);
int base_amount_pushups(double rep_max_pushup);
int base_amount_elevated_pushups(double rep_max_pushup);
double base_amount_own_exercise_lower_body(double rep_max_squats);
double base_amount_own_exercise_upper_front_body(double rep_max_pushups);
double base_amount_burpees(double rep_max_squats);
double base_amount_jumping_jacks(double rep_max_squats);

void print_exercise(exercise exercises_list[]);

//  In list.c  //

//  In new_user_questionnaire.c  //

questionnaire create_and_answer_questionnaire();
int get_user_days(questionnaire* user);
void print_quiestionnare(questionnaire user);

//  In print_routine.c  //
void print_routine();

//  In routine.c  //
exercise* create_available_exercises(exercise* all_exercises, questionnaire user_questionnaire);

//  In savesystem.c  //

#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

int check_for_save();

int save_data();

void load_data();

#endif //SAVESYSTEM_H

//  In tools.c  //

int homemade_scan(datatype type, void* input);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);


//Fjern?
exercise* create_all_exercises();







