
LINK_TARGET = sandbox

OBJS =  \
AbstractClassShape.o \
ClassRectangle.o \
ClassTriangle.o \
ClassEllipse.o \
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


unittest: ClassRectangle.c ClassRectangle.h TestRectangle.c
	gcc TestRectangle.c AbstractClassShape.c ClassRectangle.c -o TestRectangle -lcunit && ./TestRectangle

debug : clean
	gcc  -lpthread -fno-strict-aliasing -o sandbox  -Wall -Werror -pedantic-errors -ggdb sandbox.c AbstractClassShape.c ClassRectangle.c ClassTriangle.c ClassEllipse.c
	echo Debug done

run :
	./sandbox

memcheck :
	valgrind --leak-check=yes --track-origins=yes ./sandbox

commit :
	git add -u && git commit && git push origin

clean :
	rm -f $(REBUILDABLES)
	echo Clean done
