OBJ= ui.o gui.o tui.o game.o control.o human.o AI.o main.o
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS += -std=c++11
PROG=main
CXX:=g++

all:${PROG}

%.o: %.cpp
	$(CXX) ${CXXFLAGS} -c $< -o $@

${PROG}:${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${PROG} ${LIBS}


clean:
	rm -fv *.0 $(OBJ) $(PROG)
