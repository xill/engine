set(GRAPHICS_Headers
	renderer.hpp
	texturemanager.h
	include.h
)

set(GRAPHICS_Sources
	${GRAPHICS_Headers}
	renderer.cpp
	texturemanager.cpp
)

add_library(graphics ${GRAPHICS_Sources})
