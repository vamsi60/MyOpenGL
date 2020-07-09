#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
//#include "VertexBuffer.h"

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char * src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TO DO Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {   
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"; 
        std::cout << std::endl;

        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }   

    return id; 
    
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}


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

    	unsigned int shader = CreateShader(vertexShader, fragmentShader);
    	glUseProgram(shader);

    	int location = glGetUniformLocation(shader, "u_Color");
    	glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

		va.UnBind();
    	glUseProgram(0);
    	glBindBuffer(GL_ARRAY_BUFFER, 0);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    	float r = 0.0f;
    	float increment = 0.05f;

    	/* Loop until the user closes the window */
    	while (!glfwWindowShouldClose(window))
    	{
        	/* Render here */
        	glClear(GL_COLOR_BUFFER_BIT);

        	glUseProgram(shader);
        	glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

        	//glBindVertexArray(vao);
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

    	glDeleteProgram(shader);
	}

    glfwTerminate();
    return 0;

}
