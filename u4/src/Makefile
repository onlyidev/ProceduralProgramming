TARGET=main.c
OUTPUT=main
LIB=../lib

main: libstdmain.a $(TARGET)
	gcc $(TARGET) -L. -lstdmain -o $(OUTPUT)  

libstdmain.a: stdmain.o
	ar rc libstdmain.a stdmain.o 

stdmain.o:
	gcc -c $(LIB)/stdmain.c -o ./stdmain.o

clean:
	rm -rf ./*.o ./*.a
