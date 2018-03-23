
#ARM Compile Option 
    
INCLUDEDIRS += -I/opt/arm-2010q1/lib/gcc/arm-none-linux-gnueabi/4.4.1/include  -I./
#header 파일이 어디있는지
    
CC = /opt/arm-2010q1/bin/arm-none-linux-gnueabi-gcc
#컴파일러의 위치
    
CFLAGS   += $(INCLUDEDIRS)
CFLAGS   += -Wall -O2 -pthread

LDFLAGS += -L/opt/arm-2010q1/lib/gcc/arm-none-linux-gnueabi/4.4.1/
#라이브러리의 위치

#
# Compilation target for C files
#
%.o:%.c
	@echo "Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<


TARGET = device_manager

OBJS =AcceptTCPConnection.o DieWithError.o device_manager.o HandleTCPClient.o
SRCS =AcceptTCPConnection.c DieWithError.c device_manager.c HandleTCPClient.c #소스파일 이름


$(TARGET) : $(OBJS) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS)  -o $@ 

dep :
	mkdep $(INCLUDEDIRS) $(SRCS)

clean :	
	rm -rf $(OBJS) $(TARGET) core

