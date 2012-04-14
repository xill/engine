set(FRAMEWORK_Headers
	world.h
	gridrule.h
	blockinggridrule.hpp
	defaultgridrule.h
	gridobject.h
	griddata.hpp
)

set(FRAMEWORK_Sources
	${FRAMEWORK_Headers}
	world.cpp
	defaultgridrule.cpp
	blockinggridrule.cpp
	gridobject.cpp
	griddata.cpp
)

add_library(framework ${FRAMEWORK_Sources})
