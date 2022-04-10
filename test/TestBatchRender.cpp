#include "TestBatchRender.h"

#include "GLHead.h"
#include "Render.h"
#include "imgui.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace test
{
    TestBatchRender::TestBatchRender()
        :m_Proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))),
        m_TranslationA(glm::vec3(0, 0, 0)), m_TranslationB(glm::vec3(0, 0, 0))
    {
        float positions[] = {
            100.0f, 100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            200.0f, 100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            200.0f, 200.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            100.0f, 200.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            300.0f, 100.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            400.0f, 100.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            400.0f, 200.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            300.0f, 200.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 10 * 8 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(4);
        layout.Push<float>(2);
        layout.Push<float>(1);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("../OpenGL/res/shaders/Batch.shader");
        m_Shader->Bind();

        m_Texture[0] = std::make_unique<Texture>("../OpenGL/res/textures/ChernoLogo.png");
        m_Texture[1] = std::make_unique<Texture>("../OpenGL/res/textures/HazelLogo.png");
        for (size_t i = 0; i < 2; i++)
        {
            m_Texture[i]->Bind(i);
        }
        int samplers[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);
    }

    TestBatchRender::~TestBatchRender()
    {
    }

    void TestBatchRender::OnUpdate(float deltaTime)
    {
    }

    void TestBatchRender::OnRender()
    {
        GLCall(glClearColor(0.3f, 0.6f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Render render;

        {
            glm::mat4 modelA = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 modelB = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvpA = m_Proj * m_View * modelA;
            glm::mat4 mvpB = m_Proj * m_View * modelB;

            glm::mat4 mvps[2] = { mvpA, mvpB};

            m_Shader->Bind();
            m_Shader->SetUniformMat4fv("u_MVP", 2, mvps);

            render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

    }

    void TestBatchRender::OnImGuiRender()
    {
        ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
