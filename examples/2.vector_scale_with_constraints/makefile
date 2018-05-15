
 
CFLAGS += $(shell pkg-config --cflags libstarpu) 
LDFLAGS += $(shell pkg-config --libs libstarpu) 
 
all: main 
 
main : main.o vector_scale_cpu.o vector_scale_cuda.o 
	g++ main.o vector_scale_cpu.o vector_scale_cuda.o $(CFLAGS) $(LDFLAGS) -o main 
main.o : main.c 
	g++ main.c $(CFLAGS) -std=c++11 -c -o main.o 
vector_scale_cpu.o : ./vector_scale/vector_scale_cpu.c 
	g++ ./vector_scale/vector_scale_cpu.c $(CFLAGS) -c -o vector_scale_cpu.o 
vector_scale_cuda.o : ./vector_scale/vector_scale_cuda.cu 
	nvcc ./vector_scale/vector_scale_cuda.cu $(CFLAGS) --compiler-options -fpermissive -c -o vector_scale_cuda.o 

 
clean: 
	rm -f main *.o *~ 
 