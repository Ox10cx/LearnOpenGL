#include "TestBatchDynamicRender.h"
#include "GLHead.h"
#include "imgui.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"



namespace test
{


    TestBatchDynamicRender::TestBatchDynamicRender()
        :m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0))),
        m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0))),
        m_TranslationA(glm::vec3(-0.1f, 0.0f, 0.0)), m_TranslationB(glm::vec3(0.0f,0.1f, 0.0)),
        m_Scale(glm::vec3(1.0f, 1.0f, 1.0f))
    {

      const size_t MaxQuadCount = 1000;
      const size_t MaxVertexCount = 4 * MaxQuadCount;
      const size_t MaxIndexCount = 6 * MaxQuadCount;

       GLCall(glGenVertexArrays(1, &m_QuadVA));
       GLCall(glBindVertexArray(m_QuadVA));

       GLCall(glGenBuffers(1, &m_QuadVB));
       GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
       // 动态几何 改变一 nullptr  GL_DYNAMIC_DRAW 动态改变顶点数组
       GLCall(glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));

       GLCall(glEnableVertexAttribArray(0));
       GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (const void *)offsetof(Vertex, Position)));

       GLCall(glEnableVertexAttribArray(1));
       GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (const void *)offsetof(Vertex, Color)));

       GLCall(glEnableVertexAttribArray(2));
       GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (const void *) offsetof(Vertex, TexCoords)));

       GLCall(glEnableVertexAttribArray(3));
       GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof (Vertex), (const void *) offsetof(Vertex, TexID)));


//        unsigned int indices[] = {
//            0, 1, 2, 2, 3, 0,
//            4, 5, 6, 6, 7, 4
//        };
       uint32_t indices[MaxIndexCount];
       uint32_t offset = 0;
       for (size_t i = 0; i < MaxIndexCount; i += 6)
       {
           indices[i + 0] = 0 + offset;
           indices[i + 1] = 1 + offset;
           indices[i + 2] = 2 + offset;

           indices[i + 3] = 2 + offset;
           indices[i + 4] = 3 + offset;
           indices[i + 5] = 0 + offset;

           offset += 4;

       }


        GLCall(glGenBuffers(1, &m_QuadEB));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadEB));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));


        m_Shader = std::make_unique<Shader>("../OpenGL/res/shaders/BatchDynamic.shader");
        m_Shader->Bind();

        m_Texture[0] = std::make_unique<Texture>("../OpenGL/res/textures/ChernoLogo.png");
        m_Texture[1] = std::make_unique<Texture>("../OpenGL/res/textures/HazelLogo.png");
        for (size_t i = 0; i < 2; i++)
        {
            m_Texture[i]->Bind(i);
        }
        int samplers[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);


        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    }

    TestBatchDynamicRender::~TestBatchDynamicRender()
    {
          GLCall(glDeleteVertexArrays(1, &m_QuadVA));
          GLCall(glDeleteBuffers(1, &m_QuadVB));
          GLCall(glDeleteBuffers(1, &m_QuadEB));

    }
     Vertex* TestBatchDynamicRender::CreateQuad(Vertex* vertex, float x, float y, float textureID)
     {
         float size = 1.0f;

         vertex->Position = {x, y, 0.0f};
         vertex->Color = {0.18f, 0.6f, 0.96f, 1.0f};
         vertex->TexCoords= {0.0f, 0.0f};
         vertex->TexID = textureID;
         vertex++;


         vertex->Position = {x + size, y, 0.0f};
         vertex->Color = {0.18f, 0.6f, 0.96f, 1.0f};
         vertex->TexCoords= {1.0f, 0.0f};
         vertex->TexID = textureID;
         vertex++;


         vertex->Position = {x + size, y + size, 0.0f};
         vertex->Color = {0.18f, 0.6f, 0.96f, 1.0f};
         vertex->TexCoords= {1.0f, 1.0f};
         vertex->TexID = textureID;
         vertex++;

         vertex->Position = {x, y + size, 0.0f};
         vertex->Color = {0.18f, 0.6f, 0.96f, 1.0f};
         vertex->TexCoords= {0.0f, 1.0f};
         vertex->TexID = textureID;
         vertex++;

         return vertex;

     }

     std::array<Vertex, 4> TestBatchDynamicRender::CreateQuad(float x, float y, float textureID)
     {
         float size = 1.0f;

         Vertex v0;
         v0.Position = {x, y, 0.0f};
         v0.Color = {0.18f, 0.6f, 0.96f, 1.0f};
         v0.TexCoords= {0.0f, 0.0f};
         v0.TexID = textureID;


         Vertex v1;
         v1.Position = {x + size, y, 0.0f};
         v1.Color = {0.18f, 0.6f, 0.96f, 1.0f};
         v1.TexCoords= {1.0f, 0.0f};
         v1.TexID = textureID;


         Vertex v2;
         v2.Position = {x + size, y + size, 0.0f};
         v2.Color = {0.18f, 0.6f, 0.96f, 1.0f};
         v2.TexCoords= {1.0f, 1.0f};
         v2.TexID = textureID;

         Vertex v3;
         v3.Position = {x, y + size, 0.0f};
         v3.Color = {0.18f, 0.6f, 0.96f, 1.0f};
         v3.TexCoords= {0.0f, 1.0f};
         v3.TexID = textureID;

         return {v0, v1, v2, v3};

     }

    void TestBatchDynamicRender::OnUpdate(float deltaTime)
    {

        GLCall(glClearColor(0.3f, 0.6f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

//        float vertices[] = {
//            -1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
//            -0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
//            -0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,
//            -1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,

//             0.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f,
//             1.5f, -0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f,
//             1.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f, 1.0f, 1.0f,
//             0.5f,  0.5f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 0.0f, 1.0f, 1.0f,

//        };

//        auto q0 = CreateQuad(m_TranslationA[0], m_TranslationA[1], 0.0f);
//        auto q1 = CreateQuad(0.5f,  -0.5f, 1.0f);

//        Vertex vertices[8];
//        memcpy(vertices, q0.data(), q0.size() * sizeof (Vertex));
//        memcpy(vertices + q0.size() , q1.data(), q1.size() * sizeof (Vertex));


//        glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);


        unsigned int indexCount = 0;

        std::array<Vertex, 1000> vertices;
        Vertex* buffer = vertices.data();
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                buffer = CreateQuad(buffer, x, y, (x + y) % 2);
                indexCount += 6;
            }
        }

        buffer = CreateQuad(buffer, m_TranslationA[0], m_TranslationA[1], 0.0f);
        indexCount += 6;

        // Set dynamic vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof (Vertex), vertices.data());



        glm::mat4 modelA = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 modelB = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), m_Scale);
        glm::mat4 mvpA = m_Proj * m_View * modelA * modelScale;
        glm::mat4 mvpB = m_Proj * m_View * modelB * modelScale;

        glm::mat4 mvps[2] = { mvpA, mvpB};

        m_Shader->Bind();
        m_Shader->SetUniformMat4fv("u_MVP", 2, mvps);


        GLCall(glBindVertexArray(m_QuadVA));
        GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
    }

    void TestBatchDynamicRender::OnRender()
    {

    }
    void TestBatchDynamicRender::OnImGuiRender()
    {
        ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("m_Scale", &m_Scale.x, 0.0f, 1.0f);
    }

}
