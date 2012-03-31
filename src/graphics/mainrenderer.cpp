#include "graphics/mainrenderer.h"

#include "graphics/error.h"

void MainRenderer::onResize(const Vec2f &dimension) {
	this->dimension = dimension;

	glViewport(0, 0, dimension.x, dimension.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(
		0, dimension.x,
		dimension.y, 0,
		-1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainRenderer::initWindow(
	const Vec2f &dimension, int bpp,
	bool fullscreen, const std::string &title)
{
	if(SDL_Init(SDL_INIT_VIDEO) == 1){
		throw std::runtime_error("Runtime Error: SDL window init error.");
	}

	this->dimension = dimension;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption(title.c_str(), title.c_str());

	int flags = (SDL_OPENGL | SDL_DOUBLEBUF);
	flags |= (fullscreen) ? SDL_FULLSCREEN : 0;

	SDL_Surface *screen = SDL_SetVideoMode(dimension.x, dimension.y, bpp, flags);
	if (screen == NULL) {
		throw std::runtime_error("Runtime Error: SDL surface init error.");
	}

	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = dimension.x;
	resizeEvent.resize.h = dimension.y;
	SDL_PushEvent(&resizeEvent);
}
	
void MainRenderer::initGraphics() {
	if (!dimension.x || !dimension.y) {
		throw std::runtime_error("Runtime Error: Window not initialized.");
	}

	glClearColor(.0f,.0f,0.0f,1.0f);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//	glAlphaFunc(GL_LESS,0.3f);
}

void MainRenderer::startDraw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
}

void MainRenderer::drawFrame() {
	/*
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex2f(20,20);
	glVertex2f(30,20);
	glVertex2f(30,30);
	glVertex2f(20,30);
	glEnd();
	*/
	GL_PRINT_ERROR;
}

void MainRenderer::commitDraw() {
		SDL_GL_SwapBuffers();
}

Vec3f MainRenderer::unProject(const Vec2f &cursor)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble x, y, z;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	gluUnProject(
		cursor.x, cursor.y, 1.0f,
		modelview, projection, viewport,
		&x, &y, &z);

	return Vec3f(x, y, z);
}
