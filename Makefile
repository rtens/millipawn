CXX = g++
CXXFLAGS = -g
TARGET = bin/test
SRCS = $(wildcard test/*.cpp) $(wildcard lib/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(wildcard lib/include/*.h)
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(TARGET)

run: $(TARGET)
		bin/test
