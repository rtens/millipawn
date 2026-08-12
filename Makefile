CXX = g++
CXXFLAGS = -g
SRCS = $(wildcard lib/src/*.cpp)
INCLUDES = $(wildcard lib/include/*.h)
OBJS = $(SRCS:.cpp=.o)

# %: main/%.o $(OBJS)
# 		$(CXX) $(CXXFLAGS) $< $(OBJS) -o bin/$@

perft: main/perft.o $(OBJS)
		$(CXX) $(CXXFLAGS) main/perft.o $(OBJS) -o bin/perft

test: main/test.o $(OBJS)
		$(CXX) $(CXXFLAGS) main/test.o $(OBJS) -o bin/test

%.o: %.cpp $(INCLUDES)
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) main/*.o bin/*

run: $(app)
		bin/$(app)
