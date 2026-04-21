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

    /* Создаем "единичную" матрицу.
           Единичка в скобках ставит 1.0 по диагонали, чтобы при умножении
           координаты объекта не превратились в ноль. */
    glm::mat4 trans = glm::mat4(1.0f);

    /**
     * GLM применяет трансформации в обратном порядке.
     * Чтобы объект сначала уменьшился, а потом закрутился, в коде
     * мы пишем сначала Rotate, а потом Scale. Читаем снизу вверх!
     */

    // Вычисляем угол: время работы программы * скорость вращения
    float angle = (float)glfwGetTime() * 50.0f;

    /* Поворот: берем текущую матрицу и "накручиваем" на нее вращение.
       glm::radians переводит понятные градусы в радианы (математика OpenGL).
       glm::vec3(0,0,1) говорит, что крутим вокруг оси Z (как пропеллер). */
    trans =
        glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    /* Масштаб: уменьшаем объект в два раза по всем осям (X, Y, Z).
       Так как эта команда последняя в коде, она выполнится самой ПЕРВОЙ. */
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    /* Ищем, где в скомпилированном шейдере "живет" переменная transform.
       Нам нужен ее адрес (Location), чтобы закинуть туда данные. */
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

    /**
     * Отправляем готовую матрицу в шейдер:
     * - transformLoc: адрес переменной в шейдере.
     * - 1: шлем ровно ОДНУ матрицу (не массив).
     * - GL_FALSE: не меняем строки и столбцы местами (GLM и так молодец).
     * - glm::value_ptr: вытаскиваем "сырые" числа из объекта матрицы,
     * потому что OpenGL не знает, что такое класс glm::mat4.
     */
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    // Теперь рисуем меш
    ourMesh.draw();

    // Смена буферов
    myWindow.swapBuffers();
  }

  return 0;
}
