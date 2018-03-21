#include "Monoalphabetic.h"
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
int MonoKey;

bool Monoalphabetic::setKey(const string& key)
{
	if (!(MonoKey >= stoi(key)))
	{
    return false;
	}
	else
	{
  	return true;
  }
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Monoalphabetic::encrypt(const string& plainText)
{
	string encryptText ="";
	// Assigning ascii value to the letter,
	//ASCII value: A = 65, B = 66 ... Z = 90
	// Adding the ascii value depending on the key value
	for (int i=0; i<plainText.length(); i++)
	{
		int Value = int(plainText[i]) + 4;

		if (!(Value <= 90))
		{
			Value = (Value - 90) + 64;
			encryptText = encryptText + char(Value);
		}
		else
		{
			encryptText = encryptText + char(Value);
		}
	}
	return encryptText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Monoalphabetic::decrypt(const string& cipherText)
{
	string decryptText ="";

	// Assigning ascii value to the letter,
	//ASCII value: A = 65, B = 66 ... Z = 90
	// Adding the ascii value depending on the key value
	for (int i=0; i<cipherText.length(); i++)
	{
		int Value = int(cipherText[i]) - 4;

		if (!(Value >= 65))
		{
			Value = 90-(65-Value);
			decryptText = decryptText + char(Value);
		}
		else
		{
			decryptText = decryptText + char(Value);
		}
	}
	return decryptText;
}
