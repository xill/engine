include_directories(..)
include_directories(.)

# http://www.vtk.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if (WIN32)
	option(STATIC_RUNTIME "Build static runtime, no need for MSVC libraries" OFF)

	if (STATIC_RUNTIME)
		set(CMAKE_USER_MAKE_RULES_OVERRIDE
		    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/c_flag_overrides.cmake)
		set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
		    ${CMAKE_CURRENT_SOURCE_DIR}/CMake/cxx_flag_overrides.cmake)
	endif(STATIC_RUNTIME)
endif(WIN32)

# Find SDL, SDL_image and OpenGL
if (WIN32)
	set(SDL_INCLUDE_DIR ../SDL/include)
	set(SDLIMAGE_INCLUDE_DIR ../SDL/include)
	set(SDL_LIBRARY ${PROJECT_SOURCE_DIR}/SDL/lib/SDL.lib)
	set(SDLMAIN_LIBRARY ${PROJECT_SOURCE_DIR}/SDL/lib/SDLmain.lib)
	set(SDLIMAGE_LIBRARY ${PROJECT_SOURCE_DIR}/SDL/lib/SDL_image.lib)
	set(SDL_LIBRARY ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})
else (WIN32)
	find_package(SDL)
	find_package(SDL_image)
endif (WIN32)

find_package(OpenGL REQUIRED)

include_directories(
	${SDL_INCLUDE_DIR}
	${SDLIMAGE_INCLUDE_DIR}
)

add_subdirectory(graphics)
add_subdirectory(SSCon)

set(GENERAL_Headers
	controller.h
)

set(GENERAL_Sources
	${GENERAL_Headers}
	controller.cpp
	main.cpp
)

add_executable(SGBuild ${GENERAL_Sources})

target_link_libraries(SGBuild
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
	${OPENGL_LIBRARIES}
	SSCon
	graphics
)
