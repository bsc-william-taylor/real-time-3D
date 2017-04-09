
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "GL_Header.h"

enum BufferType {
	VERTEX,
	TEXTURE,
	NORMAL,
	COLOUR
};

struct BufferData {
	GLuint Size;
	GLuint ID;
};

class GL_Buffer {
private:

		GLuint VertexArray;
		GLuint Vertices;
		GLuint VBO;

	public:

	GL_Buffer();

		void Insert(void * data, int type, int size, int vertices);
		
		void DisableVertexPointer(GLuint);
		void EnableVertexPointer(GLuint);

		void ReleaseVBO();
		void BindVBO();
		void Bind();

	~GL_Buffer();
};

#endif