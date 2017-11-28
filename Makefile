OBJS=scanner.o parser.o ast.o code.o compiler.o
INTERM=scanner.c parser.c parser.h
PROGRAM=./compiler
CFLAGS=-g -w

all: $(PROGRAM)




scanner.c: newScanner.flex parser.h
	flex -o scanner.c newScanner.flex
#scanner.c: scanner.flex parser.h
#	flex -o scanner.c scanner.flex


parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS) $(INTERM)

test: $(PROGRAM)
	$(PROGRAM) tests/testesTrabalho/example1.txt
	$(PROGRAM) tests/testesTrabalho/exampleFunc.txt
	
	


