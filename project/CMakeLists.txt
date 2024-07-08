# Add header files
file(GLOB_RECURSE HEADER_FILES
	${PROJECT_SOURCE_DIR}/inc/*.h
	${PROJECT_SOURCE_DIR}/inc/*.hpp
)

add_compile_definitions(PLATFORM=${BUILD_TYPE})
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)


# Define the executable
if (BUILD_TYPE EQUAL BUILD_TYPE_AGN)
	add_executable(${PROJECT_NAME} ${HEADER_FILES}
		src/win_main.cpp
		src/dr_wav.cc
	)
elseif (BUILD_TYPE EQUAL BUILD_TYPE_WIN)
	#set (WIN32_RESOURCES ${CMAKE_SOURCE_DIR}/res/resource.rc)
	add_executable(${PROJECT_NAME} ${HEADER_FILES} ${WIN_RESOURCES}
		src/win_main.cpp
		src/dr_wav.cc
	)
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(${PROJECT_NAME}
	kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32
)

# Add SubProjects
target_link_libraries(${PROJECT_NAME} OPENAL)

#  It will place subproject .dlls inside project build directory.
add_custom_command ( TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:OPENAL> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# DEBUG SubProjects
target_link_libraries(${PROJECT_NAME} SPDLOG)
target_link_libraries(${PROJECT_NAME} TracyClient)


add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_SOURCE_DIR}/project/res
	${CMAKE_CURRENT_BINARY_DIR}/res
)
