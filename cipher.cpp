#include <string>
#include "CipherInterface.h"
#include "Playfair.h"
#include "Caesar.h"
#include "Railfence.h"
#include "RowTransposition.h"
#include "Vigenere.h"
#include "Monoalphabetic.h"
#include "Hill.h"
#include <iostream>
#include <fstream>

using namespace std;

// function to make string all uppercase
void toUppercase(string& str)
{
	for (int i=0; i<str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
}

int main(int argc, char** argv)
{
	string cipherName = argv[1];
	string key = argv[2];
	string mode = argv[3];
	string inputFile = argv[4];
	string outputFile = argv[5];
	string outputData;

	cout <<cipherName <<key <<mode <<inputFile <<outputFile <<endl;

	// open file to read its content
	ifstream readFile;
	string inputData;

	readFile.open(inputFile.c_str());
	readFile >> inputData;
	readFile.close();

	toUppercase(inputData); // Converting the data into all uppercase
	cout << "Data received: "<< inputData << endl;

	CipherInterface* cipher = NULL;

	// Create an instance for all the cipher
	if ( cipherName == "PLF")
		cipher = new Playfair();
	else if ( cipherName == "RTS")
		cipher = new RowTransposition();
	else if ( cipherName == "RFC")
		cipher = new Railfence();
	else if ( cipherName == "VIG")
		cipher = new Vigenere();
	else if ( cipherName == "CES")
		cipher = new Caesar();
		else if ( cipherName == "MAC")
			cipher = new Monoalphabetic();
	else if ( cipherName == "HIL")
		cipher = new Hill();
	else
	{
		cout << "Incorrect cipher name. Valid names are:" << endl;
		cout << "– PLF: Playfair\n"<<
				"– RTS: Row Transposition\n"<<
				"– RFC: Railfence\n"<<
				"– VIG: Vigenre\n"<<
				"– CES: Caesar\n"<<
				"- MAC: Monoalphabetic\n"<<
				"_ HIL: Hill\n";
		cout << "Execution: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>\n";
		exit(-1);
	}

	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	/* Set the encryption key */
	if (cipher->setKey(key) == false) // Shows error message if invalid key is entered
	{
		cout << "Invalid key." << endl;
		cout << "– PLF: String of regular letters. Ex: kingdom...\n"<<
				"– RTS: Separated by (,) integers. Ex: 5,2,1,3,4\n"<<
				"– RFC: An integer. Ex: 4\n"<<
				"– VIG: String of regular letters. Ex: security...\n"<<
				"– CES: An integer 1-25. Ex: 7\n"<<
				"- MAC: Doesnt require any key\n"<<
				"– HIL: 4 integers separated by (,). Ex: 3,4,9,7...\n";
		cout << "Execution: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>\n";
		exit(-1);
	}

	//encryption
	if (mode == "ENC")
	{
		string cipherText = cipher->encrypt(inputData);
		cout << "Post-Encryption Ciphertext: "<< cipherText<<endl;
		outputData = cipherText;
	}

	/* Perform decryption */
	else if (mode == "DEC")
	{
		string plainText = cipher->decrypt(inputData);
		cout << "Post-Decryption Plaintext: "<< plainText<<endl;
		outputData = plainText;
	}
	else
	{
		cout << "Please enter: ENC (encryption) or DEC (decryption)"<< endl;
		cout << "Execution: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>\n";
	}

	// writing output file
	ofstream writeFile;
	writeFile.open(outputFile);
	writeFile << outputData;
	writeFile.close();

	return 0;
}
