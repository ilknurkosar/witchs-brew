cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

project(index LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(C_SOURCE_FILES
		raylib_game.c
		screen_ending.c
		screen_gameplay.c
		screen_logo.c
		screen_options.c
		screen_title.c
)


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

add_executable(${PROJECT_NAME} ${C_SOURCE_FILES})
add_dependencies(${PROJECT_NAME} copy_resources copy_misc)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
	set(WEB_SHELL_FILE ${MISC_DIRECTORY}/minshell.html)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
	target_link_options(${PROJECT_NAME} PRIVATE
		"-sUSE_GLFW=3"
		"-sASSERTIONS=1"
		"-sWASM=1"
		"-sASYNCIFY"
		"--preload-file=${RESOURCE_DIRECTORY}"
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