set(CAMERA_Headers
	camera.hpp
	look_at.hpp
	follow_point.hpp
)

set(CAMERA_Sources
	${CAMERA_Headers}
	camera.cpp
	look_at.cpp
)

add_library(camera ${CAMERA_Sources})
