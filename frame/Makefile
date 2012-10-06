SOURCE = $(wildcard ./src/photo/*.c)
EFFECT = $(wildcard ./src/effect/*.c)			

OBJFILE = $(patsubst %.c,%.o,$(SOURCE))
CC = gcc
CFLAGS = -g -Iinclude -ljpeg -lpthread

mode1_print_photo_1.out: ./src/out/mode1_1.c $(SOURCE)
	gcc -o mode1_print_photo_1.out $^ $(CFLAGS)	
mode1_print_photo_2.out: ./src/out/mode1_2.c $(SOURCE)
	gcc -o mode1_print_photo_2.out $^ $(CFLAGS)	
mode1_print_photo_3.out: ./src/out/mode1_3.c $(SOURCE)
	gcc -o mode1_print_photo_3.out $^ $(CFLAGS)	
mode1_print_photo_4.out: ./src/out/mode1_4.c $(SOURCE)
	gcc -o mode1_print_photo_4.out $^ $(CFLAGS)	
mode1_print_photo.out: ./src/out/model.c $(SOURCE) $(EFFECT)
	gcc -o mode1_print_photo.out $^ $(CFLAGS)	




app: 
	gcc -o a.out ./src/main/mode3.c ./src/main/hxk_mouse.c $(CFLAGS)

start: ./src/main/main.c $(SOURCE)
	gcc -o start.out $^ $(CFLAGS)


	

clean: 
	rm *.out
.PHONY: clean
