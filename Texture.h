#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>

class Texture
{
private:
    unsigned int m_RenderId;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_Bpp;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const {return m_Width;}
    inline int GetHeight() const {return m_Height;}


};

#endif // TEXTURE_H
