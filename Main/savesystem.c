#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "references.h"

// Save file names
const char user_data_save_file_name[] = "user_data_save_file";
const char user_upgrades_save_file_name[] = "user_upgrades_save_file";

// Functions for data conversion

/// Uses malloc() for the return value, so remember to free it.
char* arr_to_str(const int *arr, int len) {
    char *str = malloc(len+1);
    str[0] = '\0';
    for (int i = 0; i < len; i++) {
        char temp_str[10];
        snprintf(temp_str, sizeof(temp_str), "%d", arr[i]);
        strcat(str, temp_str);
    }
    str[len] = '\0';
    return str;
}
char* int_to_str(int n) {
    static char str[2];
    sprintf(str, "%d", n);
    return (str);
}
int str_to_int(char *str) {
    return atoi(str);
}
char* double_to_str(double d) {
    static char str[10];
    sprintf(str, "%lf", d);
    return (str);
}
double str_to_double(char* str) {
    return atof(str);
}
training_day str_to_training_day(char *str) {
    training_day training_day;
    char* token = strtok(str, " - ");
    training_day.day = str_to_int(token);
    token = strtok(NULL, " - ");
    training_day.max_duration = str_to_int(token);
    return (training_day);
}
char* training_day_to_str(training_day training_day) {
    static char str[20];
    sprintf(str, "%d-%.0f", training_day.day, training_day.max_duration);
    return (str);
}
user_data convert_to_user_data (user_save_data data) {

    user_data user;
    //standard data handling with the conversion functions
    user.age            = str_to_int(data.age);
    user.weight         = str_to_double(data.weight);
    user.pushups        = str_to_int(data.pushups);
    user.squats         = str_to_int(data.squats);
    user._fitness_level = str_to_int(data.fitness_level);
    user.training_goal 	= str_to_int(data.training_goal);

    //random inputs just so it will work til its replaced
    user.available_training_days_count = str_to_int(data.available_training_days_count);

    user.available_training_days[0] = str_to_training_day(data.day1);
    user.available_training_days[1] = str_to_training_day(data.day2);
    user.available_training_days[2] = str_to_training_day(data.day3);
    user.available_training_days[3] = str_to_training_day(data.day4);
    user.available_training_days[4] = str_to_training_day(data.day5);
    user.available_training_days[5] = str_to_training_day(data.day6);
    user.available_training_days[6] = str_to_training_day(data.day7);

    //handling of arrays
    user.available_equipment_count = str_to_int(data.available_equipment_count);
    for (int i = 0 ; i <= user.available_equipment_count; i++) {
        user.available_equipment[i] = data.available_equipment[i]-'0';
    }
    user.ignored_muscle_group_names_count = str_to_int(data.ignored_muscle_group_names_count);
    for (int i = 0 ; i <= user.ignored_muscle_group_names_count; i++) {
        user.ignored_muscle_group_names[i] = data.ignored_muscle_group_names[i]-'0';
    }

    user.last_date.day = str_to_int(data.date_day);
    user.last_date.month = str_to_int(data.date_month);
    user.streak = str_to_int(data.streak);

    return user;
}

// Functions for user data save

