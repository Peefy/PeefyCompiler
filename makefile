
CC=g++

SRCS=./src/compiler.cpp

TESTSRC=./test/test.c

OBJS=$(SRCS:.cpp=.o)

EXEC=dugu
all:start run clean
start:$(OBJS)
		$(CC) -o $(EXEC) $(OBJS)
.cpp.o:
		$(CC) -o $@ -c $< -DMYLINUX
.PHONY:clean
clean:
	-rm -rf $(OBJS)
run:
	./$(EXEC)

test:
	./$(EXEC) $(TESTSRC)
