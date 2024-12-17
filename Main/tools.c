#include <ctype.h> //https://www.w3schools.com/c/c_ref_ctype.php
#include <stdio.h>

#include "references.h"

// Input functions
int homemade_scan(data_type type, void* input, FILE *file) {//Uses a void for input, because we don't know what datatype we'll get - Inspiration from qsort
    int is_right = 0;
    do {
        //Checks what datatype we want - ex if i then int
        if(type == integer) {
            //Test whether scanf gets the right input (it return 1 if true)
            if(fscanf(file,"%d",input)==1) {
                is_right = 1;
            }else {
                printf("\nPlease type an integer.");
            }
        }else if(type == character) {
            //With chars we test that it's a letter with isalpha()
            if(fscanf(file,"%c",input)==1&&isalpha(*(char*)input)!=0) {
                is_right = 1;
            }else{
                printf("\nPlease type a char.");
            }
        }else if(type == long_float) {
            if(fscanf(file,"%lf",input)==1) {
                is_right=1;
            }else{
                printf("\nPlease type a double.");
            }
        }else if(type == string) {
            if(fscanf(file,"%s",input)==1&&isalpha(*(char*)input)!=0) {
                is_right = 1;
            }else{
                printf("\nPlease type a string.");
            }
        }
        //Clears any extra inputs
        while ((fgetc(file)) != '\n');
        //Return a true/false, of whether the datatype matches what we want
    }while(is_right ==0);
    return is_right;
}

// Naming functions
char* naming_equipment(enum equipment eq) {
    switch(eq) {
        case barbell: return "Barbell";
        case bench: return "Bench";
        case pull_up_bar: return "Pull up bar";
        case pull_down_machine: return "Pull down machine";
        case resistance_bands: return "Resistance bands";
        default: return "ERROR";
    }
}
char* naming_muscle_group(muscle_group_name name) {
    switch(name) {
        case chest: return "Chest";
        case triceps: return "Triceps";
        case shoulders: return "Shoulders";
        case hamstrings: return "Hamstrings";
        case quads: return "Quads";
        default: return "ERROR";
    }
}
char* naming_days(enum day_of_the_week day) {
    switch(day) {
        case monday: return "Monday";
        case tuesday: return "Tuesday";
        case wednesday: return "Wednesday";
        case thursday: return "Thursday";
        case friday: return "Friday";
        case saturday: return "Saturday";
        case sunday: return "Sunday";
        default: return "ERROR";
    }
}
char* naming_exercises(enum exercise_name name) {
    switch(name) {
        case bench_press: return "Bench press";
        case weighted_squat: return "Weighted squat";
        case air_squat: return "Air squat";
        case pushup: return "Push up";
        case elevated_pushup: return "Elevated push up";
        case burpees: return "Burpees";
        case jumping_jacks: return "Jumping jacks";
        default: return "ERROR";
    }
}
char* naming_fitness_level(enum fitness_level name) {
    switch(name) {
        case novice: return "Novice";
        case advanced_beginner: return "Advanced beginner";
        case competent: return "Competent";
        case proficient: return "Proficient";
        case expert: return "Expert";
        default: return "ERROR";
    }
}

char* naming_training_goal(enum training_goal_e name) {
    switch(name) {
        case MUSCULAR_ENDURANCE: return "Muscular endurance";
        case HYPERTROPHY: return "Hypertrophy";
        case STRENGTH: return "Strength";
        case I_DONT_KNOW: return "I don't know";
        default: return "ERROR";
    }
}