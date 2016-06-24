obj-m+=Benchmarker.o
#CC = g++
#CFLAGS = -fno-rtti -nostdlib -nostartfiles -fno-exceptions -Xlinker -gc-sections -std=c++14
build:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
install:
	insmod Benchmarker.ko
uninstall:
	rmmod Benchmarker
output:
	dmesg | tail
objdump:
	objdump -s -a -x Benchmarker.ko
