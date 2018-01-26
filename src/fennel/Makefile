# makefile for Fennel
# (C) 2017 Hyrax Authors
#
# build pylibpws solib
.PHONY: all clean lint

all: ../libpws/config.log ../miracl/config.log
	@+$(MAKE) -C ../libpws
	@+$(MAKE) -C ../miracl

../libpws/configure: ../libpws/configure.ac
	@echo "Generating pylibpws config script"
	@cd ../libpws && ./autogen.sh

../libpws/config.log: ../libpws/configure
	@echo "Configuring pylibpws"
	@cd ../libpws && ./configure

../miracl/configure: ../miracl/configure.ac
	@echo "Generating pymiracl config script"
	@cd ../miracl && ./autogen.sh

../miracl/config.log: ../miracl/configure
	@echo "Configuring pymiracl"
	@cd ../miracl && ./configure

clean:
	@+$(MAKE) -C ../libpws distclean
	@+$(MAKE) -C ../miracl distclean

lint:
	@echo "Linting libfennel:"
	@-pylint libfennel/
	@echo
	@echo "Linting libfenneltests:"
	@-pylint libfenneltests/
	@echo "Done."
