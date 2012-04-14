#include "controller.h"

#include "SSCon/textfactory.h"
#include "framework/world.h"
#include "framework/gridobject.h"
#include <iostream>

Controller *Controller::instance_ = NULL;

Controller::Controller()
	: title_("Playground")
	, running(true)
{
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
	renderer.initWindow(720,560,32,0,title_);
	renderer.initGraphics();
	terminal.setListener(this);
	terminal.setDimension(720,560);
	terminal.setBackgroundRGBA(0,0,0,1);

	world = new World(20,20);
	player = new GridObject();
	player->setGridX(2);
	player->setGridY(2);

	world->addGridObject(player);

	while (running) {

		unsigned int duration = SDL_GetTicks() - last_step;

		if (duration > 100) {
			duration = 50;
		}

		if(!terminal.update())
		{
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				onEvent(event);
			}

			world->onStep(duration/16.0f);
		}
		last_step = SDL_GetTicks();

		renderer.startDraw();
		renderer.drawWorld(world);
		renderer.drawFrame();
		terminal.draw();
		renderer.commitDraw();
	}
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
			terminal.open();
		};
		break;
	case SDL_VIDEORESIZE:
		renderer.onResize(event.resize.w, event.resize.h);
		break;
	};
}

std::string Controller::onCommit(std::string line) {
	std::vector<std::string> commands = TextFactory::instance()->util()->split(line,' ');
	if(commands[0] == "exit") {
		terminal.close();
		running = false;

		return "";
	} else if(commands[0] == "close") {
		terminal.close();
		return "";
	}
	
	return "invalid command";
}
