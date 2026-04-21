#ifndef GEOMETRY_MESH_LIBRARY_H
#define GEOMETRY_MESH_LIBRARY_H

#include "MeshData.h"

namespace Geometry {

// Возвращает готовый набор данных для куба.
// Позже сюда можно добавить plane(), pyramid() и другие формы.
const MeshData &cube();

} // namespace Geometry

#endif
