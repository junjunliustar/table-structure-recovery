cmake_minimum_required(VERSION 3.10)
project(TableStructureRecovery VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/table_restoration.cpp
)

# Create library
add_library(table_restoration STATIC ${SOURCES})

# Create example executable
add_executable(table_restoration_example examples/example.cpp)
target_link_libraries(table_restoration_example table_restoration)

# Installation rules
install(TARGETS table_restoration
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES include/table_restoration.h
    DESTINATION include
)

# Print build information
message(STATUS "Table Structure Recovery Library")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
