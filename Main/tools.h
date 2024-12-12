#include <stdio.h>

#define ARRAY_MAX 32

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

typedef enum {
    chest, triceps, shoulders, hamstrings, quads
} muscle_group_name;

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
    muscle_group_name ignored_muscle_group_names[ARRAY_MAX]; int ignored_muscle_group_names_count;
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
    double amount_of_reps;
    int is_body_weight_exercise;
} exercise;

//// ALL FUNCTIONS HERE ////

//  In evaluation_questionnaire.c  //

int evaluation_questionnaire(questionnaire* user,FILE *file);

//  In exercises.c  //

exercise* create_available_exercises(exercise exercises_list[], questionnaire user_questionnaire, int *count);

double base_weight_bench_press(questionnaire user);
double base_weight_weighted_squats(questionnaire user);
int base_amount_air_squats(questionnaire user);
int base_amount_pushups(questionnaire user);
int base_amount_elevated_pushups(questionnaire user);
int base_amount_burpees(questionnaire user);
int base_amount_jumping_jacks(questionnaire user);
void resistance_exercises_list(exercise* exercise_list, questionnaire user);
void aerobic_exercises_list(exercise* exercise_list, questionnaire user);

exercise* create_all_exercises();
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user, exercise exercises_list[]);

//  In list.c  //

//  In new_user_questionnaire.c  //

questionnaire create_and_answer_questionnaire(FILE *file);
int get_user_days(questionnaire* user,FILE *file);
void print_quiestionnare(questionnaire user);
int get_user_days(questionnaire* user,FILE *file);

//  In print_routine.c  //
void print_routine();

//  In routine.c  //

//  In savesystem.c  //

#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

int check_for_save();

int save_data();

void load_data();

#endif //SAVESYSTEM_H

//  In tools.c  //

int homemade_scan(datatype type, void* input,FILE *file);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);
char* naming_muscles(muscle_group_name muscle);

//  In upgrade_downgrade.c  //

void upgrade_downgrade(exercise *exercise_list_sorted,questionnaire user, int sorted_count);
void upgrade_function(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int input[]);





