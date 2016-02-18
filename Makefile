obj-m+=Benchmarker.o
build:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
install:
	insmod Benchmarker.ko
uninstall:
	rmmod Benchmarker
output:
	dmesg | grep "Benchmarker:"
