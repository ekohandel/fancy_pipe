TARGET_MODULE := fancy_pipe
$(TARGET_MODULE)-objs := src/fancy_pipe.o src/fancy_pipe_bus.o src/fancy_pipe_driver.o src/fancy_pipe_device.o
# If we are running by kernel building system
ifneq ($(KERNELRELEASE),)
	obj-m := $(TARGET_MODULE).o
# If we running without kernel build system
else
	BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
	PWD:=$(shell pwd)
all:
# run kernel build system to make module
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules
clean:
# run kernel build system to cleanup in current directory
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
load:
	insmod ./$(TARGET_MODULE).ko
unload:
	rmmod ./$(TARGET_MODULE).ko
endif