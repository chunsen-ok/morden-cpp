add_library(mcpp::algos INTERFACE IMPORTED)
target_include_directories(mcpp::algos 
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/../include)
