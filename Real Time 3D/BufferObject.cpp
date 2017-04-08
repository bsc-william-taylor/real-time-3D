
#include "BufferObject.h"

GL_Buffer::GL_Buffer() {
	glGenVertexArrays(1, &VBO);
	glBindVertexArray(VBO);

	glGenBuffers(1, &Vertices);
	glBindBuffer(GL_ARRAY_BUFFER, Vertices);
}

void GL_Buffer::Insert(void * Data, int var, int size, int vertices) {
	glBindVertexArray(VBO);

	glBindBuffer(GL_ARRAY_BUFFER, Vertices);
	glBufferData(GL_ARRAY_BUFFER, size, Data, GL_STATIC_DRAW);

	EnableVertexPointer(0);
	glVertexAttribPointer(0, vertices, var, GL_FALSE, 0, 0);
	DisableVertexPointer(0);
}

void GL_Buffer::BindVBO() {
	glBindVertexArray(VBO);
}

void GL_Buffer::EnableVertexPointer(GLuint Type) {
	glEnableVertexAttribArray(Type);
}

void GL_Buffer::DisableVertexPointer(GLuint Type) {
	glDisableVertexAttribArray(Type);
}

void GL_Buffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, Vertices);
}

GL_Buffer::~GL_Buffer() {
	
	glDeleteBuffers(1, &Vertices);
	
	glDeleteVertexArrays(1, &VBO);
}