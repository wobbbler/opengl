#ifndef CONFIG_H
#define CONFIG_H

#include <glm/vec3.hpp>

// Все главные настройки проекта собраны здесь,
namespace Config {

namespace Window {
// Настройки окна.
constexpr int width = 1920;
constexpr int height = 1080;
constexpr const char *title = "OpenGL Engine";
} // namespace Window

namespace Assets {
// Пути к ресурсам проекта.
constexpr const char *vertexShaderPath = "shaders/vertex.glsl";
constexpr const char *fragmentShaderPath = "shaders/lighting.frag";
constexpr const char *defaultTexturePath = "assets/brick.jpg";
} // namespace Assets

namespace Render {
// Настройки внешнего вида кадра и начального наклона объекта.
constexpr glm::vec3 clearColor =
    glm::vec3(31.0f / 255.0f, 24.0f / 255.0f, 62.0f / 255.0f);

constexpr float modelTiltX = -28.0f;
constexpr float modelTiltY = 32.0f;
} // namespace Render

namespace Lighting {
const glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
const glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
const glm::vec3 objectColor(0.0f, 0.808f, 0.808f); // Бирюзовый (Turquoise)
} // namespace Lighting

} // namespace Config

#endif