/// Simply checks if save is available. Returns 1 if data was found, and 0 if not.
int check_for_user_data_save() {
    FILE * file;
    if ((file = fopen(user_data_save_file_name, "r"))) {   // attempts to open file
        printf("\nRead operation successful.");
        fclose(file);
        return(1);
    }
    else {printf("\nNo previous answers saved.");
        return(0);
    }
}
int reset_user_data_save() {
    FILE * file;
    if ((file = fopen(user_data_save_file_name, "w"))) {
        fprintf(file, "");
        fclose(file);
        return (1);
    }
    printf("\nFile opening error.");
    return (0);
}
/// Saves data like this {[lorem] ipsum}. Returns 1 if successful.
int add_to_user_data_save(const char *data, const char *data_name) {
    FILE * file;
    if ((file = fopen(user_data_save_file_name, "a"))) {
        fprintf(file, "{[%s] %s}, ", data_name, data);
        fclose(file);
        return (1);
    }
    printf("\nFile opening error.");
    return (0);
}
void save_user_data_save(user_data *user) {

    reset_user_data_save();

    add_to_user_data_save(int_to_str(user->squats), "squats");
    add_to_user_data_save(int_to_str(user->pushups), "push");
    add_to_user_data_save(int_to_str(user->training_goal), "train");
    add_to_user_data_save(int_to_str(user->available_training_days_count),"Days") +
    add_to_user_data_save(int_to_str(user->ignored_muscle_group_names_count), "Muscles");
    add_to_user_data_save(int_to_str(user->available_equipment_count), "Equipment");
    add_to_user_data_save(int_to_str(user->_fitness_level), "lvl");
    add_to_user_data_save(double_to_str(user->weight), "weight");

    char* equipment = arr_to_str(user->available_equipment, user->available_equipment_count);
    add_to_user_data_save(equipment, "equipment");
    free(equipment);

    char* ignored_muscles = arr_to_str(user->ignored_muscle_group_names, user->ignored_muscle_group_names_count);
    add_to_user_data_save(ignored_muscles, "muscles");
    free(ignored_muscles);

    for (int i = 0; i <= user->available_training_days_count; i++) {
        add_to_user_data_save(training_day_to_str(user->available_training_days[i]), int_to_str(i+1));
    }
    add_to_user_data_save(int_to_str(user->last_date.day), "y_day");
    add_to_user_data_save(int_to_str(user->last_date.month), "h_month");
    add_to_user_data_save(double_to_str(user->streak), "k_streak");

}
void load_user_data_save(user_data *user) {
    user_save_data data;
    FILE *file;
    if ((file = fopen(user_data_save_file_name, "r"))) {
        fseek(file, 0L, SEEK_END);
        int size = ftell(file);
        char str[size+10];
        fseek(file, 0L, SEEK_SET);
        fgets(str, sizeof(str), file);
        for (int i = 0; i<strlen(str); i++) {
            if (str[i-1] == '[') {
                char data_type[20]; //dont remove "data_name" yet will break function because of bad while loop
                char data_data[20]; //also need it for inserting data at a later point
                int j=0;
                while (str[i] != ']') {
                    data_type[j++] = str[i++]; //this is terrible but also temporary :3
                }
                data_type[j] = '\0';

                j=0;
                i+=2;
                while (str[i] != '}') {
                    data_data[j++] = str[i++];
                }
                data_data[j] = '\0';
                switch (data_type[0]) {
                    case '1':
                        strncpy(data.day1, data_data,20);
                        break;
                    case '2':
                        strncpy(data.day2, data_data,20);
                        break;
                    case '3':
                        strncpy(data.day3, data_data,20);
                        break;
                    case '4':
                        strncpy(data.day4, data_data,20);
                        break;
                    case '5':
                        strncpy(data.day5, data_data,20);
                        break;
                    case '6':
                        strncpy(data.day6, data_data,20);
                        break;
                    case '7':
                        strncpy(data.day7, data_data,20);
                        break;
                    case 'e':
                        strncpy(data.available_equipment, data_data,20);
                        break;
                    case 'E':
                        strncpy(data.available_equipment_count, data_data,20);
                        break;
                    case 'D':
                        strncpy(data.available_training_days_count, data_data,20);
                        break;
                    case 'm':
                        strncpy(data.ignored_muscle_group_names, data_data,20);
                        break;
                    case 'M':
                        strncpy(data.ignored_muscle_group_names_count, data_data,20);
                        break;
                    case 'a':
                        strncpy(data.age, data_data,20);
                        break;
                    case 'w':
                        strncpy(data.weight, data_data, 20);
                        break;
                    case 'p':
                        strncpy(data.pushups, data_data, 20);
                        break;
                    case 's':
                        strncpy(data.squats, data_data, 20);
                        break;
                    case 'l':
                        strncpy(data.fitness_level, data_data, 20);
                        break;
                    case 't':
                        strncpy(data.training_goal, data_data, 20);
                        break;
                    case 'y':
                        strncpy(data.date_day, data_data, 20);
                    break;
                    case 'h':
                        strncpy(data.date_month, data_data, 20);
                    break;
                    case 'k':
                        strncpy(data.streak, data_data, 20);
                    break;
                    default: printf("\nUnknown data type \n %s %s",data_type, data_data );
                        // Switch copies the read data to the struct user data
                        // for now user data is all stored in strings and type is read as chars for simplicity’s sake

                }
            }
        }
    } else {printf("\nFile opening error.");}
    fclose(file); //will at the moment prolly always close the file but am not 100% sure
    *user = convert_to_user_data(data);
}

// Functions for user upgrades save

void reset_user_upgrades_save(user_data *user) {
    update_possible_exercises(user);
    FILE *file = fopen(user_upgrades_save_file_name, "w");
    for (int i = 0; i < user->possible_exercises_count; i++) {
        fprintf(file, "0 ,");
    }
    fclose(file);
}
void save_user_upgrades_save(user_data *user, int data[user->possible_exercises_count+1]) {
    FILE *file = fopen(user_upgrades_save_file_name, "w");
    for (int i = 0; i < user->possible_exercises_count; i++) {
        fprintf(file, "%d ,", data[i]);
    }
    fclose(file);
}
void get_data_from_user_upgrades_save(user_data *user, int *data) {
    FILE *f = fopen(user_upgrades_save_file_name, "r");

    char temp[32*user->possible_exercises_count];
    fgets(temp, sizeof(temp), f);

    char *token = strtok(temp, ",");
    int i = 0;
    while (token != NULL && i < user->possible_exercises_count) {
        data[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
    fclose(f);
}



