#include "../include/Window.h"

Window::Window(int width, int height, const char *title) {
  // 1. Инициализация GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
  }

  // Настройка версии OpenGL (3.3 Core)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 2. Создание окна
  m_window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!m_window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  // Делаем контекст этого окна текущим
  glfwMakeContextCurrent(m_window);

  // 3. Загрузка GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
  }

  // Настройка порта вывода (в каких пикселях окна рисовать)
  glViewport(0, 0, width, height);

  // Регистрируем колбэк на изменение размера окна
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

Window::~Window() { glfwTerminate(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }
void Window::swapBuffers() const { glfwSwapBuffers(m_window); }
void Window::pollEvents() const { glfwPollEvents(); }

void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  glViewport(0, 0, width, height);
}
