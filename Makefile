##############################################################
CC = gcc
CFLAGS = -g -Wall
EJS = p3_e1 p3_e2a p3_e2b p3_e3
LDFLAGS = -L.
LDLIBS = -lqueue
##############################################################
OBJECTSP3E1 = p3_e1.o vertex.o delivery.o
OBJECTSP3E2A = p3_e2a.o vertex.o queue.o delivery.o file_utils.o
OBJECTSP3E2B = p3_e2b.o vertex.o graph.o queue.o stack.o file_utils.o
OBJECTSP3E3 = p3_e3.o list.o file_utils.o
##############################################################

all: $(EJS) clear

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1) $(LDFLAGS) $(LDLIBS)

p3_e2a: $(OBJECTSP3E2A)
	$(CC) $(CFLAGS) -o p3_e2a $(OBJECTSP3E2A)

p3_e2b: $(OBJECTSP3E2B)
	$(CC) $(CFLAGS) -o p3_e2b $(OBJECTSP3E2B)

p3_e3: $(OBJECTSP3E)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)

p3_e1.o: p3_e1.c vertex.h delivery.h queue.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2a.o: p3_e2a.c vertex.h delivery.h queue.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e2a.c
	
p3_e2b.o: p3_e2b.c
	$(CC) $(CFLAGS) -c p3_e2b.c
	
p3_e3.o: p3_e3.c list.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e3.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h stack.h vertex.h
	$(CC) $(CFLAGS) -c graph.c

delivery.o: delivery.c delivery.h queue.h
	$(CC) $(CFLAGS) -c delivery.c

file_utils.o: file_utils.c
	$(CC) $(CFLAGS) -c file_utils.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>>>>>Running p3_e1"
	./p3_e1 requests.txt
	@echo ">>>>>>>>>>Running p3_e2a"
	./p3_e2a requests.txt
	@echo ">>>>>>>>>>Running p3_e2b"
	./p3_e2b city_graph.txt 100 700
	@echo ">>>>>>>>>>Running p3_e3"
	./p3_e3 grades.txt 1
	@echo ">>>>>>>>>>Running p3_e3"
	./p3_e3 grades.txt -1
runv:
	@echo "Running p3_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e1 requests.txt
	@echo "Running p3_e2a with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2a requests.txt
	@echo "Running p3_e2b with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2b city_graph.txt 100 700
	@echo "Running p3_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e3 grades.txt 1
	@echo "Running p3_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e3 grades.txt -1
