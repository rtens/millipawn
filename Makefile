CXX = g++
CXXFLAGS = -g
SRCS = $(wildcard lib/src/*.cpp)
INCLUDES = $(wildcard lib/include/*.h)
OBJS = $(SRCS:.cpp=.o)

# %: main/%.o $(OBJS)
# 		$(CXX) $(CXXFLAGS) $< $(OBJS) -o bin/$@

tree: main/tree.o $(OBJS)
		$(CXX) $(CXXFLAGS) main/tree.o $(OBJS) -o bin/tree

spec: main/spec.o $(OBJS)
		$(CXX) $(CXXFLAGS) main/spec.o $(OBJS) -o bin/spec

%.o: %.cpp $(INCLUDES)
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) main/*.o bin/*

run: $(app)
		bin/$(app)
