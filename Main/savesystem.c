#include <stdio.h>
#include <string.h>
#include "savesystem.h"
/*
typedef struct {
    char available_equipment[20];
    char age[20];
    char gender[20];
    char weight[20];
    char height[20];
    char pushups[20];
    char fitness_level[20];
    char time_available_week[20];
    char adjustmentfactor[20];
} user_save_data;

questionnaire convert_data (user_save_data data);
///simply checks if save is available returns 1 if data was found and 0 if not
int check_for_save() {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "r"))) {   // attempts to open file
        printf("read operation successful\n");
        fclose(file);
        return(1);
    }
    else {printf("No previous answers saved\n");
        return(0);
    }
}

///saves data like this {[lorem] ipsum} returns 1 if successful
int save_data(char* data, char* data_name) {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "a"))) {
        fprintf(file, "{[%s] %s}, ", data_name, data);
        fclose(file);
        return (1);
    }
    else{
        printf("file opening error\n");
        return (0);
    }
}


///prints data should be used to be used in conjunction with load_data()
void print_user_data(user_save_data data) {
    printf("Available Equipment: %s\n", data.available_equipment);
    printf("Age: %s\n", data.age);
    printf("Gender: %s\n", data.gender);
    printf("Weight: %s\n", data.weight);
    printf("Height: %s\n", data.height);
    printf("Push ups: %s\n", data.pushups);
    printf("Fitness Level: %s\n", data.fitness_level);
    printf("Time Available per Week: %s\n", data.time_available_week);
}

///returns a struct with values harvested from user_data_savefile.txt.
///is pretty resilient and can be used like this to print "print_user_data(load_data());"
questionnaire load_data() {
    user_save_data data;
    FILE *file;
    int count=0;
    if ((file = fopen("user_data_savefile.txt", "r"))) {
        char str[500];
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
                switch (count++) {
                    case 0:
                        strncpy(data.available_equipment, data_data,20);
                        break;
                    case 1:
                        strncpy(data.age, data_data, 20);
                        break;
                    case 2:
                        strncpy(data.gender, data_data,20);
                        break;
                    case 3:
                        strncpy(data.weight, data_data, 20);
                        break;
                    case 4:
                        strncpy(data.height, data_data, 20);
                        break;
                    case 5:
                        strncpy(data.pushups, data_data, 20);
                        break;
                    case 6:
                        strncpy(data.fitness_level, data_data, 20);
                        break;
                    case 7:
                        strncpy(data.time_available_week, data_data,20);
                        break;
                    case 8:
                        strncpy(data.adjustmentfactor, data_data, 20);
                        break;
                    default: printf("too much data will not be read\n");
                    // Switch copies the read data to the struct user data
                    // for now user data is all stored as chars for simplicity’s sake

                }
            }
        }
    } else {printf("file opening error\n");}
    fclose(file); //will at the moment prolly always close the file but am not 100% sure
    questionnaire user = convert_data(data);
    return (user);
}




questionnaire convert_data (user_save_data data) {
    questionnaire user;
    user.age = str_to_int(data.age);
    user.gender = data.gender;
    user.weight = str_to_double(data.weight);
    user.height = str_to_double(data.height);
    user.pushups = str_to_int(data.pushups);
    user.squats = str_to_int(data.squats);
    user.fitness_level = str_to_int(data.fitness_level);
    user.training_days = str_to_train (data.training_days);
    user.available_equipment = str_to_int(data.available_equipment);
    return (user);
}


///needs work and might be renamed to insert data so data can be changed after the first save.
///void delete_data() {
/// FILE * file;
/// if ((file = fopen("user_data_savefile.txt", "r"))) {
/// printf("Delete operation successful\n");
/// }
/// }

*/

