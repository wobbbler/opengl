#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "geometry/MeshData.h"
#include <glm/glm.hpp>
#include <string>

// Scene объединяет меш, текстуру и model-матрицу.
// Это уже готовая сущность сцены, которую можно просто нарисовать.
class Scene {
public:
  Scene(const Geometry::MeshData &meshData, const std::string &texturePath);

  // Меняет положение/поворот/масштаб объекта в мире.
  void setModelMatrix(const glm::mat4 &modelMatrix);
  void draw(Shader &shader);

private:
  Mesh mesh;
  Texture texture;
  glm::mat4 model;
};

#endif
