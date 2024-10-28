all : stat display watershed

stat : parta.o pointcloud.o util.o bmp.o
	gcc -Wall -g -o stat parta.o pointcloud.o util.o bmp.o

display : display.o pointcloud.o util.o bmp.o
	gcc -Wall -g -o display display.o pointcloud.o util.o bmp.o

watershed : watershed.o pointcloud.o util.o bmp.o
	gcc -Wall -g -o watershed watershed.o pointcloud.o util.o bmp.o

parta.o : parta.c pointcloud.h util.h bmp.h
	gcc -Wall -g -c parta.c

display.o : display.c pointcloud.h util.h bmp.h
	gcc -Wall -g -c display.c

watershed.o : watershed.c pointcloud.h util.h bmp.h
	gcc -Wall -g -c watershed.c

pointcloud.o : pointcloud.c pointcloud.h util.h bmp.h
	gcc -Wall -g -c pointcloud.c

util.o : util.c util.h
	gcc -Wall -g -c util.c

bmp.o : bmp.c bmp.h
	gcc -Wall -g -c bmp.c

clean : 
	rm -f *.o *.gif stat display watershed

