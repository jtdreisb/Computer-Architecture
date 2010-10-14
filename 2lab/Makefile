CC = gcc

CFLAGS = -ansi -pedantic -Wall -g 

LDFLAGS = 

TARGET = lab2

OBJS = $(TARGET).o

SRC = main.c

HEADERS = 

EXTRACLEAN = $(TARGET) 

DIFF = diff -w -B 

all: clean $(OBJS) $(TARGET)

allclean: clean
	@rm -f $(EXTRACLEAN) 
clean:
	rm -f $(OBJS)
$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c -o $(OBJS) $(SRC)	
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) 
depend:
	@echo Regenerating local dependencies
	@makedepend $(SRC) $(HEADERS)
tags: $(SRC) $(HEADERS)
	cscope -b $(SRC) $(HEADERS)
test:
	./$(TARGET)  test1.asm > our1.out
	$(DIFF) our1.out test1.output
	./$(TARGET)  test2.asm > our2.out
	$(DIFF) our2.out test2.output
	./$(TARGET)  test3.asm > our3.out
	$(DIFF) our3.out test3.output

