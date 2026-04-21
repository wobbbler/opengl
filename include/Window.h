#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
  Window(int width, int height, const char *title);

  ~Window();

  bool shouldClose() const;

  // Выводит то, что мы нарисовали, на экран (меняет задний буфер на передний)
  void swapBuffers() const;

  // Проверяет события: нажатия клавиш, движение мыши, изменение размера окна
  void pollEvents() const;

  GLFWwindow *getNativeWindow() { return window; }

private:
  // Указатель на само окно в памяти GLFW
  GLFWwindow *window;

  /* Cрабатывает, когда ты растягиваешь окно мышкой,
     чтобы картинка подстраивалась под новый размер */
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
};

#endif
