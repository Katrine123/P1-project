
enum datatype {integer, character, long_float, string};
typedef enum datatype datatype;

//  Stages from problem analysis
enum stage_base_factor { novice = 5, advanced_beginner = 4, competent = 3, proficient = 2, expert = 1 };
enum equipment { barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, length_of_equipment_enum };
enum exercises {bench_press, weighted_squats, air_squats, pushups, elevated_pushups, burpees, jumping_jacks, length_of_exercises_list};
enum day_of_the_week {
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6,
    sunday = 7
};


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

//  Check equipment struct
typedef struct {
    int barbell;
    int bench;
    int pull_up_bar;
    int pull_down_machine;
    int resistance_bands;
} check_equipment;

//  Exercise platform for resistance exercises
typedef struct {
    char name[20];
    //  When calling necessary_equipment.x it searches in the check_equipment struct
    int check_eq[length_of_exercises_list];
    //  We assume that weight only increases by 2.5, argue for this in implementation/design
    double addition;
    double base_weight;
    int amount_of_reps;
} exercise;


int homemade_scan(datatype type, void* input);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);

exercise* create_available_exercises(exercise exercises_list[], questionnaire user_questionnaire, int *count);

questionnaire create_and_answer_questionnaire();

void print_quiestionnare(questionnaire user);

double base_weight_bench_press(questionnaire user);
double base_weight_weighted_squats(questionnaire user);
double base_amount_air_squats(questionnaire user);
int base_amount_pushups(questionnaire user);
int base_amount_elevated_pushups(questionnaire user);
double base_amount_burpees(questionnaire user);
double base_amount_jumping_jacks(questionnaire user);
void resistance_exercises_list(exercise* exercise_list, questionnaire user);
void aerobic_exercises_list(exercise* exercise_list, questionnaire user);

exercise* create_all_exercises();
void print_exercise(exercise exercises_list[]);
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user, exercise exercises_list[]);
void upgrade_downgrade(exercise *exercise_list_sorted, int sorted_count, int *input);
exercise* upgrade_function(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int input[]);
//
// Created by mwsan on 11/14/2024.
//

#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

int check_for_save();

int save_data();

void load_data();

#endif //SAVESYSTEM_H



