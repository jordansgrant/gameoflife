CXX = g++

CXXFLAGS = -Wall
CXXFLAGS += -pedantic-errors

LDFLAGS = 

SRCS = golFunctions.cpp gameOfLife.cpp 

HEADERS = golFunctions.hpp

OBJS = golFunctions.o gameOfLife.o

#will compile GameOfLife and generate .o files
#use clean command to remove .o files
all: GameOfLife

#Build executable from object files and headers and name GameOfLife
GameOfLife: ${OBJS} ${HEADERS} 
	${CXX} ${LDFLAGS} ${OBJS} -o GameOfLife
	
#Build each source file into an object file independently	
${OBJS}: ${SRCS} 
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

#prevent the creation of a clean file
.PHONY: clean

#remove all extraneous files such as .o and a.out files
clean:
	rm -rf *.o a.out
	

	
