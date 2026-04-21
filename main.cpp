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

int main() {
  // Инициализация окна
  Window myWindow(1920, 1080, "OpenGL Engine");

  // Загрузка ресурсов (Шейдеры, Меш, Текстура)
  // Делаем это ОДИН РАЗ до начала цикла
  Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");
  Mesh ourMesh(vertices, indices);
  Texture ourTexture("assets/brick.jpg");

  /* Без этого OpenGL не будет знать, какой треугольник находится ближе к тебе,
  а какой - дальше. В итоге задние стенки будут рисоваться поверх передних. */
  glEnable(GL_DEPTH_TEST);

  // Главный цикл
  while (!myWindow.shouldClose()) {
    // --- ЛОГИКА И ВВОД ---
    myWindow.pollEvents();

    // --- РЕНДЕРИНГ ---
    // Очистка экрана
    glClearColor(31.0f / 255.0f, 24.0f / 255.0f, 62.0f / 255.0f, 1.0f);

    /* GL_COLOR_BUFFER_BIT - Это очистка самого изображения. Чтобы каждый новый
     * кадр рисовался поверх старого.
     * GL_DEPTH_BUFFER_BIT - чтобы "сбрасывать" расстояния прошлого кадра */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Активация шейдера
    ourShader.use();

    // --- МАТЕМАТИКА МАТРИЦ (MVP) ---

    // Матрица модели: крутим объект, чтобы он лежал под углом
    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // Добавляем вращение для динамики (как было в твоем трансформе)
    model =
        glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Матрица вида: двигаем весь мир "назад" (по Z на -3.0), как будто мы
    // отошли камерой
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Матрица проекции: создаем пирамиду видимости (перспективу)
    // Используем 1920/1080 для правильных пропорций
    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

    // Каждая матрица отвечает за свой этап преобразования координат (MVP)
    /* Model: Позиционирование объекта в мировом пространстве (смещение,
     * вращение, масштаб) */
    ourShader.setMat4("model", model);

    /* View: Позиционирование камеры (перемещение всего мира относительно
     * наблюдателя) */
    ourShader.setMat4("view", view);

    /* Projection: Создание перспективы (эффект уменьшения объектов при
     * удалении) */
    ourShader.setMat4("projection", projection);

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
