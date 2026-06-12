FLAGS = *.c

make : 
	gcc -Wall -Wextra -g -o a.out ${FLAGS} `sdl2-config --cflags --libs` 
	./a.out
