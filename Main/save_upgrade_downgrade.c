#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save_upgrade_downgrade.h"

void load_upgr_dogr(int* data);
void save_upgr_dogr(int data[6]);
int lenofexercises = 6;

int main(void) {
    int data[] = {144, 22, 31, -24, 18, 6, 7};

    save_upgr_dogr(data);
    int upgrades[lenofexercises];
    load_upgr_dogr(upgrades);

    for (int i = 0; i <= lenofexercises; i++) {
        printf("%d ", upgrades[i]);
    }
    printf("\n");

    return 0;
}

void load_upgr_dogr(int* data) {
    FILE *f = fopen("user_upgrades", "r");

    char temp[500];
    fgets(temp, sizeof(temp), f);

    char *token = strtok(temp, ",");
    int i = 0;
    while (token != NULL && i <= lenofexercises) {
        data[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    fclose(f);
}

void save_upgr_dogr(int data[lenofexercises]) {
    FILE *file = fopen("user_upgrades", "w");

    for (int i = 0; i <= lenofexercises; i++) {
        fprintf(file, "%d ,", data[i]);
    }
    fclose(file);
}