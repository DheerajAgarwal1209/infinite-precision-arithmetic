CC = g++  
CFLAGS = -Wno-all -c 

all : my_inf_arith

libmy_inf_arith : float.o main.o integer.o
	g++ float.o main.o integer.o -o my_inf_arith
	ar rcs libmy_inf_arith.a float.o main.o integer.o
               
my_inf_arith : float.o main.o integer.o
	g++ float.o main.o integer.o -o  my_inf_arith
             
integer.o : integer.cpp infinitearithmetic.h
	$(CC)   $(CFLAGS) integer.cpp -o integer.o
            
float.o : float.cpp infinitearithmetic.h
	$(CC)   $(CFLAGS) float.cpp -o float.o
            
main.o : main.cpp infinitearithmetic.h
	$(CC)   $(CFLAGS) main.cpp -o main.o

clean:
	rm *.o
	rm my_inf_arith
	rm *.a