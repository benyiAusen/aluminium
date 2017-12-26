#Simple makefile template

COM = gcc #Compiler to be used
OBJS = main.c #Objects to be compiled (.c/.h/.o)
COM_FLAGS = -Os -std=c11 #Compiler flags
LNK_FLAGS = #Linker flags
EXE = aluminium #Name of the final executable


std: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(LNK_FLAGS) -o $(EXE)
		
win: $(OBJS)
	$(COM) $(OBJS) $(COM_FLAGS) $(LNK_FLAGS) -o $(EXE).exe
	
clean:
	rm -f $(EXE) *.o
	
wclean:
	del *.o
	del *.exe
