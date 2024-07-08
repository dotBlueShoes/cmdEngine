include(CPM)

# OPENAL
set(OPENAL_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/openal/include)
add_library(OPENAL SHARED IMPORTED GLOBAL)
set_property(TARGET OPENAL PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/lib/release/OpenAL32.lib)
set_property(TARGET OPENAL PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/bin/release/OpenAL32.dll)
set_property(TARGET OPENAL PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/lib/debug/OpenAL32.lib)
set_property(TARGET OPENAL PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/bin/debug/OpenAL32.dll)
target_include_directories(OPENAL INTERFACE ${OPENAL_INC_DIR})

# SPDLOG
set(SPDLOG_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/spdlog/include)
add_library(SPDLOG INTERFACE)
target_include_directories(SPDLOG INTERFACE ${SPDLOG_INC_DIR})

# Didn't work!
# TRACY
#option(TRACY_ENABLE "" ON)
#option(TRACY_ON_DEMAND "" ON)
#set(TRACY_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/tracy)
#set(TRACY_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/tracy)
#add_library(TRACY STATIC
#		${TRACY_SRC_DIR}/TracyClient.cpp
#)
#target_include_directories(TRACY PUBLIC ${TRACY_INC_DIR})
#add_subdirectory(${TRACY_INC_DIR})

# This does!
FetchContent_Declare (
	tracy
	GIT_REPOSITORY https://github.com/wolfpld/tracy.git
	GIT_TAG v0.10
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable (tracy)
target_compile_options(TracyClient PUBLIC -Wno-format)