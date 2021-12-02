obj-m := led.o
led-objs:=ledmodule.o utils.o
KDIR := /home/sofia/buildroot/buildroot-2021.02.5/output/build/linux-custom
ARCH ?= arm64


CROSS_COMPILE = /home/sofia/buildroot/buildroot-2021.02.5/output/host/bin/aarch64-linux-

export ARCH CROSS_COMPILE


KBUILD_TARGETS	:= clean help modules modules_install

.PHONY: all $(KBUILD_TARGETS)

all: modules
$(KBUILD_TARGETS):
	#$(MAKE) -C $(KDIR) M=$(shell pwd) $@ EXTRA_CFLAGS="$(MY_CFLAGS)"
	$(MAKE) -C $(KDIR) M=$(shell pwd) $@
