#include "RowTransposition.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */

vector<int> vect;

bool RowTransposition::setKey(const string& key)
{
	int i;
	stringstream strstream(key);
	// input the key into a vector
	while (strstream >> i)
    {
        vect.push_back(i);
        if (strstream.peek() == ',')
            strstream.ignore();
    }
	return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string RowTransposition::encrypt(const string& plainText)
{
	string encryptText ="";

	int strLength = plainText.length();
	int colAmt = vect.size();
	int colLength = strLength / colAmt;
	int extraLetCol = strLength % colAmt;
	int index = 0, vectorIndex = 0;

	while (encryptText.length() < plainText.length() )
	{
		if ( (vect.at(vectorIndex) - 1) < extraLetCol)
		{
			for (int x = 0; x < colLength+1; x++)
			{
				index = x * colAmt + (vect.at(vectorIndex) - 1 );
				encryptText = encryptText + plainText[index];
			}
			vectorIndex++;
		}
		else
		{
			for (int x = 0; x < colLength; x++)
			{
				index = x * colAmt + (vect.at(vectorIndex) - 1 );
				encryptText = encryptText + plainText[index];
			}
			vectorIndex++;

		}
	}
	return encryptText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string RowTransposition::decrypt(const string& cipherText)
{
	string decryptText ="";

	int strLength = cipherText.length();
	int colAmt = vect.size(); // amount of columns
	int colLength = strLength / colAmt;
	int extraLetCol = strLength % colAmt;

	// create array to prepare for insertion
	string *arr = new string[colAmt];
	string tempStr = "";
	int index = 0;

	for (int j = 0; j < colAmt; j++)
	{
		if (vect.at(j) < extraLetCol+1)
		{
			for (int a = 0; a < colLength+1; a++)
			{
				tempStr = tempStr + cipherText[index];
				index++;
			}
			arr[(vect.at(j)-1)] = tempStr;
			tempStr="";
		}
		else
		{
			for (int a = 0; a < colLength; a++)
			{
				tempStr = tempStr + cipherText[index];
				index++;
			}
			arr[(vect.at(j)-1)] = tempStr;
			tempStr="";
		}

	}

	for (int p=0; p<colAmt; p++)
	{
		tempStr = tempStr + arr[p];
	}

	int strIndex = 0, rowIndex = 0, cycleCount = 0;

	while (decryptText.length() < tempStr.length() )
	{
		rowIndex = 0;
		strIndex = cycleCount;

		for (int y = 0; y<colAmt; y++)
		{
			if (decryptText.length() < tempStr.length())
			{
				decryptText = decryptText+ tempStr[strIndex];
			}
			if (rowIndex < extraLetCol)
			{
				strIndex = strIndex + colLength + 1;
			}
			else
			{
				strIndex = strIndex + colLength;
			}
			rowIndex++;
		}
		cycleCount++;
	}
	delete [] arr;

	return decryptText;
}
