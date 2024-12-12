// #include "tools.h"
#include "File_conversition.h"
#include <stdio.h>
#include <stdlib.h>

// int total_days = 1;

// char train_to_str(training_day d);
// training_day str_to_train(char);



char* int_to_str(const int n) {
    static char str[2];
    sprintf(str, "%d", n);
    return (str);
}
int str_to_int(const char *str) {
    return atoi(str);
}
static char* double_to_str(const double d) {
    static char str[10];
    sprintf(str, "%lf", d);
    return (str);
}

double str_to_double(const char* str) {
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
