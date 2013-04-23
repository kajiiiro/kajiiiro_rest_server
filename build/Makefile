TARGET = kajiiiro
OBJ    = main.o\
		uri.o\
		helper.o\
		session.o\
		request.o\
		response.o\
		server.o\
		sampleListener.o

CXXFLAGS = -Wall -std=c++0x
LIB = -lpthread

all:${TARGET}

${TARGET}:${OBJ}
	${CXX} -o ${TARGET} ${OBJ} ${LIB}

%.o:../src/%.cpp
	${CXX} -c ${CXXFLAGS} $^

clean:
	${RM} *.o ${TARGET}

