cmake_minimum_required(VERSION 3.10)
project(Dark_age)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Include directory
include_directories(include)
# Source files (add more as you create them)
set(SOURCES
        src/main.cpp
        # src/recipe.cpp # Uncomment when you create implementation files
        # src/recipe_manager.cpp
)
# Create executable
add_executable(recipe_manager ${SOURCES})