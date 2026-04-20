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
  void swapBuffers() const;
  void pollEvents() const;

private:
  GLFWwindow *m_window;
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
};

#endif
