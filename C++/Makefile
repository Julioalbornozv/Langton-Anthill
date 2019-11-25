CXX= g++
CXXFLAGS= -Wall -Wfatal-errors $(INCLUDES)
INCLUDES= -I .\Dependencies\include
LDLIBS= -lglfw3 -lopengl32 -lgdi32 -lglu32
LDFLAGS= -L .\Dependencies\lib

dev:
	$(CXX) -o Lanthill lanthill.cpp Parameters.cpp Engine.cpp Color_Generator.cpp Tile_Generator.cpp Tile.cpp Colony.cpp Ant.cpp Camera.cpp Monitor.cpp -g $(CXXFLAGS) $(LDLIBS) $(LDFLAGS)

prod: 
	$(CXX) -o Lanthill lanthill.cpp Parameters.cpp Engine.cpp Color_Generator.cpp Tile_Generator.cpp Tile.cpp Colony.cpp Ant.cpp Camera.cpp Monitor.cpp -O2 $(CXXFLAGS) $(LDLIBS) $(LDFLAGS)

clean:
	rm -f *.o