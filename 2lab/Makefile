CC = gcc

CFLAGS = -ansi -pedantic -Wall -g 

LDFLAGS = 

TARGET = mass

OBJS = $(TARGET).o

SRC = main.c

HEADERS = 

EXTRACLEAN = $(TARGET) 

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
	./$(TARGET)  input.test
