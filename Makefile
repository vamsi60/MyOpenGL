CXX = g++
CXXFLAGS = -Wall -g -std=c++11

MyApp : Application.o VertexArray.o Shader.o VertexBuffer.o IndexBuffer.o
	$(CXX) $(CXXFLAGS) -o MyApp Application.o VertexArray.o Shader.o VertexBuffer.o IndexBuffer.o -L /home/vamsi/vamsi/OpenGL/practice/glew/build/lib -lGLEW -lglfw -lGL

Application.o : Application.cpp VertexArray.h IndexBuffer.h
	$(CXX) $(CXXFLAGS) -c Application.cpp

VertexArray.o : VertexArray.h

VertexBuffer.o : VertexBuffer.h

IndexBuffer.o : IndexBuffer.h

Shader.o : Shader.h

