cmake_minimum_required(VERSION 3.27 FATAL_ERROR)


project(cmdEngine VERSION 0.1.0)

# --- Includes
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(properties)

# --- Dependencies
add_subdirectory(dependencies)

# --- Project's sources
add_subdirectory(project)
