//
// Created by sriney on 4/8/21.
//
#pragma once

#include "GLErrorManager.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:

};

