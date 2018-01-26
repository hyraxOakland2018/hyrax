# makefile for bccgp
# (C) 2018 Hyrax Authors
#

.PHONY: all clean lint
all:
	@+$(MAKE) -C ../fennel
	@+$(MAKE) -C pylaurent/src

clean:
	@+$(MAKE) -C ../fennel clean
	@+$(MAKE) -C pylaurent/src clean

lint:
	@echo "Linting bccgp:"
	@-pylint libbccgp/
	@echo "Done."
