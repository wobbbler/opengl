#include "../../include/geometry/MeshLibrary.h"
#include "../../include/geometry/CubeData.h"

namespace Geometry {

const MeshData &cube() {
  // static гарантирует, что структура создастся один раз
  // и потом будет переиспользоваться при каждом обращении.
  static const MeshData mesh{CubeData::vertices, CubeData::indices};
  return mesh;
}

} // namespace Geometry
