#Simple makefile template

COM = gcc #Compiler to be used
OBJS = main.c #Objects to be compiled (.c/.h/.o)
COM_FLAGS = -std=c11 -O2 -march=native -fomit-frame-pointer #Compiler flags
LNK_FLAGS = -static-libgcc -s #Linker flags
EXE = aluminium #Name of the final executable


all: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(LNK_FLAGS) -o $(EXE)
	
clean:
	rm -f $(EXE) *.o
