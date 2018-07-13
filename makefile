
LINK_TARGET = sandbox

OBJS =  \
AbstractClassShape.o \
ClassRectangle.o \
ClassTriangle.o \
ClassEllipse.o \
random_data.o \
sandbox.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all : $(LINK_TARGET)
	echo All done

# $@ expands to the rule's target, in this case "sandbox".
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
sandbox.o:  AbstractClassShape.h ClassRectangle.h ClassTriangle.h ClassEllipse.h

random_data.o : random_data.dat
	ld -r -b binary random_data.dat -o random_data.o
	nm random_data.o 
	echo Embed Binary done

unittest_rectangle: ClassRectangle.c ClassRectangle.h TestRectangle.c
	gcc TestRectangle.c AbstractClassShape.c ClassRectangle.c -o TestRectangle -lcunit && ./TestRectangle

unittest_sandbox: sandbox.c TestSandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o TestSandbox.c
	gcc -lcunit -lpthread AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o TestSandbox.c -o TestSandbox  && ./TestSandbox

debug : clean random_data.o
	gcc  -lpthread -fno-strict-aliasing -o $(LINK_TARGET)  -Wall -Werror -pedantic-errors -ggdb sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c random_data.o
	gdb $(LINK_TARGET)
	echo Debug done

run : $(LINK_TARGET)
	./$(LINK_TARGET)

memcheck : $(LINK_TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(LINK_TARGET)

commit :
	git add -u && git commit && git push origin

clean :
	rm -f $(REBUILDABLES)
	echo Clean done
