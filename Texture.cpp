#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	//Assigns the type of the texture
	type = texType;

	//stores the width, height and number of colour channels of the image
	int widthImg, heightImg, numColCh;
	//Flips image so it appears right way up
	stbi_set_flip_vertically_on_load(true);
	//Loads the image and its metadata to a byte array
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//Generates OpenGL texture object
	glGenTextures(1, &ID);
	//Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	//Configures the type of algorithm used to scale the image bigger or smaller 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Configures the way the texture repeats on screen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Optional lines in case I need GL_CLAM_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed, unsupported number of colour channels.");
	
	// Generates smaller images for further away
	glGenerateMipmap(GL_TEXTURE_2D);

	//Delete the unnessecary image data as it has now beeen fully loaded to the OpenGL Texture object
	stbi_image_free(bytes);

	//Unbind OpenGL texture object so it can be accidentaly changed
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets location of Uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//Shader needs to be activated before changing the value of the uniform
	shader.Activate();
	//Applies the value to the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}