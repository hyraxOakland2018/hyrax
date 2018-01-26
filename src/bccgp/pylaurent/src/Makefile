INCLPATHS := -I$(HOME)/toolchains/include
LIBPATHS := -Wl,-rpath,$(HOME)/toolchains/lib -L$(HOME)/toolchains/lib
LIBS := -lpthread -lgmp -lntl
CXXOPTS := -m64 -std=c++14 -Wall -Werror -Wextra -Wno-unused-parameter -Wshadow -Wpointer-arith -Wcast-qual -Wformat=2 -O2
SHARED := -fPIC -shared

all: pylaurent.so

pylaurent.so: pylaurent.cc
	$(CXX) $(INCLPATHS) $(CXXOPTS) $(SHARED) -o $@ $< $(LIBPATHS) $(LIBS)

.PHONY: clean
clean:
	@rm -f pylaurent.so
