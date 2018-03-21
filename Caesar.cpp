#include "Caesar.h"
#include <iostream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
int Key;

bool Caesar::setKey(const string& key)
{
	if (!(Key =  stoi(key)))
	{
    return false;
	}
	else
	{
  	cout << "Caesar key: "<< Key <<endl;
  	return true;
  }
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Caesar::encrypt(const string& plainText)
{
	string encryptText ="";
	// Assigning ascii value to the letter,
	//ASCII value: A = 65, B = 66 ... Z = 90
	// Adding the ascii value depending on the key value
	for (int i=0; i<plainText.length(); i++)
	{
		int lValue = int(plainText[i]) + Key;

		if(lValue <= 90)
		{
			encryptText = encryptText + char(lValue);
		}
		else
		{
			lValue = (lValue - 90) + 65;
			encryptText = encryptText + char(lValue);
		}
	}
	return encryptText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Caesar::decrypt(const string& cipherText)
{
	string decryptText ="";

	// Assigning ascii value to the letter,
	//ASCII value: A = 65, B = 66 ... Z = 90
	// Adding the ascii value depending on the key value
	for (int i=0; i<cipherText.length(); i++)
	{
		int lValue = int(cipherText[i]) - Key;

		if (lValue >= 90)
		{
			decryptText = decryptText + char(lValue);
		}
		else
		{
			lValue = 90-(65-lValue);
   		decryptText = decryptText + char(lValue);

		}
	}
	return decryptText;
}
