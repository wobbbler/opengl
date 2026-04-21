#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);

  void use() { glUseProgram(ID); }
};

#endif
