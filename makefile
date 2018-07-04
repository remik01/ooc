all: sandbox.c ClassRectangle.c
	gcc -lpthread -fno-strict-aliasing -o sandbox sandbox.c ClassRectangle.c

run:
	./sandbox
