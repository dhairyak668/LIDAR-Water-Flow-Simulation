all : stat

stat : pointcloud.o
	gcc -Wall -g -o stat pointcloud.o

pointcloud.o : pointcloud.c pointcloud.h
	gcc -Wall -g -c pointcloud.c

clean : 
	rm -f *.o stat
