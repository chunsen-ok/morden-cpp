add_library(mcpp INTERFACE)
target_compile_features(mcpp INTERFACE cxx_std_17)
target_include_directories(mcpp 
    INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    INTERFACE $<INSTALL_INTERFACE:include>
)
