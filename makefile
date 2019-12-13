
CC=gcc

SRCS=./src/peefyc4/compiler.c
SRCS_C4=./third_party/c4/c4.c
SRCS_PEEFY=./src/peefycpp/peefy.cpp
SRCS_PEEFY_GO=./src/peefygo/peefy.go

TESTSRC=./test/test.c

OBJS=$(SRCS:.cpp=.o)
OBJS_C4=$(SRCS_C4:.cpp=.o)
OBJS_PEEFY=$(SRCS_PEEFY:.cpp=.o)

EXEC=dugu
EXEC_C4=c4
EXEC_PEEFY=peefy
all:start run clean
peefy:peefyc peefyr
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
peefyc:$(OBJS_PEEFY)
		g++ -o $(EXEC_PEEFY) $(OBJS_PEEFY)
peefyr:
	./$(EXEC_PEEFY)
peefygo:
	go run $(SRCS_PEEFY_GO)

