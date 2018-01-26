# ZKBoo source

This is a slightly modified version of the SHA-256 ZKBoo implementation
available from https://github.com/Sobuno/ZKBoo

The primary difference is that this implementation does not link against
OpenMP, since all of our experiments are run with a single thread. I have
also added a Makefile and I have modified the code to accept a commandline
argument indicating how many SHA-256 instances sould be proved/verified.

## Building

You will need the OpenSSL 1.0 development headers and shared library in
order to build this. On Debian-like systems, you can install these with

    apt-get install libssl1.0.2 libssl1.0-dev

Please note that the above command will also uninstall the OpenSSL1.1
headers, if those are installed on your machine!

## Running

See the run script in `src/pws/experiments/zkboo/run.sh` for details.
