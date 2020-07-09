#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H


#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
};

#endif
