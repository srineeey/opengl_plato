//
// Created by sriney on 4/8/21.
//

#include "Renderer.h"
#include <iostream>
#include "GL/glew.h"


void GLClearError()
{
while(glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char* function, const char* file, int line)
{
while(GLenum error = glGetError())
{
std::cout << "OpenGL Error: (" << std::to_string(error) << "):  " << function <<
", file " << file << ":" << std::to_string(line) << std::endl;
return false;
}
return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
