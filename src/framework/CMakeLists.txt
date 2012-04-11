set(FRAMEWORK_Headers
	world.h
	gridrule.h
	defaultgridrule.h
	gridobject.h
	griddata.hpp
)

set(FRAMEWORK_Sources
	${FRAMEWORK_Headers}
	world.cpp
	defaultgridrule.cpp
	gridobject.cpp
	griddata.cpp
)

add_library(framework ${FRAMEWORK_Sources})
