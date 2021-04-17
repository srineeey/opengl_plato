//
// Created by sriney on 4/9/21.
//
#pragma once

#include <iostream>

#include "VertexBufferLayout.h"

#include "VertexBuffer.h"


class VertexArray
{
private:
    unsigned int m_RendererID = 0;
public:
    VertexArray();

    ~VertexArray();


    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;

    void Unbind() const;

};