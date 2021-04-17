//
// Created by sriney on 4/16/21.
//

#include <vector>

#include "VertexBufferLayout.h"
#include "VertexArray.h"

struct VertexDataElement
{
    //TODO: dynamically change the types?
    float position[2];
    float normal[4];
    float color[4];
};


class plato
{
private:
    VertexBufferLayout m_Layout;

public:
    //TODO: will Vertexarrays be able to access that? dont think so, as it is private
    //TODO: Dynamic array size
    int m_NumIndices;
    unsigned int m_Indices[3];
//    std::vector<VertexDataElement> m_Data;
    int m_NumVertices;
    //TODO: Dynamic array size
    VertexDataElement m_Data[3];

    plato();

    void PushVertex(VertexDataElement vertex);

    void PushIndices(unsigned int *new_indices, unsigned int count);

    void VertexInit();

    VertexBufferLayout GetVertexBufferLayout();
    void* GetDataPtr();
    unsigned int* GetIndicesPtr();
    int GetDataSize();
    int GetIndexCount();

    void PushColored2DTriangle(float *center, float length, float angle, float *color);


};
