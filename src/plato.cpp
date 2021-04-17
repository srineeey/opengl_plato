//
// Created by sriney on 4/16/21.
//

#include <cmath>
#include "plato.h"

plato::plato():
        m_NumVertices(0), m_NumIndices(0)
{
    m_NumVertices = 0;
    //TODO: make types dynamic and specify layout via arguments
    //position
    m_Layout.Push<float>(2);
    //normal
    m_Layout.Push<float>(4);
    //color
    m_Layout.Push<float>(4);

};

void plato::PushVertex(VertexDataElement vertex)
{
//    m_Data.push_back(vertex);
    m_Data[m_NumVertices] = vertex;
    m_NumVertices = m_NumVertices + 1;
}



void plato::PushIndices(unsigned int* new_indices, unsigned int count) {

    for (int i = 0; i < count; i++)
    {
//        m_Indices.push_back(new_indices[i]);
        m_Indices[m_NumIndices+i] = new_indices[i];
    }
    m_NumIndices = m_NumIndices + count;
}


VertexBufferLayout plato::GetVertexBufferLayout() {
    return m_Layout;
}

void *plato::GetDataPtr() {
    return &(m_Data[0]);
}

unsigned int* plato::GetIndicesPtr() {
    return &(m_Indices[0]);
}

int plato::GetDataSize() {
    return m_NumVertices*m_Layout.GetStride();
}

int plato::GetIndexCount() {
    return m_NumIndices;
}

void plato::VertexInit() {

    for (int i_vertex = 0; i_vertex < m_NumVertices; i_vertex++)
    {
        for (int i = 0; i < 4; i++)
        {
            m_Data[i_vertex].color[i] = 1.0f;
            m_Data[i_vertex].normal[i] = 0.0f;
        }

    }
}

void plato::PushColored2DTriangle(float *center, float length, float angle, float *color)
{

    float d = (1.0f / sqrt(12.0f)) * length;


    VertexDataElement corners[3];
    corners[0].position[0] = center[0];
    corners[0].position[1] = center[1] + (length - d);
//    corners[0].position[2] = 0.0f;
//    corners[0].position[3] = 1.0f;

    corners[1].position[0] = center[0] - 0.5f * length;
    corners[1].position[1] = center[1] - d;
//    corners[1].position[2] = 0.0f;
//    corners[1].position[3] = 1.0f;

    corners[2].position[0] = center[0] + 0.5f * length;
    corners[2].position[1] = center[1] - d;
//    corners[1].position[2] = 0.0f;
//    corners[1].position[3] = 1.0f;

    for (int i_vertex = 0; i_vertex < 3; i_vertex++)
    {
        for (int i_color = 0; i_color < 4; i_color++)
        {
            corners[i_vertex].color[i_color] = color[i_color];
        }

    }
    PushVertex(corners[0]);
    PushVertex(corners[1]);
    PushVertex(corners[2]);

}




