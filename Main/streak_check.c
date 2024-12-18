#include "references.h"

how_many_days_left(date last);
int is_less_than_week(date current, date last);

void streak_check(user_data* user, FILE* file) {
    printf("Last date: %d/%d\n",user->last_date.day,user->last_date.month);
    date temp;
    update_date(&temp.month,&temp.day,file);

    int val = is_less_than_week(temp,user->last_date);
    if(val == 1) {
        user->streak ++;
    }else {
        user->streak =0;
    }
}

int is_less_than_week(date current, date last) {
    if(current.month == last.month){
        if(current.day > last.day+7) {
            return 0;
        }else {
            return 1;
        }
    }else if(current.month == last.month+1){
        if(how_many_days_left(last) + current.day > 7) {
            printf("Days left %d",how_many_days_left(last));
            return 0;
        }else {
            return 1;
        }
    }else {
        return 0;
    }
}

how_many_days_left(date last) {
    switch (last.month){
        case jan: return 31 - last.day;
        break;
        case feb: return 28 - last.day;
        break;
        case mar: return 31 - last.day;
        break;
        case apr: return 30 - last.day;
        break;
        case may: return 31 - last.day;
        break;
        case jun: return 30 - last.day;
        break;
        case jul: return 31 - last.day;
        break;
        case aug: return 31 - last.day;
        break;
        case sep: return 30 - last.day;
        break;
        case oct: return 31 - last.day;
        break;
        case nov: return 30 - last.day;
        break;
        case dec: return 31 - last.day;
        break;
    }
}
