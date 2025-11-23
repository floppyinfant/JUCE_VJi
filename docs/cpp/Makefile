# GNU make
# https://www.gnu.org/software/make/manual/html_node/index.html

C = gcc
CXX = g++
#CXX = clang++

SOURCE_C = snippets.c
OBJECTS_C = snippets.o

SOURCE_CXX = 1.1.cpp

all:
	$(C) -c $(SOURCE_C)
	$(CXX) $(SOURCE_CXX) $(OBJECTS_C) $(LDFLAGS_COMMON) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)
