obj-m := submot.o

 KDIR	:= /work/kernel-mds2450-3.0.22

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

app:
	arm-none-linux-gnueabi-gcc -o app app.c

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -rf app

install:
	cp *.ko 	/home/rootfs
	cp app	/home/rootfs
