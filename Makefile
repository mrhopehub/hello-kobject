obj-m += hello-kobject.o
KERNELDIR := /usr/src/linux
PWD := $(shell pwd)  
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install  
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
