#include "../include/glad.h"
#include "../include/glfw3.h"

#include <iostream>
#include <math.h>
#include <stdio.h>

#define ASSERT(x) if (!(x)) __builtin_trap();

#define GLCall(x) GLClearError();\
   x;\
   ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout<< "[OpenGL_Error] (" <<error << "): "<<function<<" " <<file<<":"<<line <<std::endl;
        return false;
    }
    return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor=aColor;\n"
    "}\0";

const char *FragmentShaderSource= "#version 330 core\n"//vec4(1.0f, 1.0f, 1.0f, 1.0f); was white, now is color gradient
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OGLTriangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    //Vertex Shader:

unsigned int vertexShader=glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
    //logging
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
    else {
        std::cout<< "Vertex Shader Success.\n"<<std::endl; }

    //Fragment Shader
    
unsigned int FragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
glCompileShader(FragmentShader);

int  fragSuccess;
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &fragSuccess);
    
    if(!fragSuccess)
{
    glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
}
    else {
        std::cout<< "Fragment Shader Success.\n"<<std::endl; }



    //Shader Program 
    //
    unsigned int ShaderProgram=glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
{
    glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
}
    else {
        std::cout<< "Shader Program Success.\n"<<std::endl; }
    glUseProgram(ShaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);

    
float leftVerticies[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,//bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//top left
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f//center
    };

unsigned int indicies[] = {
    0,1,2
};

    unsigned int LeftVAO, LeftVBO, TriEBO;
glGenVertexArrays(1, &LeftVAO);

glGenBuffers(1, &LeftVBO);

glGenBuffers(1, &TriEBO);

glBindVertexArray(LeftVAO);

glBindBuffer(GL_ARRAY_BUFFER, LeftVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(leftVerticies), leftVerticies, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TriEBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

// position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// color attribute
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);

glBindBuffer(GL_ARRAY_BUFFER, 0);

glBindVertexArray(0);


       
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        glClearColor(0.2f, 0.7f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        int vertexColorLocation = glGetUniformLocation(ShaderProgram, "ourColor");

        glUseProgram(ShaderProgram);
        glUniform4f(vertexColorLocation, 1.0f, 0.5f, 0.0f, 1.0f); 
        glBindVertexArray(LeftVAO);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        // render
        // ------
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

//Deallocate
    glDeleteVertexArrays(1, &LeftVAO);
    glDeleteBuffers(1, &LeftVBO);

    glDeleteProgram(ShaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
