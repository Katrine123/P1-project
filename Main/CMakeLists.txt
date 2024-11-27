
add_executable(main main.c)

add_library(exercises exercises)
add_library(new_user_questionnaire new_user_questionnaire)
add_library(routine routine)
add_library(evaluation_questionnaire evaluation_questionnaire)
add_library(workouts workouts)

target_link_libraries(main
        exercises
        new_user_questionnaire
        routine
        evaluation_questionnaire
        workouts)