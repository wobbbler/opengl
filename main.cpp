#include "include/Mesh.h"
#include "include/Shader.h"
#include "include/Texture.h"
#include "include/Window.h"
#include <cmath>
#include <vector>

// Структура данных: Позиция (x,y,z), Цвет (r,g,b), Текстурные координаты (s,t)
std::vector<Vertex> vertices = {
    // Позиции            // Цвета             // Текстурные координаты
    {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},   // Верх-право
    {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},  // Низ-право
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // Низ-лево
    {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}   // Верх-лево
};

std::vector<unsigned int> indices = {
    0, 1, 3, // Первый треугольник
    1, 2, 3  // Второй треугольник
};

int main() {
  // Инициализация окна
  Window myWindow(1920, 1080, "OpenGL Engine");

  // Загрузка ресурсов (Шейдеры, Меш, Текстура)
  // Делаем это ОДИН РАЗ до начала цикла
  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");
  Mesh ourMesh(vertices, indices);
  Texture ourTexture("assets/brick.jpg");

  // Главный цикл
  while (!myWindow.shouldClose()) {
    // --- ЛОГИКА И ВВОД ---
    myWindow.pollEvents();

    // --- РЕНДЕРИНГ ---
    // Очистка экрана
    glClearColor(31.0f / 255.0f, 24.0f / 255.0f, 62.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Активация шейдера
    ourShader.use();

    // // Обновление Uniform-переменных (анимация яркости)
    // float timeValue = (float)glfwGetTime();
    // float brightnessValue = (sin(timeValue) / 2.0f) + 0.5f;
    // ourShader.setFloat("brightness", brightnessValue);

    // Сначала активируем текстуру
    ourTexture.use();

    // Теперь рисуем меш
    ourMesh.draw();

    // Смена буферов
    myWindow.swapBuffers();
  }

  return 0;
}
