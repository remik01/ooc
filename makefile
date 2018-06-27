all: sandbox.c ClassRectangle.c
	gcc -o sandbox sandbox.c ClassRectangle.c

run:
	./sandbox
