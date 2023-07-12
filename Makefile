CXX = g++
CXXFLAGS = -w
LIBS = -lc

%.o: %.cpp
	$(CXX) -c $^  -o $@ $(CXXFLAGS)

bikez2: bikez2.o func.o pseudirectx.o
	$(CXX) $^ -o $@ $(LIBS) $(LDFLAGS)
