

add_executable(main-kode main-kode.c)
add_library(bib bib)
target_link_libraries(main-kode bib)