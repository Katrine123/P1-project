
add_executable(main main.c)

add_library(exercises exercises)
add_library(new_user_questionnaire new_user_questionnaire)
add_library(routine routine)
add_library(evaluation_questionnaire evaluation_questionnaire)
add_executable(workouts workouts) # TODO: Change back to: add_library(workouts workouts)
add_library(lists lists)

target_link_libraries(main
        exercises
        new_user_questionnaire
        routine
        evaluation_questionnaire
        workouts
        lists)