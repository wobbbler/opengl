#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
  // Результат — покомпонентное умножение цветов
  FragColor = vec4(lightColor * objectColor, 1.0);
}
