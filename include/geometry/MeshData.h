#ifndef GEOMETRY_MESH_DATA_H
#define GEOMETRY_MESH_DATA_H

#include "../Mesh.h"
#include <vector>

namespace Geometry {

// Универсальный контейнер для геометрии:
// ссылки на вершины и индексы готовой формы.
struct MeshData {
  const std::vector<Vertex> &vertices;
  const std::vector<unsigned int> &indices;
};

} // namespace Geometry

#endif
