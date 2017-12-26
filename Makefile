#Simple makefile template

COM = gcc #Compiler to be used
OBJS = main.c #Objects to be compiled (.c/.h/.o)
COM_FLAGS = -O3 -Wall -std=c11 #Compiler flags
LNK_FLAGS = #Linker flags
EXE = aluminium #Name of the final executable


all: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(LNK_FLAGS) -o $(EXE)

clean:
	rm -f $(EXE) *.o