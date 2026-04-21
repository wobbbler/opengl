#ifndef APPLICATION_H
#define APPLICATION_H

#include "Camera.h"
#include "Config.h"
#include "Scene.h"
#include "Shader.h"
#include "Window.h"

// Главный управляющий класс проекта.
// Он собирает все основные подсистемы в одно приложение.
class Application {
public:
  // Подготавливает окно, камеру, шейдер и сцену.
  Application();

  // Запускает главный цикл приложения.
  int run();

private:
  // Нужны для плавного движения независимо от FPS.
  float deltaTime;
  float lastFrame;

  // Базовые подсистемы приложения.
  Window window;
  Camera camera;
  Shader shader;
  Scene cube;

  // Шейдеры
  Shader lampShader;
  Scene lightSource;

  // Обновление логики кадра.
  void update();
  // Отрисовка кадра.
  void render();
};

#endif
