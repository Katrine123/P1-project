
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

enum training_goal_e { MUSCULAR_ENDURANCE = 1, HYPERTROPHY = 2, STRENGTH = 3, I_DONT_KNOW = 4 };

enum equipment {
    barbell, bench, pull_up_bar, pull_down_machine, resistance_bands, equipment_enum_length
};
enum exercise_name {
    bench_press, weighted_squat, air_squat, pushup, elevated_pushup, burpees, jumping_jacks, length_of_exercise_enum
};
enum day_of_the_week {
    monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday
};
typedef enum {
    chest, triceps, shoulders, hamstrings, quads, muscle_group_name_enum_length
} muscle_group_name;

#pragma endregion
#pragma region structs

typedef struct {
    enum day_of_the_week day;
    double max_duration;
}training_day;

typedef struct muscle_group {
    muscle_group_name name;
    struct muscle_group* parent; // Muscle groups in struct exercise refer to muscle groups in struct workout which refers to muscle groups in the global routine variable.
    int sets; // Irrelevant for struct exercise, is daily sets for struct workout, and is weekly sets for the global routine variable.
} muscle_group;

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
    int counter_upgrade_downgrade;
} exercise;

typedef struct {
    exercise exercises[ARRAY_MAX]; int exercises_count;
    double duration; double max_duration;
    muscle_group muscles[ARRAY_MAX]; int muscles_count; // Muscle groups included in the workout.
    enum day_of_the_week day;
} workout;

typedef struct {
    int age;
    double weight;
    int pushups;
    int squats;
    int _fitness_level; // enum fitness level
    training_day available_training_days[7]; int available_training_days_count;
    int available_equipment[ARRAY_MAX]; int available_equipment_count; // enum equipment
    int ignored_muscle_group_names[ARRAY_MAX]; int ignored_muscle_group_names_count; // enum muscle_group_names
    double training_goal;
    exercise possible_resistance_exercises[ARRAY_MAX]; int possible_resistance_exercises_count;
    exercise possible_aerobic_exercises[ARRAY_MAX]; int possible_aerobic_exercises_count;
    exercise possible_exercises[ARRAY_MAX*2]; int possible_exercises_count;
    workout routine_workouts[7]; int routine_workouts_count; // Max 7 workouts per week (1 per day).
    // Workout rules
    int general_warmup_duration; // In minutes.
    int max_daily_sets; // For resistance training.
    int max_daily_aerobic_exercises;
    double rest_between_sets_resistance; // In minutes.
    double aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.
    int max_weekly_sets; // For resistance training.
    int resistance_recovery;
    int max_weekly_aerobic_workouts;
} user_data;

#pragma endregion

// Functions

#pragma region tools.c

int homemade_scan(data_type type, void* input);
char* naming_equipment(enum equipment eq) ;
char* naming_days(enum day_of_the_week day);
char* naming_muscle_group(muscle_group_name name);
char* naming_exercises(enum exercise_name name);
char* naming_fitness_level(enum fitness_level name);
char* naming_training_goal(enum training_goal_e name);

#pragma endregion
#pragma region new_user_questionnaire.c

void update_questionnaire(user_data *user);
void update_available_training_days(user_data *user);

#pragma endregion
#pragma region exercises.c

void update_possible_exercises(user_data *user_data);
void all_possible_exercises(user_data *user_data);

#pragma endregion
#pragma region workouts.c

void update_routine_workouts(user_data *user);

#pragma endregion
#pragma region upgrade_downgrade.c

void upgrade_downgrade(user_data *user, int *input);

#pragma endregion
#pragma region print_routine.c

void print_routine(user_data *user);

#pragma endregion
#pragma region evaluation_questionnaire.c

void evaluation_questionnaire(user_data *user, int *input);

#pragma endregion
#pragma region savesystem.c
char* arr_to_str(const int *arr, int len);
char* int_to_str(int n);
int str_to_int(char *str);

char* double_to_str(double d);
double str_to_double(char *str);

int str_to_equip();

void load_upgr_dogr(int* data);
void upgr_dogr(int exercise_count, int upgrade_count);
void save_upgr_dogr(int data[length_of_exercise_enum]);
typedef struct {
    char available_equipment[20];
    char available_equipment_count[20];
    char available_training_days_count[20];
    char available_training_days[20];
    char ignored_muscle_group_names_count[20];
    char ignored_muscle_group_names[20];
    char age[20];
    char weight[20];
    char pushups[20];
    char squats[20];
    char fitness_level[20];
    char training_goal[20];
} user_save_data;

void save_all_data(user_data *user);

int check_for_save();

int save_data(const char *data, const char *data_name);

void print_user_data(user_save_data data);

void get_user_data(user_data *user);

user_data convert_data(user_save_data data);

#pragma endregion
#pragma region main.c

void update_and_print_routine(user_data *user);

#pragma endregion

