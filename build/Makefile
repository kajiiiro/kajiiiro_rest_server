TARGET = kajiiiro
SRC    = ../src/main.cpp\
		../src/db.cpp\
		../src/uri.cpp\
		../src/helper.cpp
OBJ    = main.o\
		db.o\
		uri.o\
		helper.o

CXXFLAGS = -Wall -std=c++0x

all:${TARGET}

${TARGET}:${OBJ}
	${CXX} -o ${TARGET} ${OBJ}

${OBJ}:${SRC}
	${CXX} -c ${CXXFLAGS} ${SRC}

clean:
	${RM} *.o ${TARGET}

