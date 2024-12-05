#include "workouts.h"
#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "exercises.h"
#include "new_user_questionnaire.h"


//TODO:
// Check that you use pointer parameters everywhere
// where you are changing the values of the parameter or its properties (if it's a struct).

//TODO:
// Implement supersets (will decrease time spent + will need information about opposing muscle groups).

//TODO:
// (ACTUALLY, THIS SHOULD BE DONE BY TEAM MISCHA AND LUNA)
// Implement ignored exercises (user story: "I hate squats, please give me any leg exercise other than squats.")



enum muscle_group_name_e {
    bicep, tricep, chest, quads
}; //TODO: expand upon this

// This is just a constant number to use as the size of arrays.
static const int MUSCLE_GROUPS_ARRAY_MAX = 32;  // 32 simply because it's a big enough number.
typedef struct {
    enum muscle_group_name_e name;
    int sets;
} muscle_group_t;
// This is the pool of muscle groups included in the whole weekly routine.
muscle_group_t routine_muscle_groups[MUSCLE_GROUPS_ARRAY_MAX];
int routine_muscle_groups_count = 0;
// This is the pool of muscle groups that the routine may include according to the user's preferences.
enum muscle_group_name_e valid_muscle_groups[MUSCLE_GROUPS_ARRAY_MAX];
int valid_muscle_groups_count = 0;

// TODO: Place this inside the questionaire.c
enum day_of_the_week {
    monday = 1, tuesday = 2, wednesday = 3, thursday = 4,
    friday = 5, saturday = 6, sunday = 7
};

// This is just a constant number to use as the size of arrays.
static const int EXERCISES_ARRAY_MAX = 32; // 32 simply because it's a big enough number. //TODO: Relocate this where the exercise struct is defined.
typedef struct {
    exercise exercises[EXERCISES_ARRAY_MAX];
    int exercises_count;
    double duration; // In minutes.
    double max_duration; // In minutes.
    enum day_of_the_week day;
} workout_t;

typedef struct {
    workout_t* workout;
    muscle_group_t targeted_muscle_groups[MUSCLE_GROUPS_ARRAY_MAX];
    int targeted_muscle_groups_count;
} resistance_training_day;

typedef struct {
    const int general_warmup_duration = 5;
    const int max_daily_sets = 6; //  For resistance training. Any more sets are junk volume.
    int max_weekly_sets; // For resistance training.
    int resistance_recovery; // For resistance training.
    int max_weekly_aerobic_workouts; //todo implement this
    int aerobic_rest_multiplier; // For example, a multiplier of 2, means a work-to-rest ratio of 1:2.
} workout_rules;

static workout_rules get_workout_rules(
    questionnaire q)
{
    workout_rules rules;
    enum fitness_level level = q.fitness_level;
    if (level >= novice) { // novice = 5, advanced_beginner = 4, competent = 3, proficient = 2
        rules.max_weekly_sets = 10; // To make it easier to get into the habit of fitness.
        rules.resistance_recovery = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_weekly_aerobic_workouts = 3; // Limited, because beginners are recommended 1-3 sessions per week.
        rules.aerobic_rest_multiplier = 3; // 1:3 work-to-rest ratio.
    } else if (level >= advanced_beginner) {
        rules.max_weekly_sets = 10; // To make it easier to get into the habit of fitness.
        rules.resistance_recovery = 3; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        rules.aerobic_rest_multiplier = 2; // 1:2 work-to-rest ratio.
    } else {
        rules.max_weekly_sets = 20; // todo: add explanation (I should research what the max volume should be)
        rules.resistance_recovery = 2; // Recovery time ranges from 48-72 hours for 6-15 reps.
        rules.max_weekly_aerobic_workouts = 7; // No limit, because recovery time is 24 hours.
        rules.aerobic_rest_multiplier = 1; // 1:1 work-to-rest ratio.
    }
    return rules;
}

/// @param workouts Output. Uses malloc().
/// @param count Output.
static void initialize_workouts(
    workout_t *workouts, int *count, questionnaire q, workout_rules rules)
{
    *count = q.available_workout_days_count;
    workouts = malloc(sizeof(workout_t) * *count);
    // Assign stat variables for the workout structs.
    for (int i = 0; i < *count; i++) {
        //todo available_workout_days is an array of struct workout_day which has an enum week_day and an int max_duration_in_minutes.
        workouts[i].day = q.available_workout_days[i].week_day;
        workouts[i].max_duration = q.available_workout_days[i].max_duration_in_minutes;
        workouts[i].exercises_count = 0;
        // Add general warmup to workout duration.
        workouts[i].duration = rules.general_warmup_duration;
    }
}

