#include "Vigenere.h"
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
string vigKey;

bool Vigenere::setKey(const string& key)
{
	int charValue;
	vigKey =  key;

	// ensure all key are uppercase and valid letters
	for (int j=0; j<vigKey.length(); j++)
	{
		charValue = int(vigKey[j]);
		if (((charValue < 65) || (charValue > 90)) && ((charValue < 97) || (charValue > 122)))
		{
			return false;
		}

		vigKey[j] = toupper(vigKey[j]);
	}

	return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Vigenere::encrypt(const string& plainText)
{
	string encryptText ="";
	int keySize = vigKey.length();
	int index = 0;
	int temp;
	char newChar;

	while (encryptText.length() < plainText.length() )
	{
		for (int i = 0; i<keySize; i++)
		{
			temp = (int(vigKey[i]) - 65 ) + (int(plainText[index]) );

			// put the value into A-Z ASCII range, 65-90
			if (temp > 90)
			{
				temp = temp - 90 + 64;
			}
			if (temp > 64 && temp < 91)
			{
				newChar = char(temp);
				encryptText = encryptText + newChar;
			}

			index++;
		}
	}
	return encryptText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Vigenere::decrypt(const string& cipherText)
{
	string decryptText ="";
	int keySize = vigKey.length(), index = 0, temp;
	char newChar;

	while (decryptText.length() < cipherText.length() )
	{
		for (int i = 0; i<keySize; i++)
		{
			temp = ( int(cipherText[index]) - (int(vigKey[i]) - 65 )  );

			// put the value into A-Z ASCII range, 65-90
			if ( 65 > temp )
			{
				temp = 91 - (65 - temp);
			}

			if (64 < temp  && 91 > temp)
			{
				newChar = char(temp);
				decryptText = decryptText + newChar;
			}

			index++;
		}
	}

	return decryptText;
}
