CXX = g++
FLAGS = -O2 -Wall
INC = -I./inc
SRC = src/fileIO.cpp src/HRing.cpp src/main.cpp src/MCsim.cpp src/Vector3D.cpp
OBJ = obj/fileIO.o obj/HRing.o obj/main.o obj/MCsim.o obj/Vector3D.o

.PHONY: all clean

all: 
	if [ ! -d "./obj" ]; then mkdir obj; fi
	make simulation

simulation: $(OBJ) 
	$(CXX) $(FLAGS) $^ -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $(FLAGS) $(INC) $< -o $@

clean: 
	echo 'rm -r ./obj'
