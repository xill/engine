#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "graphics/include.h"
#include "math/vec2.hpp"
#include "math/mat4x4.hpp"

#include <vector>
#include "framework/world.h"
#include "framework/gridobject.h"

#include <string>

class Camera;

class Renderer
{
public:
	// optional features of the renderer will be listed here.
	enum FeatureFlags {
		// kShadows      = (1 << 0),
		// kLightFrustum = (1 << 1),
	};

private:
	// FeatureFlags.
	unsigned int m_features;

	static Vec2i m_dimension;

	static Mat4x4f m_projectionMatrix;

public:
	Renderer();
	~Renderer();

	/**
	 * Initializes windows that will be filled with graphics.
	 * call this before calling any other function from this class.
	 *
	 * @throws RuntimeException if fails.
	 */
	void initWindow(
		const Vec2i &dimension, char bpp, bool fs,
		const std::string &title);

	/**
	 * Initializes openGL on the created window, must be called after
	 * InitWindow
	 *
	 * @throws RuntimeException if fails.
	 */
	void initGraphics();

	void drawFrame(const Camera &camera);

	void drawWorld(World* world);

	static void onResize(const Vec2i &dimension);
	static int getWidth();
	static int getHeight();

	void swapBuffers();

	/**
	 * Sets up my perspective.
	 *
	 * Caches the perspective projection into m_projectionMatrix.
	 *
	 * gluPerspective has been DEPRECATED since OpenGL 3.1
	 */
	static void setPerspectiveProjection(float fovy, float near, float far);

	static const Mat4x4f &getProjectionMatrix();

	/**
	 * disable some features.
	 *
	 * @param flag that contains features to be disabled.
	 */
	void disable(int flags);

	/**
	 * enable some features.
	 *
	 * @param flag that contains features to be enabled.
	 */
	void enable(int flags);

	/**
	 * toggle features.
	 *
	 * @param flags that contains features to toggle.
	 */
	void toggle(int flags);

	/**
	 * Check if some flag(s) are enabled.
	 *
	 * @param flag(s) to test.
	 *
	 * @return true if all given flags are enabled.
	 */
	bool isEnabled(int flags);
};

inline void Renderer::swapBuffers()
{
	SDL_GL_SwapBuffers();
}

inline int Renderer::getWidth()
{
	return m_dimension.x;
}

inline int Renderer::getHeight()
{
	return m_dimension.y;
}

inline void Renderer::disable(int flags)
{
	m_features &= ~(flags);
}

inline void Renderer::enable(int flags)
{
	m_features |= flags;
}

inline void Renderer::toggle(int flags)
{
	m_features ^= flags;
}

inline bool Renderer::isEnabled(int flags)
{
	return (m_features & flags);
}

#endif // RENDERER_HPP
