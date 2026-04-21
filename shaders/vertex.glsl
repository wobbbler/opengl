#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal; // Нормали из атрибута 3

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Позиция фрагмента в мировом пространстве
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Передаем нормаль, исправленную матрицей нормалей
    // (transpose(inverse(model)) нужно для корректной работы при масштабировании)
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
