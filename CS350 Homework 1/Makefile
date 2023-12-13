obj-m	:= hello_driver.o
KDIR 	:= /lib/modules/$(shell uname -r)/build
PWD 	:= $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -r *.o *.ko *mod* *sym*
