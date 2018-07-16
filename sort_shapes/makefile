
LINK_TARGET = sort_shapes

OBJS =  \
AbstractClassShape.o \
ClassRectangle.o \
ClassTriangle.o \
ClassEllipse.o \
random_data.o \
sort_shapes.o

TESTS = \
TestRectangle \
TestSortShapes \

REBUILDABLES = $(OBJS) $(LINK_TARGET) $(TESTS)

all : $(LINK_TARGET)
	echo All done

# $@ expands to the rule's target, in this case "sort_shapes".
# $^ expands to the rule's dependencies, in this case the files in OBJS
$(LINK_TARGET) : $(OBJS)
	gcc -lpthread -fno-strict-aliasing -o $@ $^

# $@ is the pattern-matched target
# $< is the pattern-matched dependency
%.o : %.c
	gcc -lpthread -fno-strict-aliasing -o $@ -c $<

AbstractClassShape.o: AbstractClassShape.h
ClassRectangle.o: AbstractClassShape.h ClassRectangle.h
ClassTriangle.o:  AbstractClassShape.h ClassTriangle.h
ClassEllipse.o:  AbstractClassShape.h ClassEllipse.h
sort_shapes.o:  AbstractClassShape.h ClassRectangle.h ClassTriangle.h ClassEllipse.h

random_data.o : random_data.dat
	ld -r -b binary random_data.dat -o random_data.o
	nm random_data.o 
	echo Embed Binary done

unittest_rectangle:
	gcc TestRectangle.c AbstractClassShape.c ClassRectangle.c -o TestRectangle -lcunit && ./TestRectangle

unittest_sort_shapes:
	gcc -lcunit -lpthread AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o TestSortShapes.c -o TestSortShapes  && ./TestSortShapes

debug : clean random_data.o
	gcc  -lpthread -fno-strict-aliasing -o $(LINK_TARGET)  -Wall -Werror -pedantic-errors -ggdb sort_shapes.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o
	gdb $(LINK_TARGET)
	echo Debug done

profile : clean random_data.o
	gcc  -lpthread -Wall -pg -no-pie sort_shapes.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o -o $(LINK_TARGET)
	./$(LINK_TARGET)
	gprof -b $(LINK_TARGET)
	echo Profiling done

run : $(LINK_TARGET)
	./$(LINK_TARGET)

memcheck : $(LINK_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(LINK_TARGET)

commit :
	git add -u && git commit && git push origin

clean :
	rm -f $(REBUILDABLES)
	echo Clean done
