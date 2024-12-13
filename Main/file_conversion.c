// #include "tools.h"
#include "file_conversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int total_days = 1;

// char train_to_str(training_day d);
// training_day str_to_train(char);

char* arr_to_str(const int *arr, int len) {
    char *str = malloc(len+1);
    str[0] = '\0';
    for (int i = 0; i < len; i++) {
        char num_str[12];
        snprintf(num_str, sizeof(num_str), "%d", arr[i]);
        strcat(str, num_str);
    }
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
//int str_to_seq_int(int n, char str[n]) {
//    int arr[6];
//    for (int i = 0; i < 6; i++) {
//        arr[i] = str[i] - '0';
//    }
//    return ;
//}



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
