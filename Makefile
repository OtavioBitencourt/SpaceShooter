# =========================================
# COMPILER
# =========================================

CXX = g++

# =========================================
# PROJECT
# =========================================

TARGET = game
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# =========================================
# SFML
# =========================================

SFML_INCLUDE = SFML/include
SFML_LIB = SFML/lib

# =========================================
# FLAGS
# =========================================

CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -I$(INCLUDE_DIR) -I$(SFML_INCLUDE)

LDFLAGS = -L$(SFML_LIB)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# =========================================
# SOURCE FILES
# =========================================

SRC = \
src/main.cpp \
src/Core/Game.cpp \
src/Entities/Entity.cpp \
src/Entities/Player.cpp \
src/Entities/Bullet.cpp \
src/Entities/Asteroid.cpp \
src/Entities/Enemy.cpp \
src/Core/EntityManager.cpp


# =========================================
# BUILD
# =========================================

all:
	$(CXX) $(SRC) -o $(BUILD_DIR)/$(TARGET) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS)

# =========================================
# CLEAN
# =========================================

clean:
	del /Q $(BUILD_DIR)\$(TARGET).exe

# =========================================
# RUN
# =========================================

run:
	$(BUILD_DIR)/$(TARGET).exe