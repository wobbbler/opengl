# Настройки компилятора
CXX = g++
CXXFLAGS = -I./include -std=c++17 -Wall
# Библиотеки: glfw, GL (графика), dl (для работы динамических библиотек в Linux)
LDFLAGS = -lglfw -lGL -ldl

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

CPP_SRCS = $(shell find $(SRC_DIR) -name '*.cpp') $(wildcard *.cpp)
C_SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS))
OBJS += $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SRCS))

TARGET = $(BUILD_DIR)/engine

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Сборка завершена: $(TARGET)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc -I./include -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
