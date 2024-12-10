//
// Created by FreshLuna on 12/3/2024.
//
#include "tools.h"
#include "file_conversion .h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char int_to_str(int n);
int str_to_int(char *str);

char double_to_str(double d);
double str_to_double(char *str);
int total_days = 1;

char train_to_str(training_day d);
training_day str_to_train(char);



char int_to_str(int n) {
    char str[2];
    sprintf(str, "%d", n);
    return (str);
}
int str_to_int(char *str) {
    int n;
    n = atoi(str);
    return n;
}
char double_to_str(double d) {
    char str[10];
    sprintf(str, "%lf", d);
    return (str);
}
double str_to_double(char *str) {
    double d;
    sscanf(str, "%lf", &d);
    return d;
}

//char train_to_str(training_day user) {
//    char str[20];
//    for (int i = 1; i <= total_days; i++) {
//        sprintf(str, "%d, %lf", user[i].day_week, user[i].available_time);
//    }
//
//    return (str);
//}


//training_day* str_to_train(const char* str) {
//    training_day *user = malloc(total_days * sizeof(training_day));
//    for (int i = 0; i <= total_days; i++) {
//
//    }
//    return user;
//}
