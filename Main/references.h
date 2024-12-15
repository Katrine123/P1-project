
// Data

#pragma region macros

// General constants
#define ARRAY_MAX 32 // 32 simply because it is big enough.

#pragma endregion
#pragma region enums

typedef enum {
    integer, character, long_float, string
} data_type;

enum fitness_level {
    novice = 5, advanced_beginner = 4, competent = 3, proficient = 2, expert = 1
};
enum equipment {
    barbell, bench, pull_up_bar, pull_down_machine, resistance_bands
};
// TODO: Add in design that the software is proof-of-concept and that's why we do not include that many exercises.
// TODO: Is length_of_exercises_list a good idea?
enum exercise_name {
    bench_press, weighted_squat, air_squat, pushup, elevated_pushup, burpees, jumping_jacks
};
enum day_of_the_week {
    monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday
};
// TODO: Add in implementation that we define muscle groups in very broad terms (overly simplified).
// TODO: Add in design that our program does not take into consideration how much an exercise targets each muscle (some muscles are worked harder than others in some exercises).
typedef enum {
    chest, triceps, shoulders, hamstrings, quads
} muscle_group_name;

#pragma endregion
#pragma region structs

typedef struct {
    enum day_of_the_week day;
    double max_duration;
}training_day;

typedef struct {
    double weight;
    int pushups;
    int squats;
    enum fitness_level _fitness_level;
    training_day available_training_days[7]; int available_training_days_count;
    enum equipment available_equipment[ARRAY_MAX]; int available_equipment_count;
    muscle_group_name ignored_muscle_group_names[ARRAY_MAX]; int ignored_muscle_group_names_count;
} questionnaire;

typedef struct muscle_group {
    muscle_group_name name;
    struct muscle_group* parent; // Muscle groups in struct exercise refer to muscle groups in struct workout which refers to muscle groups in the global routine variable.
    int sets; // Irrelevant for struct exercise, is daily sets for struct workout, and is weekly sets for the global routine variable.
} muscle_group;

//  Exercise platform for resistance exercises
typedef struct {
    enum exercise_name name;
   //  We assume that weight only increases by 2.5, argue for this in implementation/design
    double addition;
    double base_weight;
    int reps;
    int is_body_weight_exercise;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups targeted by the exercise. Aerobic exercises do not target any specific muscles.
    int sets;
    double rep_duration; // In minutes. How long it takes to perform 1 set of the exercise.
    int is_aerobic; // Is boolean.
    double specific_warmup_duration; // In minutes. Only relevant for resistance training exercises.
} exercise;
typedef struct {
    exercise exercises[ARRAY_MAX]; int exercises_count;
    double duration; double max_duration;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups included in the workout.
    enum day_of_the_week day;
} workout;

#pragma endregion
#pragma region global variables

extern int all_equipment_count;
extern enum equipment all_equipment[ARRAY_MAX];
extern int all_muscle_names_count;
extern muscle_group_name all_muscle_names[ARRAY_MAX];

extern questionnaire _questionnaire;
// TODO: Only implemented in exercises.c.
extern exercise possible_resistance_exercises[ARRAY_MAX];
extern int possible_resistance_exercises_count;
// TODO: Only implemented in exercises.c.
extern exercise possible_aerobic_exercises[ARRAY_MAX];
extern int possible_aerobic_exercises_count;
extern workout routine_workouts[7];
extern int routine_workouts_count;

// Workout rules
extern const int general_warmup_duration;
extern const int max_daily_sets;
extern const int max_daily_aerobic_exercises;
extern const double rest_between_sets_resistance;
extern double aerobic_rest_multiplier;
extern int max_weekly_sets;
extern int resistance_recovery;
extern int max_weekly_aerobic_workouts;

#pragma endregion

// Functions

#pragma region references.c

void update_and_print_routine();

#pragma endregion
#pragma region tools.c

int homemade_scan(data_type type, void* input);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);
char* naming_muscle_group(muscle_group_name name);
char* naming_exercises(enum exercise_name name);
char* naming_fitness_level(enum fitness_level name);

#pragma endregion
#pragma region new_user_questionnaire.c

void update_questionnaire();

#pragma endregion
#pragma region exercises.c

void update_possible_exercises();

#pragma endregion
#pragma region workouts.c

void update_routine_workouts();

#pragma endregion
#pragma region print_routine.c

void print_routine();

#pragma endregion
#pragma region savesystem.c


#pragma endregion
#pragma region evaluation_questionnaire.c

int evaluation_questionnaire();

#pragma endregion
#pragma region upgrade_downgrade.c

#pragma endregion



