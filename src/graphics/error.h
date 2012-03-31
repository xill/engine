#ifndef MAI_ERROR_H_
#define MAI_ERROR_H_

#include "graphics/include.h"

static unsigned int last_state = -1; // make sure to print first state.

// Helper macro.
#define CASE(x) \
	case ((x)): \
		if ((x) != last_state) { \
			printf("OpenGL STATE: %s\n", #x); \
			last_state = (x); \
		} \
		break;

// macro that is given value from glGetError()
// prints user-friendly message once.
//
// Guaranteened not to flood.
//
// @returns with the same value as glGetError. 0 means OK.
#define GL_PRINT_ERROR \
	switch (glGetError()) { \
	CASE(GL_NO_ERROR); \
	CASE(GL_INVALID_ENUM); \
	CASE(GL_INVALID_VALUE); \
	CASE(GL_INVALID_OPERATION); \
	CASE(GL_STACK_OVERFLOW); \
	CASE(GL_STACK_UNDERFLOW); \
	CASE(GL_OUT_OF_MEMORY); \
	CASE(GL_TABLE_TOO_LARGE); \
	}


#endif // MAI_ERROR_H_
