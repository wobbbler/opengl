#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);

  void use() { glUseProgram(ID); }

  /* В документации советуют добавить вспомогательные функции, чтобы не писать
     каждый раз длинные glGetUniformLocation */
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  // чтобы забыть про glGetUniformLocation в основном коде
  void setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
  }
  void setVec3(const std::string &name, float r, float g, float b) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
};

#endif
