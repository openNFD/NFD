# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2010-2014 Intel Corporation

# binary name
APP = NF

# all source are stored in SRCS-y
SRCS-y := NF.c basic_classes.c basic_methods.c

# Build using pkg-config variables if possible
$(shell pkg-config --exists libdpdk)
CPPFLAGS = -std=c++11 -lpcap
LDFLAGS = -lstdc++
ifeq ($(.SHELLSTATUS),0)

all: shared
.PHONY: shared static
shared: build/$(APP)-shared
	ln -sf $(APP)-shared build/$(APP)
static: build/$(APP)-static
	ln -sf $(APP)-static build/$(APP)

PC_FILE := $(shell pkg-config --path libdpdk)

#CFLAGS += -std=c++11
CFLAGS += -O3 $(shell pkg-config --cflags libdpdk)
LDFLAGS_SHARED = $(shell pkg-config --libs libdpdk)
LDFLAGS_STATIC = -lpcap, -Wl,-Bstatic $(shell pkg-config --static --libs libdpdk)

CFLAGS += -DALLOW_EXPERIMENTAL_API

build/$(APP)-shared: $(SRCS-y) Makefile $(PC_FILE) | build
	$(CC) $(CFLAGS) -std=c++11 $(SRCS-y) -o $@ $(LDFLAGS) $(LDFLAGS_SHARED)

build/$(APP)-static: $(SRCS-y) Makefile $(PC_FILE) | build
	$(CC) $(CFLAGS) -std=c++11 $(SRCS-y) -o $@ $(LDFLAGS) $(LDFLAGS_STATIC)

build:
	@mkdir -p $@

.PHONY: clean
clean:
	rm -f build/$(APP) build/$(APP)-static build/$(APP)-shared
	rmdir --ignore-fail-on-non-empty build

else # Build using legacy build system

ifeq ($(RTE_SDK),)
$(error "Please define RTE_SDK environment variable")
endif

# Default target, can be overridden by command line or environment
RTE_TARGET ?= x86_64-native-linuxapp-g++

include $(RTE_SDK)/mk/rte.vars.mk

CFLAGS += -DALLOW_EXPERIMENTAL_API
CFLAGS += $(WERROR_FLAGS)

# workaround for a gcc bug with noreturn attribute
# http://gcc.gnu.org/bugzilla/show_bug.cgi?id=12603
ifeq ($(CONFIG_RTE_TOOLCHAIN_GCC),y)
CFLAGS_main.o += -Wno-return-type
endif

EXTRA_CFLAGS += -O3 -g -Wfatal-errors

include $(RTE_SDK)/mk/rte.extapp.mk
endif
