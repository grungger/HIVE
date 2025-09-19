# Root CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

# Set the root project name
project(VirtualComputer)

enable_testing()

# Add subdirectories for the base_logic and derived_logic projects
add_subdirectory(base_logic)
add_subdirectory(derived_logic)
add_subdirectory(base_components)
add_subdirectory(derived_components)
add_subdirectory(Turing_Complete)
add_subdirectory(HIVEarchitecture)
#add_subdirectory(circuits)
#add_subdirectory(derived_components)

# Set global include directories for the project
# This makes the base_logic/include directory available to all targets
include_directories(${CMAKE_SOURCE_DIR}/base_logic/include)
include_directories(${CMAKE_SOURCE_DIR}/derived_logic/include)
include_directories(${CMAKE_SOURCE_DIR}/base_components/include)
include_directories(${CMAKE_SOURCE_DIR}/derived_components/include)
include_directories(${CMAKE_SOURCE_DIR}/Turing_Complete/include)
include_directories(${CMAKE_SOURCE_DIR}/HIVEarchitecture/include)
#include_directories(${CMAKE_SOURCE_DIR}/circuits/include)
#include_directories(${CMAKE_SOURCE_DIR}/derived_components/include)