/// @param resistance_days Output. Uses malloc().
/// @param rcount Output.
/// @param acount Output
static void initialize_resistance_training_days(
    resistance_training_day** resistance_days, int *rcount, int *acount, workout_rules rules,
    workout_t* workouts, int workouts_per_week, int** aerobic_days)
{
    *resistance_days = malloc(sizeof(resistance_training_day) * 3); // Can max be 3 (because of minimum 48 hours of recovery). //todo kig dobbelt pointer på resistance og fjernet "&" i
    *rcount = 0;

    *aerobic_days = malloc(sizeof(resistance_training_day) * 4); //todo Check mængden af aerobic days.
    *acount = 0;

    // Loop through workout days.
    for (int i = 0; i < workouts_per_week; i++ ) {
        int is_valid = 1;
        // In case no resistance training days exist, the day must be valid.
        if (*rcount != 0) {
            // Loop through resistance training days.
            for (int j = 0; j <= *rcount + 1; j++) {
                int days_between = workouts[i].day - (*resistance_days)[j].workout->day;
                // Account for if the check day is in next week (e.g. the days between Sunday and Monday).
                if (days_between < 0) {
                    days_between += 7;
                }
                // Mark day as invalid, if recovery rules are not met.
                if (days_between < rules.resistance_recovery) {
                    is_valid = 0;
                    break;
                }

            }
        }
        // Add valid days to the list of resistance training days.
        if (is_valid == 1) {
            resistance_training_day* addition = resistance_days[*rcount];
            addition->workout = &workouts[i];
            (*rcount)++;
        }
        // ved ikke helt hvad du ville med dette men lavede et for arobic days aswell thank me later
        else {
            resistance_training_day* addition = aerobic_days[*acount];
            addition->workout = &workouts[i];
            (*acount)++;
        }
    }
}

/// @param found_a_candidate Output.
/// @param result Output.
static void find_untargeted_muscle_group_candidates(
    int *found_a_candidate, enum muscle_group_name_e *results, resistance_training_day* resistance_day)
{
    for (int i = 0; i < valid_muscle_groups_count; i++) {
        // Looping through valid muscle groups
        for (int i = 0 )

    }

}

static void pick_best_untargeted_muscle_group_candidate()
{

}

/// @param found_a_candidate Output.
/// @param result Output.
static void find_resistance_exercise_candidates(
    int *found_a_candidate, exercise *results, muscle_group_t target_muscle_group, workout_rules rules, resistance_training_day *resistance_day)
{
    //TODO:
    // Needs to try to find a different resistance exercise
    // for the same muscle group.
    // So instead of doing squats both on resistance training day 1 and 2,
    // you do squats the first day, and then do leg press the other
    // for the 3rd day, it might then propose squats again, if there are no alternatives
    // other than squats and leg press

    // TODO: valid_resistance_exercises is a global exercise array containing all valid resistance exercises (handled by team MISCHA AND LUNA).
    // TODO: struct exercise has an array of muscle_group muscle_groups (for muscle groups that the exercise targets) and an int muscle_groups_count
    // Loop through all available exercises
    for (int i = 0; i < valid_resistance_exercises_count; i++) {
        // Does the exercise candidate include the target muscle group?
        int contains_target_muscle_group = 0;
        for (int j = 0; j < valid_resistance_exercises[i].muscle_groups_count; j++) {
            // Looping through the candidate's targeted muscle groups
            if (target_muscle_group.name == valid_resistance_exercises[i].muscle_groups[j].name) {
                contains_target_muscle_group = 1;
                break;
            }
        }
        if (!contains_target_muscle_group) {
            continue;
        }
        // Does adding the exercise candidate exceed workout duration limit?
        if (resistance_day->workout->max_duration < (resistance_day->workout->duration + valid_resistance_exercises[i].duration)) {
            continue;
        }
        // Does adding the exercise candidate exceed max weekly sets?
        int exceeds_max_weekly_sets = 0;
        int routine_contains_target_muscle_group = 0;
        for (int j = 0; j < routine_muscle_groups_count; j++) {
            // Looping through all muscle groups in the routine
            if (target_muscle_group.name == routine_muscle_groups[j].name) {
                routine_contains_target_muscle_group = 1;
                if (rules.max_weekly_sets < (routine_muscle_groups[j].sets + 1)) {
                    exceeds_max_weekly_sets = 1;
                }
                break;
            }
        }
        if (!routine_contains_target_muscle_group) {
            printf("ERROR: Tried to find an exercise candidate for a muscle group, "
                   "but the muscle group does not exist in the fitness routine's array of muscle groups.");
            exit(EXIT_FAILURE);
        }
        if (exceeds_max_weekly_sets) {
            continue;
        }
        // Does adding it exceed max daily sets?
        int exceeds_max_daily_sets = 0;
        for (int j = 0; j < resistance_day->targeted_muscle_groups_count; j++) {
            // Looping through already targeted muscle groups that day
            if (target_muscle_group.name == resistance_day->targeted_muscle_groups[j].name) {
                if (rules.max_daily_sets < (resistance_day->targeted_muscle_groups[j].sets + 1)) {
                    exceeds_max_daily_sets = 1;
                }
                break;
            }
        }
        if (exceeds_max_daily_sets) {
            continue;
        }
        // If the exercise is a valid candidate, return it
        *found_a_candidate = 1;
        *result = valid_resistance_exercises[i];
    }
    // Return NULL if no valid candidate is found.
    *found_a_candidate = 0;
}

