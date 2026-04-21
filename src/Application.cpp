#include "../include/Application.h"
#include "../include/geometry/MeshLibrary.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Здесь собираются все основные части приложения в одну рабочую сцену.
Application::Application()
    : deltaTime(0.0f), lastFrame(0.0f),
      window(Config::Window::width, Config::Window::height,
             Config::Window::title),
      camera((float)Config::Window::width, (float)Config::Window::height),
      shader(Config::Assets::vertexShaderPath,
             Config::Assets::fragmentShaderPath),
      cube(Geometry::cube(), Config::Assets::defaultTexturePath) {
  // Подключаем мышь к камере.
  camera.attachToWindow(window.getNativeWindow());
  // Включаем проверку глубины, чтобы 3D-объекты рисовались правильно.
  glEnable(GL_DEPTH_TEST);
}

int Application::run() {
  // Классический цикл приложения: обновление, рендер, показ кадра, обработка
  // событий.
  while (!window.shouldClose()) {
    update();
    render();
    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}

void Application::update() {
  // Считаем время между кадрами для плавного движения камеры.
  float currentFrame = (float)glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // Камера сама разбирает ввод и двигает себя.
  camera.processInput(window.getNativeWindow(), deltaTime);
}

void Application::render() {
  // Чистим экран и depth buffer перед новым кадром.
  glClearColor(Config::Render::clearColor.r, Config::Render::clearColor.g,
               Config::Render::clearColor.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Model-матрица задает наклон куба в мире.
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(Config::Render::modelTiltX),
                      glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(Config::Render::modelTiltY),
                      glm::vec3(0.0f, 1.0f, 0.0f));
  cube.setModelMatrix(model);

  // Шейдер получает матрицы камеры, после чего объект можно рисовать.
  shader.use();
  shader.setMat4("view", camera.getViewMatrix());
  shader.setMat4("projection",
                 camera.getProjectionMatrix((float)Config::Window::width /
                                            (float)Config::Window::height));

  // Сам объект отправляет model, текстуру и команду draw.
  cube.draw(shader);
}
