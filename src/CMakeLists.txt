include_directories(.)

# Find SDL, SDL_image and OpenGL
if (WIN32)
	set(SDL_INCLUDE_DIR ../inc/SDL/include)
	set(SDLIMAGE_INCLUDE_DIR ../inc/SDL/include)
	set(SDL_LIBRARY ${PROJECT_SOURCE_DIR}/inc/SDL/lib/SDL.lib)
	set(SDLMAIN_LIBRARY ${PROJECT_SOURCE_DIR}/inc/SDL/lib/SDLmain.lib)
	set(SDLIMAGE_LIBRARY ${PROJECT_SOURCE_DIR}/inc/SDL/lib/SDL_image.lib)
	set(SDL_LIBRARY ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})

	set(GLEW_INCLUDE_DIR ../inc/GLEW/include)
	set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/inc/GLEW/lib/glew32.lib)
else (WIN32)
	find_package(SDL REQUIRED)
	find_package(SDL_image REQUIRED)
	find_package(GLEW REQUIRED)

	if (GLEW_FOUND EQUAL 0)
		message(FATAL_ERROR "please: install glew")
	endif (GLEW_FOUND EQUAL 0)
endif (WIN32)

find_package(OpenGL REQUIRED)

include_directories(${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

add_subdirectory(graphics)
add_subdirectory(SSCon)
add_subdirectory(framework)
add_subdirectory(camera)
add_subdirectory(math)

set(GENERAL_Headers
	controller.h
)

set(GENERAL_Sources
	${GENERAL_Headers}
	controller.cpp
	main.cpp
)

add_executable(engine_project ${GENERAL_Sources})

target_link_libraries(engine_project
	${OPENGL_LIBRARIES}
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${GLEW_LIBRARY}
	SSCon
	graphics
	framework
	camera
	math
)
