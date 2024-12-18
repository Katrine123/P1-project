cmake_minimum_required(VERSION 3.14)

project(p1_project C)

set(CMAKE_C_STANDARD 11)


# Executables

add_executable(main main.c)

# Libraries

add_library(
        references
        references)
add_library(
        tools
        tools)
add_library(
        new_user_questionnaire
        new_user_questionnaire)
add_library(
        exercises
        exercises)
add_library(
        workouts
        workouts)
add_library(
        print_routine
        print_routine)
add_library(
        evaluation_questionnaire
        evaluation_questionnaire)
add_library(
        upgrade_downgrade
        upgrade_downgrade)
add_library(
        savesystem
        savesystem)

add_library(
        streak_check
        streak_check)

target_link_libraries(main
        savesystem
        evaluation_questionnaire
        streak_check
        new_user_questionnaire
        upgrade_downgrade
        exercises
        tools
        references
        workouts
        print_routine)


### STUF FOR TESTING IS HERE  ###

add_test(NAME tests COMMAND tests)

cmake_policy(SET CMP0135 NEW) # Setting this policy to NEW avoids a warning in newer versions of CMake.
include(FetchContent)
FetchContent_Declare(mtest
        URL https://github.com/MortenSchou/mtest/archive/refs/tags/v0.2.0.zip
        URL_HASH SHA256=bec1e90fb00a5bc155de12ed5ed39ea5d1a1b6fcfb6c80cce5ad3e38e360248c
)
FetchContent_MakeAvailable(mtest)

add_executable(tests tests.c)

target_link_libraries(tests
        exercises
        evaluation_questionnaire
        new_user_questionnaire
        streak_check
        savesystem
        workouts
        upgrade_downgrade
        print_routine
        tools
        references
        mtest)