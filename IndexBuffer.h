#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_RenderId;
    unsigned int m_Count;

public:
    inline unsigned int GetCount() const { return m_Count; }
};

#endif // INDEXBUFFER_H
