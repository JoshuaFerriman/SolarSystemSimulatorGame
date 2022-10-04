#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
	public:
		GLuint ID;
		const char* type;
		GLuint unit;

		Texture(const char* image, const char* texType, GLuint slot);

		//Assigns a texutre unit to a texture
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		//Binds a texture to current texture context
		void Bind();
		//Unbidns a texture from current texture context
		void Unbind();
		//Deletes a texture
		void Delete();
};

#endif // !TEXTURE_CLASS_H

