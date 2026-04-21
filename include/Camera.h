#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Камера хранит положение игрока и умеет строить view/projection матрицы.
// Также она обрабатывает клавиатуру и мышь.
class Camera {
public:
  Camera(float screenWidth, float screenHeight);

  // Подключает камеру к GLFW-окну и включает захват мыши.
  void attachToWindow(GLFWwindow *window);
  // Обрабатывает движение с клавиатуры каждый кадр.
  void processInput(GLFWwindow *window, float deltaTime);

  // Возвращает матрицу вида.
  glm::mat4 getViewMatrix() const;
  // Возвращает матрицу перспективной проекции.
  glm::mat4 getProjectionMatrix(float aspectRatio) const;

  glm::vec3 getPosition() const { return position; }

private:
  // GLFW callback статический, поэтому храним активную камеру отдельно.
  static Camera *activeCamera;

  // Базовые векторы камеры.
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;

  // Параметры обзора мышью.
  bool firstMouse;
  float yaw;
  float pitch;
  float lastX;
  float lastY;
  float fov;

  // Точка входа из GLFW в наш класс.
  static void mouseCallback(GLFWwindow *window, double xposIn, double yposIn);
  // Реальная обработка движения мыши.
  void handleMouseMove(double xposIn, double yposIn);
};

#endif
