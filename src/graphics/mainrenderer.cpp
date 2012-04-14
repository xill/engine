#include "graphics/mainrenderer.h"

#include "graphics/error.h"

void MainRenderer::onResize(const float dim_w, const float dim_h) {
	this->dim_w = dim_w;
	this->dim_h = dim_h;

	glViewport(0, 0, dim_w, dim_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(
		0, dim_w,
		dim_h, 0,
		-1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainRenderer::initWindow(
	const float dim_w, const float dim_h, int bpp,
	bool fullscreen, const std::string &title)
{
	if(SDL_Init(SDL_INIT_VIDEO) == 1){
		throw std::runtime_error("Runtime Error: SDL window init error.");
	}

	this->dim_w = dim_w;
	this->dim_h = dim_h;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption(title.c_str(), title.c_str());

	int flags = (SDL_OPENGL | SDL_DOUBLEBUF);
	flags |= (fullscreen) ? SDL_FULLSCREEN : 0;

	SDL_Surface *screen = SDL_SetVideoMode(dim_w, dim_h, bpp, flags);
	if (screen == NULL) {
		throw std::runtime_error("Runtime Error: SDL surface init error.");
	}

	SDL_Event resizeEvent;
	resizeEvent.type = SDL_VIDEORESIZE;
	resizeEvent.resize.w = dim_w;
	resizeEvent.resize.h = dim_h;
	SDL_PushEvent(&resizeEvent);
}
	
void MainRenderer::initGraphics() {
	if (!dim_w || !dim_h) {
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

void MainRenderer::drawWorld(World* world)
{
	std::vector<GridObject*> objects = world->getGridObjects();
	int h = world->getGridHeight();
	int w = world->getGridWidth();
	int sizex = 20;
	int sizey = 20;

	// debug draw movement grid.

	glPushMatrix();
//	glTranslatef(sizex * w * 0.5,sizey * h * 0.5,0);
	for(int y = 0 ; y < h ; ++y )
	{
		glPushMatrix();
		for(int x = 0 ; x < w ; ++x )
		{
			int c = (y+x)%2;

			if(c == 0) glColor4f(.5,0,0,.5);
			else glColor4f(0,.5,0,.5);

			glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(sizex,0);
			glVertex2f(sizex,sizey);
			glVertex2f(0,sizey);
			glEnd();

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
		glTranslatef((*it)->getX(),(*it)->getY(),0);

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
