
Participant: Rithesh Girish Gowda

***********************************************************
Programming language used: C++

***********************************************************
Description: These programs are used to encrypt and decrypt messages for classical ciphers.

***********************************************************
Instructions to compile and execute code:

1. To compile, simply, type "make" at the terminal which will generate .obj file and .exe file.
2. To execute, type in the terminal in the form as follows: .\cipher <CIPHER NAME> <KEY> <ENC\DEC> <INPUTFILE> <OUTPUT FILE>
Example: .\cipher PLF security ENC input.txt output.txt

***********************************************************
Cipher names: CES: Caesar
              PLF: Playfair
	      RTS: Row Transposition
	      RFC: Railfence
	      VIG: Vigenre
	      MAC: Monoalphabetic
	      HIL: Hill

Cipher key: CES: An integer between 1-25. Ex: 7
	       Can be executed using the cmd: .\cipher CES 7 ENC y1.txt y2.txt
            PLF: String of letters. Ex: security
               Can be executed using the cmd: .\cipher PLF security ENC y1.txt y2.txt
	    RTS: Integers separated by comma. Ex: 5,2,1,3,4
               Can be executed using the cmd: .\cipher RTS 5,2,1,3,4 ENC y1.txt y2.txt
	    RFC: Any integer Ex: 5
               Can be executed using the cmd: .\cipher RFC 5 ENC y1.txt y2.txt
	    VIG: String of letters. Ex: security
               Can be executed using the cmd: .\cipher VIG security ENC y1.txt y2.txt
	    MAC: Doesn't require key as it matches each alphabet to a random alphabet.
               Can be executed using the cmd: .\cipher MAC 0 ENC y1.txt y2.txt
	    HIL: Set of 4 integers separated by comma. Ex: 3,4,9,7
               Can be executed using the cmd: .\cipher HIL 3,4,9,7 ENC y1.txt y2.txt

***********************************************************
Extra Credit: Only Hill cipher was attempted for a 2*2 matrix due to lack of time and complexity.


                                                                                        -End-
