#ifndef TESTBATCHDYNAMICRENDER_H
#define TESTBATCHDYNAMICRENDER_H


#include "Test.h"
#include "Shader.h"
#include "Texture.h"

#include <array>
#include <iostream>
#include <string>
#include <map>
#include <memory>


struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

struct Vec4
{
    float x, y, z, w;
};

struct Vertex
{
    Vec3 Position;
    Vec4 Color;
    Vec2 TexCoords;
    float TexID;
};

namespace test
{



    class TestBatchDynamicRender : public Test
    {
    private:
         unsigned int m_QuadVA;
         unsigned int m_QuadVB;
         unsigned int m_QuadEB;
         std::unique_ptr<Shader> m_Shader;
         std::unique_ptr<Texture> m_Texture[2];
         float m_Scale;

         glm::mat4 m_Proj, m_View, m_Model;
         glm::vec3 m_TranslationA, m_TranslationB;

    private:
        Vertex* CreateQuad(Vertex* vertex, float x, float y, float textureID);
        std::array<Vertex, 4> CreateQuad(float x, float y, float textureID);



    public:
        TestBatchDynamicRender();
        ~TestBatchDynamicRender();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}


#endif // TESTBATCHDYNAMICRENDER_H
