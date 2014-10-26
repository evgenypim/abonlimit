obj-m := abonlimit.o
abonlimit-objs := xt_abonlimit.o
all: libxt_abonlimit modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) KBUILD_EXTMOD=$(PWD) modules

libxt_abonlimit:
	$(CC) -shared libxt_abonlimit.c -fPIC -o libxt_abonlimit.so

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean; rm *.so
