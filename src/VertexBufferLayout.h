//
// Created by sriney on 4/9/21.
//
#pragma once

#include <iostream>

#include <vector>
#include <GL/glew.h>

#include "GLErrorManager.h"




struct VertexBufferElementLayout
{
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;

    }
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElementLayout> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
    : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count);


    const std::vector<VertexBufferElementLayout> GetElements() const
    {
        return m_Elements;
    }

    inline unsigned int GetStride() const {return m_Stride;}

};

