target_include_directories(${PROJECT_NAME} PRIVATE
	include
)
target_sources(${PROJECT_NAME}
	PRIVATE
		customTextures.cpp
		MainLoop.cpp
)

add_subdirectory(Renderer)