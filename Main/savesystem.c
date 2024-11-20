#include "savesystem.h"
#include "new_user_questionnaire.h"
#include <stdio.h>

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

int save_data(char* data, char* data_name) {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "a"))) {
        fprintf(file, "{[%s] %s}, ", data_name, data);
        fclose(file);
    }
    else{
        printf("file opening error\n");
    }
    return (1);
}


void load_data() {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "r"))) {
        char str[500];
        printf("%s", fgets(str, 500, file));
        fclose(file);

    }

}


/// %[^"]"]


void delete_data() {
    FILE * file;
    if ((file = fopen("user_data_savefile.txt", "r"))) {



    }
}