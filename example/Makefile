OOO = xx.o xxmain.o lib.o
xx:$(OOO)
	g++ $(OOO) -o xx
	rm $(OOO)
%.o:%.cpp
	g++ -c $< -o $@ -std=c++11
clean:
	rm $(OOO)
