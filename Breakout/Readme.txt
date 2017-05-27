g++ main.cpp -std=c++11 -lglfw -lGLEW -lGL -pthread -lSOIL -I./src/


g++ -std=c++11 main.cpp -c -llua5.3 -I ./LuaBridge/ -I ./src/ ./src/*.cpp


g++ -std=c++11 main.cpp -o Breakout -llua5.3 -I ./LuaBridge/ -I ./src/ luahelperfunctions.o graphicscomponent.o entity.o npccomponent.o Breakout


g++ -std=c++11 main.cpp -o Breakout -llua5.3 -I ./LuaBridge/ -I ./src/ ./src/luahelperfunctions.cpp ./src/graphicscomponent.cpp ./src/entity.cpp ./src/npccomponent.cpp 





g++ -std=c++11 main.cpp -o Breakout -pthread -llua5.3 -I ./include/LuaBridge/ -I ./src/ ./src/luahelperfunctions.cpp ./src/graphicscomponent.cpp ./src/entity.cpp ./src/npccomponent.cpp ./src/opengl.cpp -lglfw -lGLEW -lGL -lSOIL
