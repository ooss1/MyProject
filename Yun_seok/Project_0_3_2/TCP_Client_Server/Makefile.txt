
# ARM Compile Option 
    
INCLUDEDIRS += -I/usr/armv5l-linux/include  -I./
    
CC = armv5l-linux-gcc
    
CFLAGS   += $(INCLUDEDIRS)
CFLAGS   += -Wall -O2

LDFLAGS += -L/usr/armv5l-linux/lib

#
# Compilation target for C files
#
%.o:%.c
	@echo "Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<


TARGET = comtest

OBJS = comtest.o
SRCS = comtest.c


$(TARGET) : $(OBJS) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS)  -o $@ 

dep :
	mkdep $(INCLUDEDIRS) $(SRCS)

clean :	
	rm -rf $(OBJS) $(TARGET) core

