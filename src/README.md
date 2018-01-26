# `bccgp/`

This directory contains our BCCGP-sqrt and Bulletproofs implementations.

If this directory contains unresolved symbolic links, you haven't built.
See the main README file for more information.

`libfennel/` and `pymircffi/` are symbolic links into `../fennel/`; see descriptions there.

- `run_bccgp.py` is the driver script for BCCGP-sqrt and Bulletproofs. Run with `--help` or see scripts in `../pws/experiments/` for more information.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`libbccgp/`

This is the Python library implementing the bulk of BCCGP-sqrt and Bulletproofs.

- `bccgp.py` is the BCCGP-sqrt implementation

- `bullet.py` is the Bulletproofs implementation

- `pws.py` is the AC-to-constraints compiler

- `solve.py` generates satisfying a satisfying assignment from a set of constraints and a program that produces a witness from the public inputs.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`pylaurent/`

This directory contains a C library and Python CFFI linkage for calling NTL from the BCCGP-sqrt prover.

# `fennel/`

This directory contains our Hyrax and Hyrax-naive implementations.

- `pws_info.py` displays useful information about Hyrax's representation of a PWS file.

- `run_fennel.py` is the driver script for Hyrax and Hyrax-naive. Run with `--help` or see scripts in `../pws/experiments/` for more information.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`libfennel/`

This is the Python library implementing Gir++ and all ZK sub-protocols, plus other scaffolding shared among Hyrax, Hyrax-naive, BCCGP-sqrt, and Bulletproofs. Highlights:

- `circuitnizkvecwit.py` implements the Hyrax prover and verifier.

- `circuitnizk.py` implements the Hyrax-naive prover and verifier.

- `circuitprover.py` and `circuitverifier.py` implement the Gir++ prover and verifier, respectively.

- `commit.py` implements commitment primitives.

- `fiatshamir.py` implements the Fiat-Shamir transform.

- `rdlprover.py` implements a specialized Gir++ prover for RDLs.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`libfenneltests/`

This directory comprises a test suite. You can run it with, e.g., `python libfenneltests/ 10` to run each test 10 times.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`pymircffi/`

This is the Python CFFI linkage to our multi-exponentiation library; for more information, see `../miracl`.

## &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`pypws/`

This is the Python CFFI linkage to our PWS parser library; for more information, see `../libpws`.

# `libpws/`

This directory contains a library and several utilities for working with PWS files.

- `src/circuit/` is the main PWS parsing code.

- `src/pws2svg/` renders PWS files (as interpreted by Hyrax) as SVG files.

- `src/pwsrepeat/` consumes a PWS and produces a new one repeating the same computation a specified number of times in parallel.

- `src/pylibpws/` implements a simple interface to the PWS parsing code in `src/circuit/`.

# `miracl/`

This directory contains our C library for fast multi-exponentiation and the MIRACL Crypto SDK.

- `lib/` contains curve definitions and Sage scripts for regenerating them.

- `src/miracl/` contains the MIRACL Crypto SDK, with minor modifications and bugfixes.

- `src/pymircffi/` contains our multi-exponentiation library.

# `pws/`

This directory contains our scripts for generate PWS files and our driver scripts for running experiments.

- `lanczos2.py` generates image scaling PWS and RDL files

- `matmult.py` generates matrix factoring PWS files

- `sha256gen.py` generates SHA-256 PWS files and Merkle tree RDLs

- `experiments/` contains all of our experimental driver scripts. In the `lanczos2`, `matmult`, and `SHA256` subdirectories, `build.sh` generates the necessary PWS files, `run.sh` runs the experiments, `process.sh` processes the outputs, and `plot.sh` generates plots.

# `zkboo/`

This directory contains the ZKBoo implementation we tested. See the README file in this directory for more information.
