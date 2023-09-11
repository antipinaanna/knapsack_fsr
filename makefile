all: main.o conditions.o knapsack.o solver.o
	g++ -o knapsack main.o conditions.o knapsack.o solver.o
main.o: main.cpp conditions.h knapsack.h solver.h
	g++ -c -g main.cpp

conditions.o: conditions.cpp conditions.h
	g++ -c -g conditions.cpp

knapsack.o: knapsack.cpp knapsack.h
	g++ -c -g knapsack.cpp

solver.o: solver.cpp solver.h
	g++ -c -g solver.cpp

clean: cleanobj cleanmain 

cleanobj:
	rm -f *.o

cleanmain:
	rm knapsack

.PHONY: clean cleanobj cleanmain