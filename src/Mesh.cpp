#include "../include/Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
  this->indicesCount = indices.size();
  setupMesh(vertices, indices);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh(const std::vector<Vertex> &vertices,
                     const std::vector<unsigned int> &indices) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Привязываем VAO — теперь все настройки ниже запишутся в этот объект
  glBindVertexArray(VAO);

  // VBO: создаем склад для самих точек
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Копируем данные из нашего вектора (RAM) в память видеокарты (VRAM)
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  // EBO: создаем список порядка отрисовки
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // Копируем индексы в видеокарту
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  /* --- АТРИБУТЫ --- */
  // Атрибут 1 - позиция
  // Указываем OpenGL, как читать наши данные из структуры Vertex
  /*
     0 — это location в шейдере (layout (location = 0)).
     3 — количество значений (x, y, z).
     GL_FLOAT — тип данных.
     sizeof(Vertex) — шаг (сколько байт пропустить до следующей точки).
     (void*)0 — отступ от начала буфера.
  */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(
      0); // Включаем этот атрибут (по умолчанию они выключены)

  // Атрибут 2 - цвет (r, g, b)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Атрибут 3 - текстура
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Отвязываем VAO, чтобы случайно не изменить его
  glBindVertexArray(0);
}

// Функция рисования: вызываем в главном цикле
void Mesh::draw() {
  // Активируем настройки нашего объекта
  glBindVertexArray(VAO);
  // Рисуем треугольники, используя наши индексы (EBO)
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
  // Отключаем VAO после отрисовки
  glBindVertexArray(0);
}
