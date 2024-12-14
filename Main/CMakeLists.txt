
# Executables

add_executable(main main.c)
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


target_link_libraries(main
        references
        tools
        new_user_questionnaire
        exercises
        workouts)

# Libraries

#add_library(
#        references
#        references)
#target_link_libraries(main
#        references)
#add_library(
#        tools
#        tools)
#target_link_libraries(main
#        tools)
#add_library(
#        new_user_questionnaire
#        new_user_questionnaire)
#target_link_libraries(main
#        new_user_questionnaire)
#add_library(
#        evaluation_questionnaire
#        evaluation_questionnaire)
#target_link_libraries(main
#        evaluation_questionnaire)
#add_library(
#        exercises
#        exercises)
#target_link_libraries(main
#        exercises)
#add_library(
#        print_routine
#        print_routine)
#target_link_libraries(main
#        print_routine)
#add_library(
#        savesystem
#        savesystem)
#target_link_libraries(main
#        savesystem)
#add_library(
#        upgrade_downgrade
#        upgrade_downgrade)
#target_link_libraries(main
#        upgrade_downgrade)
#add_library(
#        workouts
#        workouts)
#target_link_libraries(main
#        workouts)