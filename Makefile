CC = gcc
CFLAG = 
SRC = main.c
SRC += src/platform_basic_func.c src/platform_basic_func.h  src/Seeed_3D_touch_mgc3030.c src/Seeed_3D_touch_mgc3030.h
LIB = -lwiringPi -lcurses

EXEC_NAME = mgc3030

all: 
	$(CC) $(CFLAG) $(SRC) $(LIB) -o $(EXEC_NAME)
clean:
	rm -f $(EXEC_NAME)