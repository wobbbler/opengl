#version 330 core // Версия OpenGL (3.3 Core)

// Входные данные: берем позицию точки из 0-го атрибута (тот самый location = 0 из Mesh.cpp)
// vec3 — это X, Y и Z координаты, которые мы передали в VBO
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; // Берем цвет из атрибута 1
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor; // Передаем цвет в фрагментный шейдер
out vec2 TexCoord;

void main() {
  // gl_Position — это встроенная переменная OpenGL.
  // Мы должны записать в неё итоговую позицию точки.

  // Мы превращаем vec3 (3 числа) в vec4 (4 числа), добавляя 1.0 в конце.
  // Четвертое число (W) нужно видеокарте для сложной математики и перспективы.
  gl_Position = vec4(aPos, 1.0);
  ourColor = aColor; // Пробрасываем цвет
  TexCoord = aTexCoord;
}
