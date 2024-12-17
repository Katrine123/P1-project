
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

target_link_libraries(main
        new_user_questionnaire
        exercises
        savesystem
        evaluation_questionnaire
        upgrade_downgrade
        tools
        references
        workouts
        print_routine)
