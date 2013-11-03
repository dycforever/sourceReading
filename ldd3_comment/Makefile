
SUBDIRS =  misc-progs misc-modules \
	skull scull scullc sculld scullp scullv \
			short shortprint pci simple usb tty lddbus
#           skull scull scullc sculld scullp scullv sbull snull
all: subdirs

subdirs:
	for n in $(SUBDIRS); do $(MAKE) -C $$n || exit 1; done

clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
