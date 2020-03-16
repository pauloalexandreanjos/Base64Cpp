EXEC = base64.exe

CC=g++

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

all: myprog

myprog: $(obj)
	$(CC) -o $(EXEC) $^
	
.PHONY: clean
clean:
	del $(obj) $(EXEC)