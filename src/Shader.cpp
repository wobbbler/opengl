#include "../include/Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  // Переменные под текст шейдеров
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure &e) {
    std::cerr << "ОШИБКА: Не удалось прочитать файлы шейдеров! Проверь пути."
              << std::endl;
  }

  // OpenGL не понимает std::string, ему нужны const char*
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // --- КОМПИЛЯЦИЯ ---
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // Вертексный шейдер
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cerr << "ОШИБКА КОМПИЛЯЦИИ ВЕРТЕКСНОГО ШЕЙДЕРА:\n"
              << infoLog << std::endl;
  }

  // Фрагментный шейдер
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cerr << "ОШИБКА КОМПИЛЯЦИИ ФРАГМЕНТНОГО ШЕЙДЕРА:\n"
              << infoLog << std::endl;
  }

  // --- ЛИНКОВКА ---
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cerr << "ОШИБКА ЛИНКОВКИ ПРОГРАММЫ:\n" << infoLog << std::endl;
  }

  // Удаляем шейдеры, они уже внутри (ID)
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
