all:
	gcc -o p MPC_SHA256.c -lcrypto -lssl
	gcc -o v MPC_SHA256_VERIFIER.c -lcrypto -lssl

clean:
	rm -f p v out137.bin
