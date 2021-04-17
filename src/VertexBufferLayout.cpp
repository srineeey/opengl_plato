//
// Created by sriney on 4/9/21.
//
#pragma once

//#include "VertexBufferLayout.h"


#include "Renderer.h"


template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
    //m_Stride += sizeof(GLfloat);
    //*count?
    m_Stride += count * VertexBufferElementLayout::GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({count, GL_UNSIGNED_INT, GL_FALSE});
    //m_Stride += sizeof(GLuint);
    m_Stride += count * VertexBufferElementLayout::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE});
    //m_Stride += sizeof(GLbyte);
    m_Stride += count * VertexBufferElementLayout::GetSizeOfType(GL_UNSIGNED_BYTE);
}