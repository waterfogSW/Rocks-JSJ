CC = g++
INC = -I${CURDIR}/include/
CFLAGS = -g $(INC)

LIBS= -lrocksdb

OBJS = genByCSV.o genByRandom.o hello.o

SRCS = $(OBJS:.o=.c)

TARGET = hello

.SUFFIXES : .c .o

.c.o:
	@echo "Compiling$< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

all : $(TARGET)

dep : 
	gccmaedep $(INC) $(SRCS)

clean :
	@echo "Cleaning$< ..."
	rm -rf $(OBJS) $(TARGET) 

new :
	$(MAKE) clean
	$(MAKE)