all :  eigenval

eigenval : main.o input.o rot_method.o ref_method.o
	gcc main.o input.o rot_method.o ref_method.o -lm -o eigenval

main_1.o : main.c
	gcc -c main.c
	
input.o : input.c
	gcc -c input.c

rot_method.o : rot_method.c
	gcc -c rot_method.c

ref_method.o : ref_method.c
	gcc -c ref_method.c

clean:
	rm -rf *.o eigenval

#.o - объектные файлы
