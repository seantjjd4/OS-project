obj-m = myDataStruct.o

default:
	make -C/lib/modules/$(shell uname -r)/build M=`pwd` modules

clean:
	rm -rf *.o *.ko *.mod.c *.cmd *.markers *.order *.symvers *.tmp_versions *.mod
