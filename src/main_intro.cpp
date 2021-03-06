//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if  (!(x)) std::cout << "break";
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}


static bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "OpenGL Error: (" << std::to_string(error) << "):  " << function <<
        ", file " << file << ":" << std::to_string(line) << std::endl;
        return false;
    }
    return true;
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    std::cout  << std::endl << filepath << std::endl;
    std::cout  << "stream fails: " << stream.fail() << std::endl;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    unsigned int i = 0;
    while(getline(stream, line))
    {
        i++;
        std::cout << std::to_string(i) << line << std::endl;
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        } else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};

}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char) );
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }

    //TODO: Error handling

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew not ok\n";
    else
        std::cout << "glew ok\n";

    std::cout << glGetString(GL_VERSION);


    /*
     * Define Buffer here
     */

    float positions[] =
            {
            -0.5f,-0.5f,
            0.5f,-0.5f,
            0.5f,0.5f,
            -0.5f,0.5f,
            };

    unsigned int indices[] =
                         {
            0,1,2,
            2,3,0
                         };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*2*sizeof(unsigned int), indices, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0));

    const std::string shadersourcefilepath = "src/res/shaders/Basic.shader";
    ShaderProgramSource source = ParseShader(shadersourcefilepath);
    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    int color_location = glGetUniformLocation(shader, "u_Color");
    ASSERT(color_location != -1);

    float color[4] =
            {
                    0.5f, 0.0f, 0.0f, 1.0f
            };

    float color_delta = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */


        if (color[0] < 0.0f)
        {
            color_delta = 0.05f;
        } else if (color[0] > 1.0f)
        {
            color_delta = -0.05f;
        }

        color[0] += color_delta;

        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(color_location, color[0], color[1], color[2], color[3]));

        GLCall(glBindVertexArray(vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}