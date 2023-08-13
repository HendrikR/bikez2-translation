LIBS=sdl2 glm gl glew SDL2_mixer
CXX = g++
CXXFLAGS = -g `pkg-config --cflags ${LIBS}`
LDFLAGS = -g -lc `pkg-config --libs ${LIBS}`

%.o: %.cpp
	$(CXX) -c $^  -o $@ $(CXXFLAGS)

bikez2: bikez2.o func.o pseudirectx.o
	$(CXX) $^ -o $@ $(LDFLAGS)
