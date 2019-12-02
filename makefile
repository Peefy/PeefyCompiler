
CC=gcc

SRCS=./src/compiler.c

SRCS_C4=./third_party/c4/c4.c

TESTSRC=./test/test.c

OBJS=$(SRCS:.cpp=.o)

OBJS_C4=$(SRCS_C4:.cpp=.o)

EXEC=dugu
EXEC_C4=c4
all:start run clean
start:$(OBJS)
		$(CC) -o $(EXEC) $(OBJS)
c4:$(OBJS_C4)
		$(CC) -o $(EXEC_C4) $(OBJS_C4)
.cpp.o:
		$(CC) -o $@ -c $< -DMYLINUX
.PHONY:clean
clean:
	-rm -rf $(OBJS)
run:
	./$(EXEC)
r:
	./$(EXEC) -s-d $(TESTSRC)
r4:
	./$(EXEC_C4) -s-d $(TESTSRC)
