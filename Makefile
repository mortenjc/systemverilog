# Copyright (C) 2021 Morten Jagd Christensen, LICENSE: BSD2
#

include Makefile.macros

# User only needs to edit below
MODULES = clockdiv counter
UNITS = div10counter
UNITS.div10counter = src/modules/clockdiv.sv src/modules/counter.sv
# User only needs to edit above

TARGETS = $(addsuffix Test, $(addprefix bin/, $(MODULES))) $(addsuffix Test, $(addprefix bin/, $(UNITS)))

vpath %.sv src/modules src/units

all: directories $(TARGETS)
	@echo "done"

# Create dependencies using macros
# main targets
$(foreach module, $(MODULES), $(eval $(call make_bintargets,$(module))))
$(foreach unit, $(UNITS), $(eval $(call make_bintargets,$(unit))))
# dependencies
$(foreach module, $(MODULES), $(eval $(call make_mktargets,$(module),modules)))
$(foreach unit, $(UNITS), $(eval $(call make_mktargets,$(unit),units,$(UNITS.$(unit)))))


#
runtest: all $(TARGETS)
	for test in $(TARGETS); do ./$$test || exit 1; done

gtest:
	@./scripts/makegtest

# make sure build directory is created
.PHONY: directories
#
directories: build bin

build:
	@mkdir -p build
	@mkdir -p bin

# Misc clean targets
clean:
	@rm -fr build *.bak bin

realclean: clean
	@rm -fr googletest db output_files simulation
