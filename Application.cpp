#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

int main()
{
	GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "UNIFORMS", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(5);

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

	{
		unsigned int indices[6] = {
        	0, 1, 2,
        	2, 3, 0
    	};

    	float positions[8] = {
        	-0.5f, -0.5f,
         	 0.5f, -0.5f,
         	 0.5f,  0.5f,
        	-0.5f,  0.5f
    	};

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);

		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

    	std::string vertexShader =
    	"#version 330 core\n"
    	"\n"
    	"layout(location = 0) in vec4 position;\n"
    	"\n"
    	"void main()\n"
    	"{\n"
    	"   gl_Position = position;\n"
    	"}\n";

    	std::string fragmentShader =
    	"#version 330 core\n"
    	"\n"
    	"layout(location = 0) out vec4 color;\n"
    	"\n"
    	"uniform vec4 u_Color;\n"
    	"\n"
    	"void main()\n"
    	"{\n"
    	"   color = u_Color;\n"
    	"}\n";

		Shader shader("shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		va.UnBind();
    	shader.Unbind();
		vb.UnBind();
		ib.UnBind();

    	float r = 0.0f;
    	float increment = 0.05f;

    	/* Loop until the user closes the window */
    	while (!glfwWindowShouldClose(window))
    	{
        	/* Render here */
        	glClear(GL_COLOR_BUFFER_BIT);

        	shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			va.Bind();
			ib.Bind();

        	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        	if(r > 1.0f)
            	increment = -0.05f;
       		else if(r < 1.0f)
            	increment = 0.05f;

        	r += increment;

        	/* Swap front and back buffers */
        	glfwSwapBuffers(window);

        	/* Poll for and process events */
        	glfwPollEvents();
		}
	}

    glfwTerminate();
    return 0;

}
