all : stat display

stat : parta.o pointcloud.o util.o bmp.o
	gcc -Wall -g -o stat parta.o pointcloud.o util.o bmp.o -lm

display : display.o pointcloud.o util.o bmp.o
	gcc -Wall -g -o display display.o pointcloud.o util.o bmp.o -lm

pointcloud.o : pointcloud.c pointcloud.h util.h bmp.h
	gcc -Wall -g -c pointcloud.c

util.o : util.c util.h
	gcc -Wall -g -c util.c

bmp.o : bmp.c bmp.h
	gcc -Wall -g -c bmp.c

clean : 
	rm -f *.o *.gif stat display

