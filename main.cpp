#include "include/Mesh.h"
#include "include/Shader.h"
#include "include/Window.h"
#include <vector>

std::vector<Vertex> vertices = {
    // Позиция            // Цвет (RGB)
    {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f},   // 0: Верх-право (Красный)
    {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f},  // 1: Низ-право (Зеленый)
    {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f}, // 2: Низ-лево (Синий)
    {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f}   // 3: Верх-лево (Желтый)
};

std::vector<unsigned int> indices = {
    0, 1, 3, // Первый треугольник
    1, 2, 3  // Второй треугольник
};

int main() {
  // Создаем окно
  Window myWindow(1920, 1080, "Window");

  // Создаем шейдеры, указывая пути к файлам относительно main.cpp
  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");

  // Создаем меш
  Mesh ourMesh(vertices, indices);

  // Главный цикл
  // Проверяем, не нажат ли "крестик"
  while (!myWindow.shouldClose()) {

    // Логика и ввод
    myWindow.pollEvents(); // Проверяем нажатия клавиш, движение мыши и т.д.

    // Рендеринг
    // Устанавливаем цвет очистки (RGBA)
    /* OpenGL принимает значения только от 0.0 до 1.0. Поэтому делим наши
       значения на 255 для нормализац */
    glClearColor(31.0f / 255.0f, 24.0f / 255.0f, 62.0f / 255.0f, 1);

    // Очищаем буфер цвета текущим цветом
    glClear(GL_COLOR_BUFFER_BIT);
    ourShader.use(); // Включаем шейдеры
    ourMesh.draw();  // Рисуем меш

    // Смена буферов
    myWindow.swapBuffers();
  }

  // Когда цикл закончился, объект myWindow выйдет из области видимости
  // и вызовется деструктор ~Window(), который всё почистит.
  return 0;
}
