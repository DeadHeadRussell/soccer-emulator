# Project: Soccer
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = main.o game.o $(RES)
LINKOBJ  = main.o game.o $(RES)
LIBS =  -L"H:/Dev-Cpp/lib" -mwindows  
INCS =  -I"H:/Dev-Cpp/include" 
CXXINCS =  -I"H:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include"  -I"H:/Dev-Cpp/include/c++/3.4.2/backward"  -I"H:/Dev-Cpp/include/c++/3.4.2/mingw32"  -I"H:/Dev-Cpp/include/c++/3.4.2"  -I"H:/Dev-Cpp/include" 
BIN  = Soccer.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before Soccer.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Soccer.exe" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

game.o: game.cpp
	$(CPP) -c game.cpp -o game.o $(CXXFLAGS)
