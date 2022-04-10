#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GLHead.h"
#include "Texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Render.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//struct ShaderProgramSource
//{
//    std::string VertexSource;
//    std::string FragmentSource;
//};


//ShaderProgramSource ParseShader(const std::string& filepath)
//{
//    std::ifstream stream(filepath);
//    enum class ShaderType {
//        NONE = -1, VERTEX = 0, FRAGMENT = 1
//    };

//    std::string line;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::NONE;
//    while (getline(stream, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if (line.find("vertex") != std::string::npos) {
//                type = ShaderType::VERTEX;
//            }
//            else if (line.find("fragment") != std::string::npos) {
//                type = ShaderType::FRAGMENT;
//            }
//        }
//        else {
//            ss[(int)type] << line << '\n';
//        }
//    }
//    return { ss[0].str(),ss[1].str() };
//}

//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//    GLCall(unsigned int id = glCreateShader(type));
//    const char* src = source.c_str();
//    GLCall(glShaderSource(id, 1, &src, nullptr));
//    GLCall(glCompileShader(id));

//    int result;
//    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
//    if (result == GL_FALSE)
//    {
//        int length;
//        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//        char* message = (char *)alloca(length * sizeof (char));
//        GLCall(glGetShaderInfoLog(id, length, &length, message));
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? " vertexShader" : "fragmentShader" )  << " shader !"<< std::endl;
//        std::cout << message << std::endl;
//        GLCall(glDeleteShader(id));
//        return 0;
//    }
//    return id;
//}

//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    GLCall(unsigned int program = glCreateProgram());
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

//    GLCall(glAttachShader(program, vs));
//    GLCall(glAttachShader(program, fs));
//    GLCall(glLinkProgram(program));
//    GLCall(glValidateProgram(program));

//    GLCall(glDeleteShader(vs));
//    GLCall(glDeleteShader(fs));
//    return program;

//}

int main(void)
{
    GLFWwindow* window;

       /* Initialize the library */
       if (!glfwInit())
           return -1;

       // 核心配置 没有默认的vao，需要我们显示配置
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
       // 在 Mac 上要加这一句配置，否则不显示
       glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
       glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

       /* Create a windowed mode window and its OpenGL context */
       window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
       if (!window)
       {
           glfwTerminate();
           return -1;
       }

       /* Make the window's context current */
       glfwMakeContextCurrent(window);

       if (glewInit() != GLEW_OK)
           std::cout<<"glewinit error" << std::endl;

        std::cout<< glGetString(GL_VERSION) << std::endl;


        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        float positions[] = {
            -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, 0.5f,   0.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };





//        unsigned int vao;
//        GLCall(glGenVertexArrays(1, &vao));
//        GLCall(glBindVertexArray(vao));


//        unsigned int vbo;
//        GLCall(glGenBuffers(1, &vbo));
//        GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
//        GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof (float), positions, GL_STATIC_DRAW));

//        GLCall(glEnableVertexAttribArray(0));
//        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, 0));

//        unsigned int ebo;
//        GLCall(glGenBuffers(1, &ebo));
//        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
//        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof (float), indices, GL_STATIC_DRAW));

//        ShaderProgramSource shaderSource = ParseShader("../OpenGL/res/shaders/Basic.shader");
//        unsigned int shaderProgram = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
//        GLCall(glUseProgram(shaderProgram));
//        GLCall(int location = glGetUniformLocation(shaderProgram, "u_Color"));
//        ASSERT(location != -1);
//        GLCall(glUniform4f(location, 0.2f, 0.4f, 0.8f, 1.0f));


//        GLCall(glUseProgram(0));
//        GLCall(glBindVertexArray(0));
//        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
//        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        VertexArray va;

        VertexBuffer vb(positions, 4 * 2 * 2 * sizeof (float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer eb(indices, 6);


        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, 0.0f, 0.0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0));


        glm::mat4 mvp =  model * view * proj;



        Shader shader("../OpenGL/res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.4f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_Mvp", mvp);

        Texture texture("../OpenGL/res/textures/ChernoLogo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);



        va.Unbind();
        vb.UnBind();
        eb.Unbind();
        shader.Unbind();

        Render render;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();

        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);

        glm::vec3 translationA(-0.1f, 0.0f, 0.0);
        glm::vec3 translationB(-0.5f, 0.0f, 0.0);

        float r = 0.0f;
        float increment = 0.05f;
       /* Loop until the user closes the window */
       while (!glfwWindowShouldClose(window))
       {
           /* Render here */
//           GLCall(glClear(GL_COLOR_BUFFER_BIT));

//           GLCall(glUseProgram(shaderProgram));
//           GLCall(glUniform4f(location, r, 0.4f, 0.8f, 1.0f));
//           //绑定vao就不需要绑定 重新绑定vbo了
//           GLCall(glBindVertexArray(vao));
//           GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

//           shader.Bind();
//           shader.SetUniform4f("u_Color", r, 0.4f, 0.8f, 1.0f);
//           va.Bind();
//           eb.Bind();



//           GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


//           if (r > 1.0f)
//               increment = -0.05f;
//           else if (r < 0.0f)
//               increment = 0.05f;
//           r += increment;

           render.Clear();

           ImGui_ImplOpenGL3_NewFrame();
           ImGui_ImplGlfw_NewFrame();
           ImGui::NewFrame();


           shader.Bind();
           shader.SetUniform4f("u_Color", 0.2f, 0.4f, 0.8f, 1.0f);

           {
               glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
               glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
               shader.SetUniformMat4f("u_Mvp", proj * model);
               render.Draw(va, eb, shader);
           }

           {
               model = glm::translate(glm::mat4(1.0f), translationB);
               shader.SetUniformMat4f("u_Mvp", proj * model);
               render.Draw(va, eb, shader);
           }


           {
               ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 1.0f);
               ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 1.0f);
               ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
           }


           ImGui::Render();
           ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

           /* Swap front and back buffers */
           glfwSwapBuffers(window);

           /* Poll for and process events */
           glfwPollEvents();
       }

       ImGui_ImplOpenGL3_Shutdown();
       ImGui_ImplGlfw_Shutdown();
       ImGui::DestroyContext();

       glfwTerminate();
       return 0;
}



