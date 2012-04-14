#ifndef GRAPHICS_INCLUDE_H
#define GRAPHICS_INCLUDE_H

#ifdef _WIN32
#	define NOMINMAX
#	include <windows.h>
#endif

#define GL_GLEXT_PROTOTYPES 1 // get OpenGL extensions prototypes.

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef GL_TABLE_TOO_LARGE
#ifdef GL_TABLE_TOO_LARGE_EXT
#define GL_TABLE_TOO_LARGE GL_TABLE_TOO_LARGE_EXT
#else
#define GL_TABLE_TOO_LARGE 0x8031
#endif
#endif

#include "graphics/error.h"

#endif // GRAPHICS_INCLUDE_H
