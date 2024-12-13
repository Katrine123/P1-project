#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H
#include "tools.h"

typedef struct {
    char available_equipment[20];
    char age[20];
    char gender[20];
    char weight[20];
    char height[20];
    char pushups[20];
    char squats[20];
    char fitness_level[20];
    char adjustment_factor[20];
} user_save_data;

int check_for_save();

int save_data(const char *data, const char *data_name);

void print_user_data(user_save_data data);

questionnaire load_data();

questionnaire convert_data(user_save_data data);

#endif //SAVESYSTEM_H
