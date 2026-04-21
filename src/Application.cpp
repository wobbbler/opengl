#include "../include/Application.h"
#include "../include/geometry/MeshLibrary.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Application::Application()
    : deltaTime(0.0f), lastFrame(0.0f),
      window(Config::Window::width, Config::Window::height,
             Config::Window::title),
      camera((float)Config::Window::width, (float)Config::Window::height),
      shader(Config::Assets::vertexShaderPath,
             Config::Assets::fragmentShaderPath),

      // Твой основной куб
      cube(Geometry::cube(), Config::Assets::defaultTexturePath),

      // Инициализируем шейдер лампы
      lampShader("shaders/vertex.glsl", "shaders/lamp.frag"),

      // Инициализируем лампу (lightSource)
      lightSource(Geometry::cube(), "assets/lamp.jpg") {
  camera.attachToWindow(window.getNativeWindow());
  glEnable(GL_DEPTH_TEST);
}

int Application::run() {
  while (!window.shouldClose()) {
    update();
    render();
    window.swapBuffers();
    window.pollEvents();
  }
  return 0;
}

void Application::update() {
  float currentFrame = (float)glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  camera.processInput(window.getNativeWindow(), deltaTime);
}

void Application::render() {
  // Используем цвет фона из настроек
  glClearColor(Config::Render::clearColor.r, Config::Render::clearColor.g,
               Config::Render::clearColor.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float aspect = (float)Config::Window::width / (float)Config::Window::height;
  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 projection = camera.getProjectionMatrix(aspect);

  // --- 1. РИСУЕМ ОСНОВНОЙ КУБ ---
  shader.use();
  
  // Передаем Uniform-переменные для освещения
  shader.setVec3("objectColor", Config::Lighting::objectColor);
  shader.setVec3("lightColor", Config::Lighting::lightColor);
  shader.setVec3("lightPos", Config::Lighting::lightPos);
  shader.setVec3("viewPos", camera.getPosition());

  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  glm::mat4 model = glm::mat4(1.0f);
  // Можем добавить небольшое вращение для наглядности
  model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
  
  cube.setModelMatrix(model);
  cube.draw(shader);

  // --- 2. РИСУЕМ ЛАМПУ ---
  lampShader.use();
  lampShader.setMat4("view", view);
  lampShader.setMat4("projection", projection);

  // Матрица модели для лампы
  glm::mat4 lampModel = glm::mat4(1.0f);
  lampModel = glm::translate(lampModel, Config::Lighting::lightPos);
  lampModel = glm::scale(lampModel, glm::vec3(0.2f));

  lightSource.setModelMatrix(lampModel);
  lightSource.draw(lampShader);
}
