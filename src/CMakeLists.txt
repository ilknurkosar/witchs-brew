cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

project(index LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
add_subdirectory(dependencies)

set(RESOURCE_DIRECTORY
		resources
)
add_custom_target(copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/${RESOURCE_DIRECTORY}
	${CMAKE_BINARY_DIR}/${RESOURCE_DIRECTORY}
	COMMENT "Copying resourcess into binary dir"
)

set(MISC_DIRECTORY
		misc
)
add_custom_target(copy_misc ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/${MISC_DIRECTORY}
	${CMAKE_BINARY_DIR}/${MISC_DIRECTORY}
	COMMENT "Copying misc into binary dir"
)

set(SOURCE_FILES
		main.cpp
		customTextures.cpp
#		raylib_game.c
#		screen_ending.c
#		screen_gameplay.c
#		screen_logo.c
#		screen_options.c
#		screen_title.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_dependencies(${PROJECT_NAME} copy_resources copy_misc)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} PRIVATE
	raylib
	raylib_cpp
	raygui
)

target_include_directories(${PROJECT_NAME} PRIVATE
	headers
)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
	set(WEB_SHELL_FILE ${MISC_DIRECTORY}/minshell.html)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
	set(EMSCRIPTEN_DIR ${CMAKE_TOOLCHAIN_FILE})
	cmake_path(REMOVE_FILENAME EMSCRIPTEN_DIR)
	target_link_options(${PROJECT_NAME} PRIVATE
		"-sUSE_GLFW=3"
		"-sASSERTIONS=1"
		"-sWASM=1"
		"-sASYNCIFY"
		"--preload-file=${RESOURCE_DIRECTORY}"
#		"-sMAX_WEBGL_VERSION=2"
		$<$<NOT:$<CONFIG:Debug>>:
			"--shell-file=${WEB_SHELL_FILE}"
		>
		)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()