CXX = g++
CXXFLAGS = -Wall -g -std=c++11

MyApp : Application.o VertexArray.o VertexBuffer.o IndexBuffer.o
	$(CXX) $(CXXFLAGS) -o MyApp Application.o VertexArray.o VertexBuffer.o IndexBuffer.o -L /home/vamsi/vamsi/OpenGL/practice/glew/build/lib -lGLEW -lglfw -lGL

Application.o : Application.cpp VertexArray.h IndexBuffer.h
	$(CXX) $(CXXFLAGS) -c Application.cpp

VertexArray.o : VertexArray.h VertexArray.cpp

VertexBuffer.o : VertexBuffer.h VertexBuffer.cpp

IndexBuffer.o : IndexBuffer.h IndexBuffer.cpp

