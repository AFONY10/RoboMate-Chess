SOURCES=main.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXECUTABLE=RoboMate_PSoC
CXX=garm-rpizw-g++

all: ${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CXX} -o $@ $^

%.o: %.cpp
	${CXX} -c -o $@ $^

clean: 
	rm -f ${EXECUTABLE} ${OBJECTS}

help:
	@echo "Available targets:"
	@echo "	all		: Compile the program (default target)"
	@echo "	clean	: Remove object files and the executable"
	@echo "	help	: Print this help message"