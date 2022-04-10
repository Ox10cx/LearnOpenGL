#include "Render.h"

void Render::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Render::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
