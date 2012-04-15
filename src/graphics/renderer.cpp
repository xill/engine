#include "graphics/renderer.hpp"
#include "graphics/error.h"

#include "math/math.hpp"

#include "camera/camera.hpp"

#include <stdexcept>
#include <functional>
#include <algorithm>
#include <iostream>

Vec2i Renderer::m_dimension;
Mat4x4f Renderer::m_projectionMatrix;

Renderer::Renderer()
	: m_features(0)
{
	//enable(kShadows | kLightFrustum);
}

Renderer::~Renderer()
{
	SDL_Quit();
}

void Renderer::initWindow(
const Vec2i &dimension, char bpp, bool fs, const std::string &title)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		throw new std::runtime_error("initialization of window failed");
	}

	m_dimension = dimension;

	// all values are "at least"
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// set title
	SDL_WM_SetCaption(title.c_str(), title.c_str());

	// set flags, opengl and double buffering on default
	int flags = (SDL_OPENGL | SDL_DOUBLEBUF);
	flags |= (fs) ? SDL_FULLSCREEN : 0;

	SDL_Surface *screen =
		SDL_SetVideoMode(m_dimension.x, m_dimension.y, bpp, flags);
	if (screen == NULL) {
		throw new std::runtime_error("init of video mode failed");
	}

	// Grab all input, doesn't let the cursor get away.
	//SDL_WM_GrabInput(SDL_GRAB_ON);
	//SDL_ShowCursor(SDL_DISABLE);

	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = m_dimension.x;
	resizeEvent.resize.h = m_dimension.y;
	SDL_PushEvent(&resizeEvent);
}

void Renderer::initGraphics()
{
	if (m_dimension.isZero()) {
		throw new std::runtime_error("init of graphics failed");
	}

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::string error("glewInit() failed: ");
		error += std::string((const char *)glewGetErrorString(err));
		throw new std::runtime_error(error);
	}

	if (GLEW_VERSION_2_0) {
		std::cout << "OpenGL 2.0 is supported, All Good :)" << std::endl;
	} else {
		std::cerr << "OpenGL 2.0 IS NOT SUPPORTED!" << std::endl;
		throw new std::runtime_error("OpenGL 2.0 NOT SUPPORTED.");
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void Renderer::onResize(const Vec2i &dimension)
{
	m_dimension = dimension;
	float aspect = (float) m_dimension.x / (float) m_dimension.y;

	glViewport(0, 0, m_dimension.x, m_dimension.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspectiveProjection(60.0f, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Renderer::setPerspectiveProjection(float fovy, float _near, float _far)
{
	float radians = 0.5f * fovy * DEGREES_2_RADIANS;
	float d       = cosf(radians) / sinf(radians);
	float aspect  = (float) m_dimension.x / (float) m_dimension.y;
	float deltaZ  = _far - _near;

	m_projectionMatrix.set(
		d / aspect, .0f, .0f                 , .0f,
		.0f       , d  , .0f                 , .0f,
		.0f       , .0f, -(_far+_near)/deltaZ, (-2*_far*_near)/deltaZ,
		.0f       , .0f, -1.0f               , .0f
	);

	glMultMatrixf(m_projectionMatrix.m);
}

const Mat4x4f &Renderer::getProjectionMatrix()
{
	return m_projectionMatrix;
}

void Renderer::drawFrame(const Camera &camera)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.setupScene();

	GL_PRINT_ERROR;
}

void Renderer::drawWorld(World* world)
{
	std::vector<GridObject*> objects = world->getGridObjects();
	std::vector<GridRule*> rules = world->getRuleSet();
	GridData*** grid = world->getGrid();
	int h = world->getGridHeight();
	int w = world->getGridWidth();
	int sizex = 20;
	int sizey = 20;

	// debug draw movement grid.

	glPushMatrix();
	for(int y = 0 ; y < h ; ++y )
	{
		glPushMatrix();
		for(int x = 0 ; x < w ; ++x )
		{
			if(!rules[grid[y][x]->ruleid]->ignoreAll())
			{
				int c = (y+x)%2;

				if(c == 0) glColor4f(.5,0,0,.5);
				else glColor4f(0,.5,0,.5);

				glPushMatrix();
				glTranslatef(0,0,grid[y][x]->elevation);

				glBegin(GL_QUADS);
				glVertex2f(0,0);
				glVertex2f(sizex,0);
				glVertex2f(sizex,sizey);
				glVertex2f(0,sizey);
				glEnd();

				glPopMatrix();
			}

			glTranslatef(sizex,0,0);
		}
		glPopMatrix();
		glTranslatef(0,sizey,0);
	}
	glPopMatrix();

	glColor4f(0,0,1,1);
	for(std::vector<GridObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		glPushMatrix();
		glTranslatef((*it)->getX(),(*it)->getY(),(*it)->getZ() - 1);

		int size = 5;

		glBegin(GL_QUADS);
		glVertex2f(-size,-size);
		glVertex2f(size,-size);
		glVertex2f(size,size);
		glVertex2f(-size,size);
		glEnd();

		glPopMatrix();
	}
}