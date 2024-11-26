
add_executable(main main.c)

add_library(bib bib
        savesystem.c
        savesystem.h)
add_library(exercises exercises)
add_library(new_user_questionnaire new_user_questionnaire)
add_library(routine routine)
add_library(evaluation_questionnaire evaluation_questionnaire)
add_library(tools tools)

target_link_libraries(main
        bib
        exercises
        new_user_questionnaire
        routine
        evaluation_questionnaire
        tools)