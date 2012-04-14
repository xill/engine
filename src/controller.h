#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <list>
#include <SSCon/text_include.h>

#include "graphics/mainrenderer.h"
#include "graphics/texturemanager.h"
#include "SSCon/terminallistener.h"
#include "SSCon/terminal.h"

union SDL_Event;
struct Object;

class Controller : public TerminalListener
{
protected:

	const std::string title_;

	static Controller *instance_;
	/** singleton */
	Controller();

	MainRenderer renderer;
	Terminal terminal;

	bool running;

	World* world;
	GridObject* player;

public:

	static Controller *instance();
	void onEvent(const SDL_Event &event);
	std::string onCommit(std::string);
	void run();

private:

};

#endif // CONTROLLER_H
