LIBS=sdl2 glm gl
CXX = g++
CXXFLAGS = -g `pkg-config --cflags ${LIBS}`
LDFLAGS = -lc `pkg-config --libs ${LIBS}`

%.o: %.cpp
	$(CXX) -c $^  -o $@ $(CXXFLAGS)

bikez2: bikez2.o func.o pseudirectx.o
	$(CXX) $^ -o $@ $(LDFLAGS)
