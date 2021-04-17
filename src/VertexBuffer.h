//
// Created by sriney on 4/8/21.
//

#include <iostream>

class VertexBuffer
{
private:
    unsigned int m_RendererID = 0;
public:
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void BufferData(const void *data, unsigned int size);

    void Bind() const;
    void Unbind() const;
};