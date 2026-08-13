CXX = g++
CXXFLAGS = -g
SRCS = $(wildcard lib/src/*.cpp)
TESTS = $(wildcard test/*.cpp)
INCLUDES = $(wildcard lib/include/*.h)
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TESTS:.cpp=.o)

# %: main/%.o $(OBJS)
# 		$(CXX) $(CXXFLAGS) $< $(OBJS) -o bin/$@

perft: main/perft.o $(OBJS)
		$(CXX) $(CXXFLAGS) main/perft.o $(OBJS) -o bin/perft

test: main/test.o $(OBJS) $(TEST_OBJS)
		$(CXX) $(CXXFLAGS) main/test.o $(OBJS) $(TEST_OBJS) -o bin/test

%.o: %.cpp $(INCLUDES)
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(TEST_OBJS) main/*.o bin/*

run: $(app)
		bin/$(app)
