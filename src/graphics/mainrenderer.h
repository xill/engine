#ifndef MAIN_RENDERER_H
#define MAIN_RENDERER_H

#include <string>
#include <list>
#include <stdexcept>

class MainRenderer
{
private:
	float dim_w,dim_h;	
public:


	MainRenderer()
	{

	}

	void onResize(const float dim_w, const float dim_h);

	void initWindow(
		const float dim_w, const float dim_h, int bpp,
		bool fullscreen, const std::string &title);

	void initGraphics();

	void startDraw();
	void drawFrame();
	void commitDraw();

	float getWidth()
	{
		return dim_w;
	}

	float getHeight() 
	{
		return dim_h;
	}
};

#endif // MAIN_RENDERER_H
