add_executable(main main.c)

add_executable(workouts workouts.c) # TODO: Change back to: add_library(workouts workouts)

add_library(exercises exercises)
add_library(new_user_questionnaire new_user_questionnaire)
add_library(routine routine)
add_library(evaluation_questionnaire evaluation_questionnaire)
add_library(lists lists)