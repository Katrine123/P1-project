//
// Created by Luna on 11/14/2024.
//
#pragma once
typedef struct {
    char available_equipment[20];
    char age[20];
    char gender[20];
    char weight[20];
    char height[20];
    char pushups[20];
    char fitness_level[20];
    char time_available_week[20];
    char adjustmentfactor[20];
} user_save_data;

#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

int check_for_save();

int save_data();

void user_save();

void print_user_data();

user_save_data load_data();

#endif //SAVESYSTEM_H
