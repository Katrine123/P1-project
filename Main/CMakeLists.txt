
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
        exercises
        savesystem.c
)
add_library(
        workouts
        workouts)
add_library(
        print_routine
        print_routine)


target_link_libraries(main
        new_user_questionnaire
        exercises
        workouts
        print_routine
        tools
        references)
