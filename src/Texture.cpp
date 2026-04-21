#include "../include/Texture.h"
#include "../include/stb_image.h"

Texture::Texture(const std::string &path) {
  // Генерируем уникальный ID для текстуры и сразу "выбираем" её (bind)
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  /* Настраиваем WRAP (повторение): если координаты текстуры больше 1.0,
     картинка будет дублироваться (плиткой) по осям S (X) и T (Y) */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* Настраиваем FILTER (сглаживание): при уменьшении используем мипмапы для
     плавности, а при увеличении — линейную интерполяцию, чтобы не было видно
     пикселей */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;

  /* В OpenGL координаты текстур идут снизу вверх: (0.0) — это низ, (1.0) — это
     верх. А обычные картинки (JPG/PNG) хранятся наоборот: у них (0.0) — это
     самый верх. Без этого "флипа" картинка натянется на квадрат вверх ногами */
  stbi_set_flip_vertically_on_load(true);
  stbi_set_flip_vertically_on_load(true);

  // Пытаемся прочитать файл и вытащить из него байты
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

  if (data) {
    // Вычисляем является ли это RGB или RGBA
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    /* Скармливаем видеокарте сырые байты картинки. С этого момента GPU
           уже держит текстуру в своей памяти, а не в нашей оперативке.
           Сразу генерим мипмапы — это копии картинки в стиле "чем дальше
       объект, тем меньше разрешение", чтобы текстура не рябила и не жрала
       ресурсы, когда квадрат улетит вдаль. */
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
  }

  /* Данные уже в видеокарте, так что мусор из оперативной памяти (CPU) можно
     удалять */
  stbi_image_free(data);
}

void Texture::use(unsigned int unit) {
  /* В видеокарте много "слотов" под текстуры. Выбираем нужный (обычно 0-й),
     и привязываем наш ID, чтобы шейдер знал, какую картинку юзать прямо сейчас
   */
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, ID);
}
