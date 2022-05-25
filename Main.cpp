#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"












//Vertices coordinates for a triangle
GLfloat vertices[] =
{	//						COORDINATES						 /			COLOURS			 //
	-0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,		 0.992f, 0.917f, 0.384f,	 // Lower left corner
	0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,		 0.992f, 0.917f, 0.384f,	 // Lower right corner
	0.0f,		0.5f * float(sqrt(3)) * 2 / 3,	0.0f,		 0.992f, 0.917f, 0.384f,	 // Upper corner
	-0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f,		 0.992f, 0.529f, 0.384f,	 // Inner left
	0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f,		 0.992f, 0.529f, 0.384f,	 // Inner right
	0.0f,		-0.5f * float(sqrt(3)) / 3,		0.0f,		 0.992f, 0.529f, 0.384f		 // Inner down
};

//Vertices coordinates for a square?
GLfloat verticesSquare[] =
{
	-0.5f, -0.5f , 0.0f, //lower left corner
	0.5f, -0.5f , 0.0f, //Lower right corner
	0.5f, 0.5f , 0.0f, //Upper corner
	-0.5f, 0.5f , 0.0f //lower left corner
};

GLuint indicesSquare[] =
{
	0, 1, 2, //Bottom triangle
	0, 3, 2  //Top triangle
};

GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main() 
{
	//Initialise GLFW
	glfwInit();

	//Tell GLFW which version of OpenGL we are using
	//For Example we are using 3.3.7 here
	//Only first two need to be given
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW to use the core profile
	//No need for backwards compatible functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a 800 by 800 window, with a placeholder title
	GLFWwindow* window = glfwCreateWindow(800,800, "Placeholder: SolarSystemSImGame", NULL, NULL);
	//Check that the window actually managed to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window you fucking nerd" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Add the window to the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Set the viewport of OpenGL inside the window
	//Set it to 800 by 800 to cover whole window
	glViewport(0, 0, 800, 800);



	//Load the vertices and fragment shaders we want
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verticesSquare, sizeof(verticesSquare));
	EBO EBO1(indicesSquare, sizeof(indicesSquare));

	//Link VBO attributes such as coordinates and colours to VBO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//Unbind all so we dont accidentaly modify
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	/*
	GLfloat scale {0.00f};
	short direction{ 1 };
	*/

	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Specify background colour
		glClearColor(0.211f, 0.082f, 0.298f, 1.0f);
		//Clean the back buffer and assing the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		/*
		//Make scale increase and decrease
		if (scale >= 1)
		{
			direction = -1;
		}
		else if (scale <= -1)
		{
			direction = 1;
		};
		scale += direction * 0.0005f;
		*/

		//Assigns a value to uniform scale
		glUniform1f(uniID, 0.5);

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,  0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Handle all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Delete window before terminating program
	glfwDestroyWindow(window);
	//Terminate GLFW before closing the program
	glfwTerminate();
	return 0;
}