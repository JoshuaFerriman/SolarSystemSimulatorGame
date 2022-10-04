#include"Model.h"
#include"SphereGenerator.h"

 int width{ 800 };
 int height{ 800 };

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
	GLFWwindow* window = glfwCreateWindow(width, height, "SolarSystemSimGame", NULL, NULL);

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
	//Set it to width by height constants to cover whole window
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Shader outliningProgram("outlining.vert", "outlining.frag");
	Shader sunShaderProgram("light.vert", "light.frag");


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(sunShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(sunShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glUniform4f(glGetUniformLocation(sunShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(sunShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Enables the Stencil Buffer
	//glEnable(GL_STENCIL_TEST);
	// Sets rules for outcomes of stecil tests
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


	

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	
	SphereGenerator sphereGenerator;
	Mesh mesh = sphereGenerator.CreateSphereMesh(0);
	Model model("models/cube/cube.gltf");

	//sphereGenerator.~SphereGenerator();
	

	
	

	//Model model("models/sword/scene.gltf");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background colour
		glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
		// Clean the back buffer and assing the new colour to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Handles Camera Inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Make it so the stencil test always passes
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		// Enable modifying of the stencil buffer
		//glStencilMask(0xFF);
		

		//Draw a model
		//model.Draw(shaderProgram, camera);


		/*
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		outliningProgram.Activate();
		glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
		model.Draw(outliningProgram, camera);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
		*/

		
		//mesh.Draw(shaderProgram, camera);
		model.Draw(lightShaderProgram, camera);
		


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Handle all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects we've created
	shaderProgram.Delete();
	//Delete window before terminating program
	glfwDestroyWindow(window);
	//Terminate GLFW before closing the program
	glfwTerminate();
	return 0;
}