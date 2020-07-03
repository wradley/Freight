#pragma once
#include <glad/glad.h>
#include "Freight/pch.hpp"

GLuint CreateShader(const fr::Filepath &shaderFile, GLenum type);
GLuint CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &fPath);
GLuint CreateShaderProgram(const fr::Filepath &vPath, const fr::Filepath &gPath, const fr::Filepath &fPath);