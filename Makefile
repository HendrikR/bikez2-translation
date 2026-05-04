LIBS=sdl2 gl glew SDL2_mixer
CXX = g++
CXXFLAGS = -g `pkg-config --cflags ${LIBS}`
LDFLAGS = -g -lc `pkg-config --libs ${LIBS}` -lglm

%.o: %.cpp
	$(CXX) -c $^  -o $@ $(CXXFLAGS)

bikez2: bikez2.o func.o pseudirectx.o json11.o
	$(CXX) $^ -o $@ $(LDFLAGS)
