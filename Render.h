#ifndef RENDER_H
#define RENDER_H


#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Render
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
#endif // RENDER_H
