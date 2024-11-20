#include "tools.h"
#include <ctype.h> //https://www.w3schools.com/c/c_ref_ctype.php
#include <stdio.h>

int homemade_scan(datatype type, void* input) {//Uses a void for input, because we don't know what datatype we'll get - Inspiration from qsort
    int is_right = 0;
    do {
        //Checks what datatype we want - ex if i then int
        if(type == integer) {
            //Test whether scanf gets the right input (it return 1 if true)
            if(scanf("%d",input)==1) {
                is_right = 1;
            }else {
                printf("Please type an integer");
            }
        }else if(type == character) {
            //With chars we test that it's a letter with isalpha()
            if(scanf("%c",input)==1&&isalpha(*(char*)input)!=0) {
                is_right = 1;
            }else{
                printf("Please type a char");
            }
        }else if(type == long_float) {
            if(scanf("%lf",input)==1) {
                is_right=1;
            }else{
                printf("Please type a double");
            }
        }else if(type == string) {
            if(scanf("%s",input)==1&&isalpha(*(char**)input)!=0) {
                is_right = 1;
            }else{
                printf("Please type a string");
            }
        }
        //Clears any extra inputs
        while ((getchar()) != '\n');//https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
        //Return a true/false, of whether the datatype matches what we want
    }while(is_right ==0);
    return is_right;
}



char* naming_equipment(enum equipment eq) {
    switch(eq) {
        case barbell: return "Barbell";
        break;
        case bench: return "Bench";
        break;
        case pull_up_bar: return "Pull up bar";
        break;
        case pull_down_machine: return "Pull down machine";
        break;
        case resistance_bands: return "Resistance bands";
        break;
    }
}