#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#ifdef _WIN32
#	include <unordered_map>
#else
#	include <tr1/unordered_map>
#endif
#include <string>
#include <vector>
#include "SSCon/text_include.h"

class TextureManager {

public:
	~TextureManager(){
		delete m_instance;
	}

	static TextureManager* instance();

	GLuint getTexture(int id);
	void mapTexture(std::string texture_path);
	void loadTexture(int ,int xWrap, int yWrap, GLenum = GL_RGBA);
	void releaseTexture(int texture_id);

	void bindOrDoNothing(GLuint texture_id);

	bool isValidMap(int i);
	bool isValidTexture(int i);

	std::vector<std::string> getMapped() { return texture_map; }

	std::string idToPath(int id);
	int pathToId(std::string);

private:
	TextureManager();

	static TextureManager *m_instance;
	GLuint current_bind;

	std::vector<std::string> texture_map;
	std::tr1::unordered_map<int,GLuint> textures;
};

#endif
