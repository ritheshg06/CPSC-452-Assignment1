#include "Railfence.h"
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
int RailfenceKey;

bool Railfence::setKey(const string& key)
{
	if (RailfenceKey =  stoi(key))
	{
		cout << "Railfence key: "<< RailfenceKey <<endl;
		return true;
	}
	else
		return false;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Railfence::encrypt(const string& plainText)
{
	string encryptText ="";
	int stringLength = plainText.length();
	int rowLength = stringLength / RailfenceKey;
	int extraLetterRows = stringLength % RailfenceKey;
	int index = 0, rowIndex = 0;

	// run through the entire plaintext
	while (encryptText.length() < plainText.length() )
	{

		if (!(rowIndex < extraLetterRows))
		{
			// if it's a regular row, then do for loop of rowlength
			for (int i = 0; i < rowLength; i++)
			{
				// apprehend the appropriate char from the plaintext index
				encryptText = encryptText + plainText[index];
				// then increment the index by key value
				index = index + RailfenceKey;
			}

			// increment the row index after a row is finished processing
			rowIndex++;
			index = rowIndex;
		}

		// if it's a row with extra letter do for loop of rowlength+1
		else
		{
			for (int i = 0; i < rowLength+1; i++)
			{
				// apprehend the appropriate char from the plaintext index
				encryptText = encryptText + plainText[index];
				// increment the index by key value
				index = index + RailfenceKey;
			}

			// increment the row index after a row is finished processing
			rowIndex++;
			index = rowIndex;
		}
	}

	return encryptText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Railfence::decrypt(const string& cipherText)
{
	string decryptText ="";

	int stringLength = cipherText.length();
	int rowLength = stringLength / RailfenceKey;
	int extraLetterRows = stringLength % RailfenceKey;
	int index = 0;
	int rowIndex = 0;
	int Count = 0;

	// run through the entire plaintext
	while (decryptText.length() < cipherText.length() )
	{
		rowIndex = 0;
		index = Count;

		for (int i = 1; i< RailfenceKey+1; i++)
		{
			if ( decryptText.length() < cipherText.length() )
			{
				decryptText = decryptText + cipherText[index];
			}

			if (!(rowIndex < extraLetterRows))
			{
				index = index + rowLength ;
			}
			else
			{
				index = index + rowLength + 1  ;
			}
			rowIndex++;
		}

		Count++;
	}

	return decryptText;
}
