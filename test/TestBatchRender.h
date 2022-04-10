#ifndef TESTBATCHRENDER_H
#define TESTBATCHRENDER_H

#include "Test.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"


#include <memory>

namespace test
{

    class TestBatchRender : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture[2];

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_TranslationA, m_TranslationB;

    public:
        TestBatchRender();
        ~TestBatchRender();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}

#endif // TESTBATCHRENDER_H
