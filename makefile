all: sandbox.c ClassRectangle.c
	gcc -lpthread -o sandbox sandbox.c ClassRectangle.c

run:
	./sandbox
