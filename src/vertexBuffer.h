#pragma once

class VertexBuffer
{
private: 
   unsigned int m_RendererID;
public:
   VertexBuffer(const void* data, unsigned int size);
   _VertexBuffer();

   void Bind();
   void Unbind();
};
