#include "Playfair.h"
#include <iostream>
#include <algorithm>

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */

char Matrix[5][5];
string pKey;
string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // j --> i
string keyAndAlphabet = "";
string temp = "";
bool duplicate = false;

bool Playfair::setKey(const string& key)
{
	int charValue;
	pKey =  key;

	// verify all key chars are uppercase and valid letters and not special symbols
	for (int j=0; j<pKey.length(); j++)
	{
		charValue = int(pKey[j]);
		if (((charValue < 65) || (charValue > 90)) && ((charValue < 97) || (charValue > 122)))
		{
			return false;
		}

		pKey[j] = toupper(pKey[j]);
	}

	cout << "Playfair key: "<< pKey <<endl;

	return true;
}

// create Playfair Matrix using key and remaining alphabets
void Playfair::CreateMatrix()
{
	int count = 0;
	keyAndAlphabet = pKey + alphabet;

	// creating string with non-repeated alphabet letters to prepare for matrix insertion
	for (int k=0; k<keyAndAlphabet.length(); k++)
	{
		duplicate = false;

		for (int l=0; l<temp.length(); l++)
		{
			if ( (keyAndAlphabet[k] == 'J') && (temp[l] == 'I') )
			{
				duplicate = true;
			}
			else if (keyAndAlphabet[k] == temp[l])
			{
				duplicate = true;
			}
		}

		if (duplicate == false) //J --> I
		{
			if (keyAndAlphabet[k] == 'J')
			{
				temp = temp + 'I';

			}
			else
			{
				temp = temp + keyAndAlphabet[k];
			}
		}
	}


	// inserting key into 5*5 matrix
	for (int a=0; a<5; a++)
	{
		for (int b=0; b<5; b++)
		{
			Matrix[a][b] =  temp[count];
			count++;
		}
	}

	//print 5*5 matrix after inserting key
	for (int a=0; a<5; a++)
	{
		for (int b=0; b<5; b++)
		{
			cout << Matrix[a][b] <<" | ";
		}
		cout << endl;
	}
}

// find the value of row and column index for a letter in the matrix
void Playfair::FindMatrixIndex(char letter, int& row, int& col)
{
	for (int a=0; a<5; a++)
	{
		for (int b=0; b<5; b++)
		{
			if ( letter == Matrix[a][b] )
			{
				row = a;
				col = b;
			}
		}
	}
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plainText)
{
	CreateMatrix();

	string encryptedText ="";
	string filteredText ="";
	string newPlainText ="";

	int lI1 = 0;
	int lI2 = 1;

	int row1, row2;;
	int col1, col2;

	int plainTextIndex = 0;
	int newPos;

	int counter = 0,  xCounter = 0;

	//  all 'J' become 'I'	in plaintext
	for (int q=0; q<plainText.length(); q++)
	{
		if( plainText[q] == 'J')
	   	filteredText = filteredText + 'I';
		else
	  	filteredText = filteredText + plainText[q];
	}

	// add X to first letter for filling empty spaces
	for (int n=0; n<filteredText.length(); n++)
	{
		if ((counter%2==0) && (filteredText[counter-xCounter] == filteredText[counter-xCounter+1]))
		{
			newPlainText = newPlainText + filteredText[counter-xCounter];
			newPlainText = newPlainText + "X";
			counter = counter +2;
			xCounter++;
		}
		else
		{
			newPlainText = newPlainText + filteredText[counter-xCounter];
			counter++;
		}
	}

	// add x at the end of string for filling empty spaces
	if((newPlainText.length() % 2) == 1)
	{
		newPlainText = newPlainText + "X";
	}
	else
	{
		newPlainText = newPlainText;
	}

	while (plainTextIndex < newPlainText.length())
	{
		// find index of letter
		FindMatrixIndex( newPlainText[lI1], row1, col1);
		FindMatrixIndex( newPlainText[lI2], row2, col2);

		// rule for letters for same column
		if (col1 == col2)
		{
			newPos = row1+1;

			// if the new position is over the array limit, bring it back to 0
			if (newPos == 5)
			{
				newPos = 0;
			}
			encryptedText = encryptedText + Matrix[newPos][col1];

			newPos = row2+1;
			if (newPos == 5)
			{
				newPos = 0;
			}
			encryptedText = encryptedText + Matrix[newPos][col2];
		}
		// rule for letters for the same row
		else if (row1 == row2)
		{
			newPos = col1+1;
			if (newPos == 5)
			{
				newPos = 0;
			}
			encryptedText = encryptedText + Matrix[row1][newPos];

			newPos = col2+1;
			if (newPos == 5)
			{
				newPos = 0;
			}
			encryptedText = encryptedText + Matrix[row2][newPos];
		}
		// regular playfair rule
		else
		{
			encryptedText = encryptedText + Matrix[row1][col2];
			encryptedText = encryptedText + Matrix[row2][col1];
		}

		plainTextIndex = plainTextIndex +2;
		lI1 = lI1 + 2;
		lI2 = lI2 + 2;
	}
	return encryptedText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText)
{
	CreateMatrix();

	string decryptedText ="";
	string newCipherText ="";

	int newPos;
	int cipherTextIndex = 0;
	int lI1 = 0;
	int lI2 = 1;
	int row1, row2;
	int col1, col2;

	// all 'J' become 'I'	in plaintext
	for (int q=0; q<cipherText.length(); q++)
	{
		if ( cipherText[q] == 'J')
		newCipherText = newCipherText + 'I';
		else
		newCipherText = newCipherText + cipherText[q];
	}

	while (cipherTextIndex < newCipherText.length())
	{
		FindMatrixIndex( newCipherText[lI1], row1, col1);
		FindMatrixIndex( newCipherText[lI2], row2, col2);

		// letters for same column
		if (!(col1 == col2))
		{
			newPos = col1-1;
			if (newPos == -1)
			{
				newPos = 4;
			}
			decryptedText = decryptedText + Matrix[row1][newPos];

			newPos = col2-1;
			if (newPos == -1)
			{
				newPos = 4;
			}
			decryptedText = decryptedText + Matrix[row2][newPos];
		}
		// letters for the same row
		else if (!(row1 == row2))
		{
			decryptedText = decryptedText + Matrix[row1][col2];
			decryptedText = decryptedText + Matrix[row2][col1];
  	}
		// rule for regular letters
		else
		{
			newPos = row1-1;

			// if the new position is -1, bring it back to 4
			if (newPos == -1)
			{
				newPos = 4;
			}
			decryptedText = decryptedText + Matrix[newPos][col1];

			newPos = row2-1;
			if (newPos == -1)
			{
				newPos = 4;
			}
			decryptedText = decryptedText + Matrix[newPos][col2];
		}

		cipherTextIndex = cipherTextIndex +2;
		lI1 = lI1 + 2;
		lI2 = lI2 + 2;
	}

	return decryptedText;

}
