#ifndef MAIN_RENDERER_H
#define MAIN_RENDERER_H

#include <string>
#include <list>
#include <stdexcept>

#include "math/vec2.h"
#include "math/vec3.h"

class MainRenderer
{
private:
	Vec2f dimension;
public:


	MainRenderer()
	{

	}

	void onResize(const Vec2f &dimension);

	void initWindow(
		const Vec2f &dimension, int bpp,
		bool fullscreen, const std::string &title);

	void initGraphics();

	void startDraw();
	void drawFrame();
	void commitDraw();

	Vec2f getDimension() const {
		return dimension;
	}

	/**
	 * NeHe: Using gluUnProject
	 * http://nehe.gamedev.net/article/using_gluunproject/16013/
	 *
	 * Find the 3d coordinate that cursor is hitting
	 *
	 * @return pos
	 */
	static Vec3f unProject(const Vec2f &cursor);

};

#endif // MAIN_RENDERER_H
