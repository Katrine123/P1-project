#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "references.h"


// Conversion

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
training_day str_to_week(char *str) {
}
user_data convert_data (user_save_data data) {
    user_data user;
    //standard data handling with the conversion functions
    user.age            = str_to_int(data.age);
    user.weight         = str_to_double(data.weight);
    user.pushups        = str_to_int(data.pushups);
    user.squats         = str_to_int(data.squats);
    user._fitness_level = str_to_int(data.fitness_level);
    user.training_goal 	= str_to_int(data.training_goal);

    //TODO: Replace
    //random inputs just so it will work til its replaced
    user.available_training_days_count = 6;
    user.available_training_days[0] = (training_day){1, 42};
    user.available_training_days[1] = (training_day){2, 42};
    user.available_training_days[2] = (training_day){3, 42};
    user.available_training_days[3] = (training_day){4, 42};
    user.available_training_days[4] = (training_day){5, 42};
    user.available_training_days[5] = (training_day){6, 42};
    user.available_training_days[6] = (training_day){7, 42};

    //handling of arrays
    user.available_equipment_count = str_to_int(data.available_equipment_count);
    for (int i = 0 ; i <= user.available_equipment_count; i++) {
        user.available_equipment[i] = data.available_equipment[i]-'0';
    }
    user.ignored_muscle_group_names_count = str_to_int(data.ignored_muscle_group_names_count);
    for (int i = 0 ; i <= user.ignored_muscle_group_names_count; i++) {
        user.ignored_muscle_group_names[i] = data.ignored_muscle_group_names[i]-'0';
    }
    //user.available_training_days_count = str_to_int(data.available_training_days_count);
    //for (int i = 0 ; i <= user.available_training_days_count; i++) {
    //    user.available_training_days[i] = data.available_training_days[i]-'0';
    //}
    return (user);
}

// User data save

///simply checks if save is available returns 1 if data was found and 0 if not
int check_for_save() {
    FILE * file;
    if ((file = fopen("user_save_file", "r"))) {   // attempts to open file
        printf("read operation successful\n");
        fclose(file);
        return(1);
    }
    else {printf("No previous answers saved\n");
        return(0);
    }
}
int reset_save_data() {
    FILE * file;
    if ((file = fopen("user_save_file", "w"))) {
        fprintf(file, "");
        fclose(file);
        return (1);
    }
    printf("file opening error\n");
    return (0);
}
/// Saves data like this {[lorem] ipsum}. Returns 1 if successful
int save_to_user_data_save(const char *data, const char *data_name) {
    FILE * file;
    if ((file = fopen("user_save_file", "a"))) {
        fprintf(file, "{[%s] %s}, ", data_name, data);
        fclose(file);
        return (1);
    }
    printf("file opening error\n");
    return (0);
}
void save_user_data(user_data *user) {

    reset_save_data();
    //int active_functions = 8;
    //int error_check = 0;
    save_to_user_data_save(int_to_str(user->squats), "squats");
    save_to_user_data_save(int_to_str(user->pushups), "push");
    save_to_user_data_save(int_to_str(user->training_goal), "train");
    //save_data(int_to_str(user->available_training_days_count),"Days") +
    save_to_user_data_save(int_to_str(user->ignored_muscle_group_names_count), "Muscles");
    save_to_user_data_save(int_to_str(user->available_equipment_count), "Equipment");
    save_to_user_data_save(int_to_str(user->_fitness_level), "lvl");
    save_to_user_data_save(double_to_str(user->weight), "weight");
    //save_data(arr_to_str(user->available_training_days, user->available_training_days_count),"days");
    save_to_user_data_save(arr_to_str(user->available_equipment, user->available_equipment_count), "equipment");
    save_to_user_data_save(arr_to_str(user->ignored_muscle_group_names, user->ignored_muscle_group_names_count),"muscles");


    //if (error_check==active_functions) {
    //  printf("data saved successfully\n");
    //for (int i = 1; i <= 7; i++) {
    //    save_data(int_to_str(user->available_training_days[i].max_duration), int_to_str(i));
    //}
    //if (error_check<active_functions) {
    // printf("ERROR: file could most likely not be opened.\n");
    // printf("If user_save_data.txt'' is open on pc please attempt to close the file\n");
    // printf("Attempting to save again\n");
    // save_all_data();
}
void get_saved_user_data(user_data *user) {
    user_save_data data;
    FILE *file;
    if ((file = fopen("user_save_file", "r"))) {
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
                //printf("%s\n", data_name);

                j=0;
                i+=2;
                while (str[i] != '}') {
                    data_data[j++] = str[i++];
                }
                data_data[j] = '\0';
                //printf("%s\n", data_data);
                switch (data_type[0]) {
                    case 'e':
                        strncpy(data.available_equipment, data_data,20);
                        break;
                    case 'E':
                        strncpy(data.available_equipment_count, data_data,20);
                        break;
                    case 'd':
                    //    strncpy(data.available_training_days, data_data,20);
                        break;
                    case 'D':
                    //    strncpy(data.available_training_days_count, data_data,20);
                        break;
                    case 'm':
                        strncpy(data.ignored_muscle_group_names, data_data,20);
                    break;
                    case 'M':
                        strncpy(data.ignored_muscle_group_names_count, data_data,20);
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
                    default: printf("unknown data type \n %s %s\n",data_type, data_data );
                        // Switch copies the read data to the struct user data
                        // for now user data is all stored in strings and type is read as chars for simplicity’s sake

                }
            }
        }
    } else {printf("file opening error\n");}
    fclose(file); //will at the moment prolly always close the file but am not 100% sure
    *user = convert_data(data);
    return;
}

// User upgrade save

void reset_upgrades_save(user_data *user) {
    update_possible_exercises(user);
    FILE *file = fopen("user_upgrades", "w");
    for (int i = 0; i < user->possible_exercises_count; i++) {
        fprintf(file, "0 ,");
    }
    fclose(file);
}
void save_upgrades(user_data *user, int data[user->possible_exercises_count+1]) {
    FILE *file = fopen("user_upgrades", "w");
    for (int i = 0; i < user->possible_exercises_count; i++) {
        fprintf(file, "%d ,", data[i]);
    }
    fclose(file);
}
void get_saved_upgrades(user_data *user, int *data) {
    FILE *f = fopen("user_upgrades", "r");

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
void upgrade_or_downgrade_exercise(user_data *user, int exercise_index, int addition_to_upgrade) {
    int temp_save[user->possible_exercises_count];
    get_saved_upgrades(user, temp_save);
    temp_save[exercise_index] = temp_save[exercise_index] + addition_to_upgrade;
    save_upgrades(user, temp_save);
}


