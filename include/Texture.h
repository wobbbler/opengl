#ifndef TEXTURE_H
#define TEXTURE_H

#include "../include/glad/glad.h"
#include <iostream>
#include <string>

class Texture {
public:
  unsigned int ID;
  Texture(const std::string &path);
  void use(unsigned int unit = 0);
};

#endif
