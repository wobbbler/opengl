#include "include/Mesh.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/Window.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

// Структура данных: Позиция (x,y,z), Цвет (r,g,b), Текстурные координаты (s,t)
std::vector<Vertex> vertices = {
    // Позиции             // Цвета              // Текстурные координаты
    {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},   // Верх-право
    {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},  // Низ-право
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // Низ-лево
    {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}   // Верх-лево
};

std::vector<unsigned int> indices = {
    0, 1, 3, // Первый треугольник
    1, 2, 3  // Второй треугольник
};

// Положение камеры в пространстве
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Для плавности движения (независимо от FPS)
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
  float cameraSpeed =
      2.5f * deltaTime; // Скорость теперь привязана ко времени, а не к FPS
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

int main() {
  // Инициализация окна
  Window myWindow(1920, 1080, "OpenGL Engine");

  // Загрузка ресурсов (Шейдеры, Меш, Текстура)
  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");
  Mesh ourMesh(vertices, indices);
  Texture ourTexture("assets/brick.jpg");

  /* Без этого OpenGL не будет знать, какой треугольник находится ближе к тебе,
  а какой - дальше. В итоге задние стенки будут рисоваться поверх передних. */
  glEnable(GL_DEPTH_TEST);

  // Главный цикл
  while (!myWindow.shouldClose()) {
    // Считаем время кадра (чтобы на любом компе летали с одинаковой
    // скоростью)
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Ввод (передаем указатель на нативное окно GLFW для обработки нажатий)
    processInput(myWindow.getNativeWindow());

    // --- РЕНДЕРИНГ ---
    glClearColor(31.0f / 255.0f, 24.0f / 255.0f, 62.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ourShader.use();
    ourTexture.use();

    // --- МАТЕМАТИКА КАМЕРЫ (MVP) ---

    // Матрица модели
    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Матрица вида теперь создается через LookAt
    // Мы смотрим из cameraPos в сторону куда направлена камера (cameraPos +
    // cameraFront)
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // Матрица проекции: создаем перспективу
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

    // Отправка матриц в шейдер
    ourShader.setMat4("model", model);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    // Рисуем наш меш
    ourMesh.draw();

    // Смена буферов и опрос событий
    myWindow.swapBuffers();
    myWindow.pollEvents();
  }

  return 0;
}
