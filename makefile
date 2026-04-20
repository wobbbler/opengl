# Настройки компилятора
CXX = g++
CXXFLAGS = -I./include -std=c++23 -Wall
# Библиотеки: glfw, GL (графика), dl (для работы динамических библиотек в Linux)
LDFLAGS = -lglfw -lGL -ldl

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard *.cpp) $(SRC_DIR)/glad.c
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(filter %.cpp, $(SRCS))))
OBJS += $(OBJ_DIR)/glad.o

TARGET = $(BUILD_DIR)/engine

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Сборка завершена: $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/glad.o: $(SRC_DIR)/glad.c
	@mkdir -p $(OBJ_DIR)
	gcc -I./include -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
