CXX = g++
CXXFLAGS = -Wall -std=c++17
PROG = main
PROG_OBJ = ui.o tui.o game.o main.o 

all:	$(PROG)
$(PROG): $(PROG_OBJ)
		$(CXX) $(CXXFLAGS) -o	$@ $^
.o: .cpp
		$(CXX) -c $^
clean:
	rm -fv *.0 $(PROG_OBJ) $(PROG)
