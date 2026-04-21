#include "../include/Camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

// GLFW колбэки не знают про объекты C++, поэтому активную камеру
// временно держим в статическом указателе.
Camera *Camera::activeCamera = nullptr;

Camera::Camera(float screenWidth, float screenHeight)
    : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f), firstMouse(true), yaw(-90.0f), pitch(0.0f),
      lastX(screenWidth / 2.0f), lastY(screenHeight / 2.0f), fov(45.0f) {}

void Camera::attachToWindow(GLFWwindow *window) {
  // Прячем курсор и фиксируем его внутри окна как в FPS-играх.
  activeCamera = this;
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, Camera::mouseCallback);
}

void Camera::processInput(GLFWwindow *window, float deltaTime) {
  // Скорость камеры зависит от deltaTime, а не от количества кадров в секунду.
  float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    position += cameraSpeed * front;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    position -= cameraSpeed * front;

  // Вправо считаем через векторное произведение направления взгляда и up.
  glm::vec3 right = glm::normalize(glm::cross(front, up));
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    position -= right * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    position += right * cameraSpeed;
  // Подъем и спуск идут по мировому вектору up.
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    position += up * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    position -= up * cameraSpeed;
}

glm::mat4 Camera::getViewMatrix() const {
  // Камера смотрит из position в точку position + front.
  return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
  // Perspective добавляет ощущение глубины: дальние объекты кажутся меньше.
  return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::mouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
  (void)window;

  // Перенаправляем событие в текущий объект камеры.
  if (activeCamera != nullptr)
    activeCamera->handleMouseMove(xposIn, yposIn);
}

void Camera::handleMouseMove(double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  // Превращаем движение мыши в изменение углов yaw/pitch.
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  // Понижаем чувствительность, чтобы камера не дергалась слишком резко.
  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // Ограничиваем вертикальный угол, чтобы камера не перевернулась.
  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  // Пересчитываем направление взгляда из углов в нормализованный вектор.
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(direction);
}
