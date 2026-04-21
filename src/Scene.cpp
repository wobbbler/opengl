#include "../include/Scene.h"

// Объект сцены получает геометрию и текстуру при создании.
Scene::Scene(const Geometry::MeshData &meshData, const std::string &texturePath)
    : mesh(meshData.vertices, meshData.indices), texture(texturePath),
      model(1.0f) {}

void Scene::setModelMatrix(const glm::mat4 &modelMatrix) {
  // Model-матрица хранит положение объекта в мировом пространстве.
  model = modelMatrix;
}

void Scene::draw(Shader &shader) {
  shader.setMat4("model", model);
  texture.use();
  mesh.draw();
}
