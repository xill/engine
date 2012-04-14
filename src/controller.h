#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SSCon/terminallistener.h"

#include "math/vec2.hpp"
#include "framework/gridobject.h"

#include <string>

class Renderer;
class Camera;
class Terminal;

union SDL_Event;
struct Object;

class Controller : public TerminalListener
{
protected:

	const std::string title_;

	static Controller *instance_;
	/** singleton */
	Controller();
	~Controller();

	Renderer* renderer;
	Terminal* terminal;
	Camera *m_camera;

	GridObject* player;

	bool running;

	// mouse events
	bool m_mouseLeft, m_mouseRight;
	Vec2i m_mousemotion;
	float m_zoomFactor;

	void onEvent(const SDL_Event &event);

	void onMouseButtonDown(const Vec2i &cursor);
	void onMouseMotion(const Vec2i &motion);

	void onResize(const Vec2i &dimension);

public:

	static Controller *instance();
	
	std::string onCommit(std::string);
	void run();

private:

};

#endif // CONTROLLER_H
