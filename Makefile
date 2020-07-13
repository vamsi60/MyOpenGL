CXX = g++
CXXFLAGS = -Wall -g -std=c++11

IDIR = vendor/stb_image

LFLAGS = -L /home/vamsi/vamsi/OpenGL/practice/glew/build/lib
LIBS = -lGLEW -lglfw -lGL

MyApp : Application.o VertexArray.o Shader.o Renderer.o Texture.o VertexBuffer.o IndexBuffer.o
	$(CXX) $(CXXFLAGS) -o MyApp Application.o VertexArray.o Shader.o Renderer.o Texture.o VertexBuffer.o IndexBuffer.o $(LFLAGS) $(LIBS)

Application.o : Application.cpp VertexArray.h Shader.h Renderer.h Texture.h IndexBuffer.h
	$(CXX) $(CXXFLAGS) -c Application.cpp

VertexArray.o : VertexArray.h

VertexBuffer.o : VertexBuffer.h

IndexBuffer.o : IndexBuffer.h

Shader.o : Shader.h

Renderer.o : Renderer.h

Texture.o : Texture.h

clean :
	rm *.o MyApp
