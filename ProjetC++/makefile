CC = g++
CXXFLAGS = -std=c++11 -Wall
EXEC_NAME = projet
#SRC= $(wildcard *.cpp)
SRC = src/Phase.cpp src/Game.cpp src/Player.cpp src/Human.cpp src/AI.cpp src/Unit.cpp src/Soldier.cpp src/Bowman.cpp src/Catapult.cpp  

CLASSES = $(SRC:.cpp=)
	SRC += src/main.cpp
OBJ_FILES = $(SRC:.cpp=.o)

all : $(EXEC_NAME)

clean :
		rm $(OBJ_FILES)

mrproper : clean
		rm $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
		$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o : %.cpp %.hpp
		$(CC) $(CXXFLAGS) -o $@ -c $<



