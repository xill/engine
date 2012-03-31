#include "texturemanager.h"

TextureManager* TextureManager::m_instance = NULL;

#include <stdexcept>

TextureManager::TextureManager() : current_bind(0){

}

TextureManager* TextureManager::instance(){
	if(m_instance == 0){
		m_instance = new TextureManager();
	}
	return m_instance;
}

GLuint TextureManager::getTexture(int id){
	return textures[id];
}

void TextureManager::bindOrDoNothing(GLuint texture_id){
	if(current_bind != texture_id){
		current_bind = texture_id;
		glBindTexture(GL_TEXTURE_2D,texture_id);
	}
}

void TextureManager::mapTexture(std::string texture_path){
	texture_map.push_back(texture_path);
}

void TextureManager::loadTexture(int texture_id,int xWrap, int yWrap, GLenum type){
	SDL_Surface *textureImage = NULL;
	textureImage = IMG_Load(texture_map[texture_id].c_str());
	if (textureImage == NULL) {
		return;
	}

	GLuint gl = 0;
	glGenTextures(1, &gl);

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, gl);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xWrap);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yWrap);
			
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTexImage2D(
		GL_TEXTURE_2D, 0, 4, textureImage->w,
		textureImage->h, 0, type, GL_UNSIGNED_BYTE,
		textureImage->pixels
	);

	SDL_FreeSurface(textureImage);

	textures[texture_id] = gl;

	if(gl == 0){
		throw std::runtime_error("texture loading failed");
	}
}

void TextureManager::releaseTexture(int texture_id) {
	glDeleteTextures(1,&textures[texture_id]);
}

bool TextureManager::isValidMap(int i) {
	return (i >= 0 && i < texture_map.size());
}

bool TextureManager::isValidTexture(int i) {
	return (textures[i] > 0);
}

std::string TextureManager::idToPath(int id) {
	int index = -1;
	for(int i = 0; i < textures.size(); ++i) {
		if(textures[i] == id) {
			index = i;
			break;
		}
	}
	return (isValidMap(index))?texture_map[index]:"none";
}

int TextureManager::pathToId(std::string path) {
	int index = -1;
	for(int i = 0; i < texture_map.size(); ++i) {
		if(texture_map[i] == path) {
			index = i;
			break;
		}
	}
	return (isValidTexture(index))?textures[index]:-1;
}