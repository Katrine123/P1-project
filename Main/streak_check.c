#include "references.h"

how_many_days_left(date last);
int is_more_than_week(date current, date last);

void streak_check(user_data* user, FILE* file) {
    printf("Last date: %d/%d\n",user->last_date.day,user->last_date.month);
    printf("What is the current date? Please write the date, enter, and then month");
    date temp;
    homemade_scan(integer,&temp.day,file);
    homemade_scan(integer,&temp.month,file);
    int val = is_more_than_week(temp,user->last_date);
    if(val == 1) {
        user->streak ++;
    }else {
        user->streak =0;
    }
}

int is_more_than_week(date current, date last) {
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
        case 1: return 31 - last.day;
        break;
        case 2: return 28 - last.day;
        break;
        case 3: return 31 - last.day;
        break;
        case 4: return 30 - last.day;
        break;
        case 5: return 31 - last.day;
        break;
        case 6: return 30 - last.day;
        break;
        case 7: return 31 - last.day;
        break;
        case 8: return 31 - last.day;
        break;
        case 9: return 30 - last.day;
        break;
        case 10: return 31 - last.day;
        break;
        case 11: return 30 - last.day;
        break;
        case 12: return 31 - last.day;
        break;
    }
}
