TARGET = kajiiiro
OBJ    = main.o\
		db.o\
		uri.o\
		helper.o\
		session.o\
		request.o\
		response.o\
		server.o\
		sampleListener.o

CXXFLAGS = -Wall -std=c++0x

all:${TARGET}

${TARGET}:${OBJ}
	${CXX} -o ${TARGET} ${OBJ}

%.o:../src/%.cpp
	${CXX} -c ${CXXFLAGS} $^

clean:
	${RM} *.o ${TARGET}

