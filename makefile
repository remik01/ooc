all: sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c AbstractClassShape.h ClassRectangle.h ClassTriangle.h ClassEllipse.h
	gcc -lpthread -fno-strict-aliasing -o sandbox sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c

debug: sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c AbstractClassShape.h ClassRectangle.h ClassTriangle.h ClassEllipse.h
	gcc  -lpthread -fno-strict-aliasing -o sandbox  -Wall -Werror -pedantic-errors -ggdb sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c

run:
	./sandbox

memcheck:
	valgrind --leak-check=yes --track-origins=yes ./sandbox
