#include "Renderer.h"

#include <GLEW/glew.h>
#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	//shader.Bind();
	//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

	va.Bind();
	ib.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
