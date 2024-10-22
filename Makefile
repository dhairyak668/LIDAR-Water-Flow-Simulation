all : stat

stat : util.o pointcloud.o 
	gcc -Wall -g -o stat util.o pointcloud.o 

pointcloud.o : pointcloud.c pointcloud.h util.h
	gcc -Wall -g -c pointcloud.c

util.o : util.c util.h
	gcc -Wall -g -c util.c

clean : 
	rm -f *.o stat

