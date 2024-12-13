#include <stdio.h>
#include <string.h>
#include "savesystem.h"

#include "file_conversion.h"

questionnaire convert_data (user_save_data data);
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
///saves data like this {[lorem] ipsum} returns 1 if successful
int save_data(const char *data, const char *data_name) {
    FILE * file;
    if ((file = fopen("user_save_file", "a"))) {
        fprintf(file, "{[%s] %s}, ", data_name, data);
        fclose(file);
        return (1);
    }
    printf("file opening error\n");
    return (0);
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
}

///returns a struct with values harvested from user_data_savefile.txt.
///is pretty resilient and can be used like this to print "print_user_data(load_data());"
questionnaire load_data() {
    user_save_data data;
    FILE *file;
    int count=0;
    if ((file = fopen("user_save_file", "r"))) {
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
                switch (data_type[0]) {
                    case 'e':
                        strncpy(data.available_equipment, data_data,20);
                        break;

                    case 'a':
                        strncpy(data.age, data_data,20);
                        break;

                    case 'g':
                        strncpy(data.gender, data_data,20);
                        break;

                    case 'w':
                        strncpy(data.weight, data_data, 20);
                        break;

                    case 'h':
                        strncpy(data.height, data_data, 20);
                        break;

                    case 'p':
                        strncpy(data.pushups, data_data, 20);
                        break;

                    case 's':
                        strncpy(data.squats, data_data, 20);
                        break;

                    case 'f':
                        strncpy(data.fitness_level, data_data, 20);
                        break;

                    case 'u':
                        strncpy(data.adjustment_factor, data_data, 20);
                        break;

                    default: printf("unknown data type\n");
                        // Switch copies the read data to the struct user data
                        // for now user data is all stored in strings and type is read as chars for simplicity’s sake

                }
            }
        }
    } else {printf("file opening error\n");}
    fclose(file); //will at the moment prolly always close the file but am not 100% sure
    return (convert_data(data));
}

questionnaire convert_data (user_save_data data) {
    questionnaire user;
    user.age = str_to_int(data.age);
    user.weight = str_to_double(data.weight);
    user.height = str_to_double(data.height);
    user.pushups = str_to_int(data.pushups);
    user.squats = str_to_int(data.squats);
    user.fitness_level = str_to_int(data.fitness_level);
    strcpy(user.gender, data.gender);
    user.training_days[0] = (training_day){0, 4.0};  // Sunday: 4.0 hours
    user.training_days[1] = (training_day){1, 2.5};  // Monday: 2.5 hours
    user.training_days[2] = (training_day){2, 3.0};  // Tuesday: 3.0 hours
    user.training_days[3] = (training_day){3, 2.0};  // Wednesday: 2.0 hours
    user.training_days[4] = (training_day){4, 1.0};  // Thursday: 1.0 hours
    user.training_days[5] = (training_day){5, 1.5};  // Friday: 1.5 hours
    user.training_days[6] = (training_day){6, 0.5};  // Saturday: 0.5 hours
    for (int i = 0 ; i < 5; i++) {
        user.available_equipment[i] = data.available_equipment[i]-'0';
    }
    return (user);
}


///needs work and might be renamed to insert data so data can be changed after the first save.
///void delete_data() {
/// FILE * file;
/// if ((file = fopen("user_data_savefile.txt", "r"))) {
/// printf("Delete operation successful\n");
/// }
/// }



