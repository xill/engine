set(GRAPHICS_Headers
	mainrenderer.h
	texturemanager.h
	include.h
)

set(GRAPHICS_Sources
	${GRAPHICS_Headers}
	mainrenderer.cpp
	texturemanager.cpp
)

add_library(graphics ${GRAPHICS_Sources})
