include(ExternalProject)

ExternalProject_Add(
    cppjieba
    GIT_REPOSITORY "https://github.com/yanyiwu/cppjieba.git"
    GIT_SUBMODULES_RECURSE ON

    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

ExternalProject_Get_Property(
    cppjieba
    SOURCE_DIR
)

add_library(ExternalLimonp INTERFACE)
add_library(External::Limonp ALIAS ExternalLimonp)
target_include_directories(ExternalLimonp INTERFACE ${SOURCE_DIR}/deps/limonp/include)
target_compile_features(ExternalLimonp INTERFACE cxx_std_17)

add_library(ExternalCppjieba INTERFACE)
add_library(External::Cppjieba ALIAS ExternalCppjieba)
target_include_directories(ExternalCppjieba INTERFACE ${SOURCE_DIR}/include)
target_link_libraries(ExternalCppjieba INTERFACE ExternalLimonp)
target_compile_features(ExternalCppjieba INTERFACE cxx_std_17)
