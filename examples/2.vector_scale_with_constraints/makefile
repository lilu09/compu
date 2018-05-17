
 
CFLAGS += $(shell pkg-config --cflags libstarpu) 
LDFLAGS += $(shell pkg-config --libs libstarpu) 
 
all: main 
 
main : main.o vector_scale_cpu.o 
	g++ main.o vector_scale_cpu.o $(CFLAGS) $(LDFLAGS) -o main 
main.o : main.c 
	g++ main.c $(CFLAGS) -std=c++11 -c -o main.o 
vector_scale_cpu.o : ./vector_scale/vector_scale_cpu.c 
	g++ ./vector_scale/vector_scale_cpu.c $(CFLAGS) -c -o vector_scale_cpu.o 

 
clean: 
	rm -f main *.o *~ 
 