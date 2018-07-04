all: sandbox.c ClassRectangle.c
	gcc -lpthread -fno-strict-aliasing -o sandbox sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c

run:
	./sandbox
