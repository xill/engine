#include "controller.h"

#include "graphics/include.h"

#include "camera/camera.hpp"
#include "camera/look_at.hpp"

#include "graphics/renderer.hpp"

#include "SSCon/terminal.h"

#include "framework/world.h"
#include "framework/gridobject.h"

#include <iostream>

static Vec3f start;
static Vec3f end;
static Vec3f point;
static bool intersection = false;

Controller *Controller::instance_ = NULL;

Controller::Controller()
	: title_("Playground")
	, running(true)
	, renderer(new Renderer())
	, terminal(new Terminal())
	, m_camera(0)
	, player(0)
	, m_mouseLeft(false)
	, m_mouseRight(false)
{
}

Controller::~Controller()
{
	delete renderer;
	delete terminal;
}

Controller *Controller::instance()
{
	if (instance_ == NULL) {
		instance_ = new Controller();
	}

	return instance_;
}

void Controller::run()
{
	unsigned int last_step = 0;
	float dt = 0;
	renderer->initWindow(Vec2i(720,560),32,0,title_);
	renderer->initGraphics();
	terminal->setListener(this);
	terminal->setDimension(720,560);
	terminal->setBackgroundRGBA(.2,.2,.2,.3);

	player = new GridObject();
	player->setGridX(2);
	player->setGridY(2);

//	m_camera = new LookAt(player , Vec3f(10,0,0), Vec3f(0,1,0));
	m_camera = new LookAt(Vec3f(0,0,50),Vec3f(0,0,0), Vec3f(0,1,0));

	World* world = new World(20,20);

	world->addGridObject(player);

	while (running) {

		unsigned int duration = SDL_GetTicks() - last_step;

		if (duration > 100) {
			duration = 50;
		}

		last_step = SDL_GetTicks();

		m_zoomFactor = 1.0f;
		m_mousemotion.setZero();

		if(!terminal->update())
		{
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				onEvent(event);
			}

			world->onStep(duration/16.0f);
		}

		if (!m_mousemotion.isZero()) {
			Vec2f mv(-m_mousemotion.x, m_mousemotion.y);
			mv *= DEGREES_2_RADIANS * .1f;
			m_camera->onCameraMotion(mv);
		}

		if (m_zoomFactor != 1.0f) {
			m_camera->onCameraZoom(m_zoomFactor);
			m_camera->updateModelViewMatrix();
		}

		renderer->drawFrame(*m_camera);
		glColor4f(0.0, 1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f(start.x, start.y, start.z);
			glVertex3f(end.x, end.y, end.z);
		glEnd();

		if (intersection) {
			glPushAttrib(GL_POINT_BIT);
			glPointSize(10.0f);
			glBegin(GL_POINTS);
				glVertex3f(point.x, point.y, point.z);
			glEnd();
			glPopAttrib();
		}

		glPushAttrib(GL_POINT_BIT);
			glPointSize(10.0f);
			glBegin(GL_POINTS);
				glVertex3f(player->getX(), player->getY(), player->getZ());
			glEnd();
		glPopAttrib();

		renderer->drawWorld(world);
		terminal->draw();
		renderer->swapBuffers();
	}

	delete m_camera;
	delete player;
}

void Controller::onEvent(const SDL_Event &event)
{
	switch (event.type) {

	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {

		case SDLK_ESCAPE:
			running = false;
			break;
		default:
			break;
		};
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {

		case SDLK_UP:
			player->setYOffset(-1);
			break;
		case SDLK_DOWN:
			player->setYOffset(1);
			break;
		case SDLK_LEFT:
			player->setXOffset(-1);
			break;
		case SDLK_RIGHT:
			player->setXOffset(1);
			break;
		case SDLK_HOME:
			terminal->open();
		};
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch(event.button.button) {

		case SDL_BUTTON_LEFT:
			m_mouseLeft = true;
			onMouseButtonDown(Vec2i(event.button.x,event.button.y));
			break;

		case SDL_BUTTON_RIGHT:
			m_mouseRight = true;
			onMouseButtonDown(Vec2i(event.button.x,event.button.y));
			break;

		case SDL_BUTTON_WHEELDOWN:
			m_zoomFactor += 0.1f;
			break;

		case SDL_BUTTON_WHEELUP:
			m_zoomFactor -= 0.1f;
			break;

		default:
			break;

		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch(event.button.button) {

		case SDL_BUTTON_LEFT:  m_mouseLeft = false; break;
		case SDL_BUTTON_RIGHT: m_mouseRight = false; break;
		default: break;

		}
		break;

	case SDL_VIDEORESIZE:
		onResize(Vec2i(event.resize.w, event.resize.h));
		break;

	case SDL_MOUSEMOTION:
		onMouseMotion(Vec2i(event.motion.xrel, event.motion.yrel));
		break;

	default:
		break;
	};
}

void Controller::onMouseButtonDown(const Vec2i &cursor)
{
	if (m_mouseLeft) {
		start = m_camera->screenSpacePointTo3DRay(cursor, 0);
		end = m_camera->screenSpacePointTo3DRay(cursor, 1);
		//intersection = prane->getRayIntersection(point, start, end);
	}
}

void Controller::onMouseMotion(const Vec2i &motion)
{
	if (m_mouseRight) {
		m_mousemotion += motion;
	}
}

void Controller::onResize(const Vec2i &dimension)
{
	//m_dimension = dimension;
	renderer->onResize(dimension);
}

std::string Controller::onCommit(std::string line) {
	std::vector<std::string> commands = TextFactory::instance()->util()->split(line,' ');
	if(commands[0] == "exit") {
		terminal->close();
		running = false;

		return "";
	} else if(commands[0] == "close") {
		terminal->close();
		return "";
	}
	
	return "invalid command";
}