static void pick_best_resistance_exercise_candidate()
{
    initialize_resistance_training_days();
}


static void add_resistance_exercises(
    questionnaire q, resistance_training_day* resistance_days, int resistance_days_count)
{
    // TODO: Implement this.

    // Loop until we have tried to add an exercise for each muscle group.
    do {
        modified_a_day_this_loop = 0;
        for (int i = 0; i < resistance_days_count; i++) {
            // Looping through the resistance training days.
            // Get an untargeted muscle group candidate

            // Found a candidate?

            // Get an exercise candidate

            // Found a candidate?

            // Add exercise and specific warmup
        }
    } while ();
}

/// @param found_a_candidate Output.
/// @param result Output.


    // Start of Lunas lovely hiding spot

exercise find_aerobic_exercise_candidate(exercise available_aerobic_exercises_list) //i assume this is what it
{




    return ;
}

static void add_aerobic_exercises(workout_t workouts, resistance_training_day aerobic_days, int aerobic_days_count, //add pointers forstår ikke dit system
                                  int number_of_aerobic_exercises, exercise aerobic_candidates[], int count_of_workouts )
{
    int array[number_of_aerobic_exercises]; // initializes an array with numbers from 0 too num of exercises

    for (int i = 0; i < number_of_aerobic_exercises; i++) {
        array[i] = i;
    }
    for (int i = 0; i < number_of_aerobic_exercises; i++) { //shuffles array
        array[i]           = array[rand() % number_of_aerobic_exercises]; //todo fix potential issu with reoccuring workouts.
    }


    // inputs exercises randomly into workout.exercises
    for (int i = 0; i <= aerobic_days_count; i++) {
        for (int j = 0; j <3; j++) {
            workouts[count_of_workouts].exercises[j] = aerobic_candidates[array[i]];
            count_of_workouts++;
        }
}



    // End of Lunas Lovely hiding spot. :3


static void fill_workouts_with_sets(workout_t* workouts)
{
    // TODO: Implement this
}

static void reverse_order_of_exercises(workout_t* workouts)
{
    // TODO: Implement this
}


/// @param valid_muscle_groups Output.
/// @param count Output.
static void get_valid_muscle_groups(questionnaire q)
{
    // TODO: all_muscle_groups is a global muscle group array containing all muscle groups
    int all_muscle_groups_count = sizeof(all_muscle_groups) / sizeof(all_muscle_groups[0]);
    // Loop through all muscle groups.
    for (int i = 0; i < all_muscle_groups_count; i++) {
        muscle_group_t* the_group = &all_muscle_groups[i];
        int is_valid = 1;
        // Loop through all ignored muscle groups.
        for (int j = 0; j < q.ignored_muscle_groups_count; j++) {
            // Mark ignored groups as invalid.
            if (the_group->name == q.ignored_muscle_groups[j].name) {
                is_valid = 0;
                break;
            }
        }
        // Add valid muscle groups to the output array.
        if (is_valid) {
            valid_muscle_groups[valid_muscle_groups_count] = the_group->name;
            valid_muscle_groups_count++;
        }
    }
}

/// Return value is allocated to the heap.
/// SUMMARY: Creates an array of workouts to be used as the final fitness routine.
/// @param q - the used questionnaire.
/// @param resistance - array of resistance training exercises to be used.
/// @param aerobic - array of aerobic training exercises to be used.
workout_t *create_workouts(questionnaire q, exercise resistance[], int resistance_length, exercise aerobic[], int aerobic_length)
{
    // todo: implement this.

    get_valid_muscle_groups(q);

    workout_rules rules = get_workout_rules();

    workout_t* workouts;
    int workouts_count;
    initialize_workouts();

    resistance_training_day* resistance_workouts;
    int resistance_workouts_count;
    initialize_resistance_training_days();

    add_resistance_exercises();
    add_aerobic_exercises();
    fill_workouts_with_sets();
    reverse_order_of_exercises(); // Makes aerobic exercises come before resistance exercises.

    return workouts;
}

