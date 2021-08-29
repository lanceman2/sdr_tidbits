
SUBDIRS := bin

# add tests/ to make if we are cleaning:
ifeq ($(strip $(subst cleaner, clean, $(MAKECMDGOALS))),clean)
SUBDIRS +=\
 tests
endif


ifneq ($(wildcard quickbuild.make),quickbuild.make)
$(error "First run './bootstrap'")
endif



CLEANFILES := xxx_quickbuild.make_HASH_FAIL

include ./quickbuild.make
