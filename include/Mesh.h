#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"
#include <vector>

// Структура одной точки (вершины)
struct Vertex {
  float x, y, z; // Координаты в пространстве
  float r, g, b; // Цвет
};

class Mesh {
public:
  /* Конструктор: принимает точки и порядок их соединения, сразу закидывает их в
     GPU. Благодаря плотной упаковке в памяти (3 float по 4 байта = 12 байт)*/
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

  // Деструктор: подчищает за собой память в видеокарте, когда объект удаляется
  ~Mesh();

  // Функция отрисовки: говорит видеокарте нарисовать наш объект прямо сейчас
  void draw();

private:
  // ID (числа-ссылки)
  unsigned int VAO; // Настройки: как читать данные
  unsigned int VBO; // Сами координаты точек
  unsigned int EBO; // Индексы - порядок соединения точек
  // VAO — Vertex Array Object
  // VBO — Vertex Buffer Object
  // EBO — Element Buffer Object

  int indicesCount;

  // Связываем данные с видеокартой
  void setupMesh(const std::vector<Vertex> &vertices,
                 const std::vector<unsigned int> &indices);
};

#endif
