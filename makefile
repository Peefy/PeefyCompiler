
CC=g++

SRCS=./src/compiler.cpp

OBJS=$(SRCS:.cpp=.o)

EXEC=compiler
all:start run 
start:$(OBJS)
		$(CC) -o $(EXEC) $(OBJS)
.cpp.o:
		$(CC) -o $@ -c $< -DMYLINUX
.PHONY:clean
clean:
		-rm -rf $(OBJS)
run:
	./$(EXEC)
