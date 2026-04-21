#version 330 core // Используем OpenGL 3.3, core - современный режим

// Итоговый цвет пикселя (RGBA)
out vec4 FragColor;
in vec3 ourColor; // Получаем цвет из вершинного шейдера

uniform sampler2D ourTexture; // "Ссылка" на нашу текстуру
in vec2 TexCoord; // Данные из вертексного шейдера

void main() {

  // Назначаем цвет каждому пикселю, который попал внутрь нашего объекта.
  // vec4 — это 4 значения: Красный, Зеленый, Синий и Альфа (прозрачность).
  // 1.0f в конце — полная непрозрачность.
  FragColor = texture(ourTexture, TexCoord);
}
