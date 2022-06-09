cmake_minimum_required(VERSION 3.20)

project(AnyLib  
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1
include(GenerateExportHeader)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_library(AnyLib SHARED
    src/anylib.cpp
    src/session_data.cpp
    # src/private/data_private.hpp
    # src/private/data_private.cpp
)

# 2 
generate_export_header(AnyLib)

target_include_directories(AnyLib INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include"
)

set_target_properties(AnyLib PROPERTIES
    DEBUG_POSTFIX d
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_compile_definitions(AnyLib PRIVATE ANY_LIBRARY)

target_link_libraries(AnyLib 
    PRIVATE Qt6::Core
)

install(TARGETS AnyLib 
    EXPORT AnyLibTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(
    FILES $<TARGET_PDB_FILE:AnyLib>
    DESTINATION "bin"
    OPTIONAL
)

install(DIRECTORY include/anylib
    DESTINATION include
    COMPONENT AnyLib
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/AnyLib/AnyLibConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT AnyLibTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/AnyLib/AnyLibTargets.cmake"
    NAMESPACE AnyLib::
)
configure_file(cmake/AnyLibConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/AnyLib/AnyLibConfig.cmake"
    COPYONLY
)

set(ConfigPackageLocation lib/cmake/AnyLib)
install(EXPORT AnyLibTargets
    FILE AnyLibTargets.cmake
    NAMESPACE AnyLib::
    DESTINATION ${ConfigPackageLocation}
)
install(FILES 
    cmake/AnyLibConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/AnyLib/AnyLibConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation}
    COMPONENT Core
)
