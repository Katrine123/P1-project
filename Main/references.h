
// Data

#pragma region macros

// General constants
#define ARRAY_MAX 32 // 32 simply because it is big enough.

#pragma endregion
#pragma region enums

typedef enum {
    integer, character, long_float, string
} datatype;

//TODO: Rename to fitness level
enum stage_base_factor {
    novice = 5, advanced_beginner = 4, competent = 3, proficient = 2, expert = 1
};
enum equipment {
    barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, length_of_equipment_enum
};
// TODO: Rename to exercise_name
enum exercises {
    bench_press, weighted_squats, air_squats, pushups, elevated_pushups, burpees, jumping_jacks, length_of_exercises_list
};
enum day_of_the_week {
    monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday
};
// TODO: Not implemented yet.
typedef enum {
    calves, biceps, chest, triceps, quads
} muscle_group_name;

#pragma endregion
#pragma region structs

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
    enum stage_base_factor fitness_level;
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
    double amount_of_reps;
    int is_body_weight_exercise;
} exercise;

// TODO: Not implemented yet.
 typedef struct muscle_group {
     muscle_group_name name;
     struct muscle_group* parent; // Muscle groups in struct exercise refer to muscle groups in struct workout which refers to muscle groups in the global routine variable.
     int sets; // Irrelevant for struct exercise, is daily sets for struct workout, and is weekly sets for the global routine variable.
 } muscle_group;
// TODO: Not implemented yet.
 typedef struct {
     exercise_name name;
     muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups targeted by the exercise. Aerobic exercises do not target any specific muscles.
     int sets;
     double set_duration; // In minutes. How long it takes to perform 1 set of the exercise.
     int is_aerobic; // Is boolean.
     double specific_warmup_duration; // In minutes. Only relevant for resistance training exercises.
 } exercise;
// TODO: Not implemented yet.
 typedef struct {
     day_of_the_week _day_of_the_week;
     double max_duration; // In minutes.
 } workout_day;
// TODO: Not implemented yet.
 typedef struct  {
     enum stage_base_factor fitness_level;
     muscle_group_name ignored_muscle_group_names[ARRAY_MAX]; int ignored_muscle_group_names_count;
     workout_day available_workout_days[7]; int available_workout_days_count;
 } _questionnaire;

#pragma endregion
#pragma region global variables

// TODO: Not implemented yet.
questionnaire _questionnaire;
// TODO: Not implemented yet.
muscle_group_name all_muscle_names[ARRAY_MAX]; int all_muscle_names_count;
// TODO: Not implemented yet.
exercise valid_resistance_exercises[ARRAY_MAX]; int valid_resistance_exercises_count;
// TODO: Not implemented yet.
exercise valid_aerobic_exercises[ARRAY_MAX]; int valid_aerobic_exercises_count;

#pragma endregion

// Functions

#pragma region evaluation_questionnaire.c

int evaluation_questionnaire();

#pragma endregion
#pragma region exercises.c

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
void print_exercise(exercise exercises_list[]);
void print_exercises_2(exercise sorted_exercise_list[], int count, questionnaire user, exercise exercises_list[]);

#pragma endregion
#pragma region new_user_questionnaire.c

questionnaire create_and_answer_questionnaire();
void print_quiestionnare(questionnaire user);
int get_user_days(questionnaire* user);

#pragma endregion
#pragma region print_routine.c

void print_routine();

#pragma endregion
#pragma region savesystem.c

int check_for_save();
int save_data();
void user_save();
void print_user_data();
questionnaire load_data();

#pragma endregion
#pragma region tools.c

int homemade_scan(datatype type, void* input);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);

#pragma endregion
#pragma region upgrade_downgrade.c

void upgrade_downgrade(exercise *exercise_list_sorted, int sorted_count, int *input);
void upgrade_function(exercise *exercise_list_sorted, questionnaire user, int sorted_count, int input[]);

#pragma endregion



