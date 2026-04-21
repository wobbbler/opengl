#include "../include/Window.h"

Window::Window(int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
  }

  // Настройка версии OpenGL (3.3 Core)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Создание окна с помощю GLFW
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  // Делаем контекст этого окна текущим
  glfwMakeContextCurrent(window);

  // Загрузка GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
  }

  // Настройка порта вывода (в каких пикселях окна рисовать)
  glViewport(0, 0, width, height);

  // Регистрируем колбэк на изменение размера окна
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window() { glfwTerminate(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }
void Window::swapBuffers() const { glfwSwapBuffers(window); }
void Window::pollEvents() const { glfwPollEvents(); }

void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  glViewport(0, 0, width, height);
}
