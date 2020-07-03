#include "GLShader.hpp"
#include "../FileSystem/FileLoader.hpp"

GLuint CreateShader(const fr::Filepath &shaderFile, GLenum type)
{
    int success;
    char infoLog[512];
    fr::String shaderStr;
    fr::LoadFileAsString(shaderFile, shaderStr);
    const char *shaderCStr = shaderStr.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCStr, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        FR_WARN("Shader compilation error [" << shaderFile << "]: " << infoLog);
    };

    return shader;
}


GLuint CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &fPath)
{
    int success;
    char infoLog[512];

    GLuint vertex = CreateShader(vPath, GL_VERTEX_SHADER);
    GLuint fragment = CreateShader(fPath, GL_FRAGMENT_SHADER);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 512, NULL, infoLog);
        FR_WARN("GL Shader Link Error: " << infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return prog;
}


GLuint CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &gPath, const fr::Filepath &fPath)
{
    int success;
    char infoLog[512];

    GLuint vertex = CreateShader(vPath, GL_VERTEX_SHADER);
    GLuint geometry = CreateShader(gPath, GL_GEOMETRY_SHADER);
    GLuint fragment = CreateShader(fPath, GL_FRAGMENT_SHADER);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, geometry);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 512, NULL, infoLog);
        FR_WARN("GL Shader Link Error: " << infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);

    return prog;
}