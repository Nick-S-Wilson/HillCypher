// Nick Wilson
// Lab 2 Hill Cypher

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>


using namespace std;

int main() {

	//declarations (move to the header)
	char KeyLetterMatrix[3][3];			// key matrix of letters (read in from file)
	int KeyNumberMatrix[3][3];			// key matrix of numbers (converted in function)

	char HeloLetterMatrix[3][3];		// heloworld matrix of letters (fill matrix in header as well)
	int HeloNumberMatrix[3][3];			// heloworld matrix of numbers (converted in function)

	int EncryptMatrix[3][3];			// filled after multiplication (encryption)
	int CofactorMatrix[3][3];			// filled with cofactor of key matrix
	int FlippedCofactorMatrix[3][3];	// cofactor matrix's rows and columns flipped
	float InverseMatrix[3][3];			// filled after inverse calculation (possible float)

	int DecryptMatrix[3][3];			// filled after decryption
	char DecryptLetterMatrix[3][3];		// converted decryption matrix to letters

	void passArrays(char CharArr[3][3], int IntArr[3][3]);									// Converts Letters into Numbers
	void EncryptArrays(int IntArrOne[3][3], int IntArrTwo[3][3], int IntArrThree[3][3]);	// Multiplies the two arrays for encryption and fills the third
	void CofactorArrays(int KeyArr[3][3], int CoArr[3][3]);									// Calculates cofactor matrix
	void FlipCofactorMatrix(int CoArr[3][3], int FlipArr[3][3]);							// flips the cofactor matrix's rows and columns
	void DecryptArrays(int IntArrOne[3][3], float IntArrTwo[3][3], int IntArrThree[3][3]);	// Multiplies the two arrays for decryption and fills the third
	void DecryptLetters(char CharArr[3][3], int IntArr[3][3]);								// converts decrypted matrix back to plain text

	int Det = 0;


	ifstream myfile;
	myfile.open("D:\key.txt");		//opens text file with the key

	char a;		//temp character variable to read in from file to fill array

				//loop filling the key letter matrix
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			myfile.get(a);
			KeyLetterMatrix[i][j] = a;
		}
	}


	//call the conversion function for the key matrix
	passArrays(KeyLetterMatrix, KeyNumberMatrix);


	//print out key number matrix
	cout << "Key Number Matrix:" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << KeyNumberMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;


	// filling heloworld letter matrix (move to header?)*******
	HeloLetterMatrix[0][0] = 'h';
	HeloLetterMatrix[0][1] = 'e';
	HeloLetterMatrix[0][2] = 'l';
	HeloLetterMatrix[1][0] = 'o';
	HeloLetterMatrix[1][1] = 'w';
	HeloLetterMatrix[1][2] = 'o';
	HeloLetterMatrix[2][0] = 'r';
	HeloLetterMatrix[2][1] = 'l';
	HeloLetterMatrix[2][2] = 'd';


	//call the conversion function for heloworld matrix
	passArrays(HeloLetterMatrix, HeloNumberMatrix);



	//print out heloworld number matrix
	cout << "Message Number Matrix: " << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << HeloNumberMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;


	// calls the Matrix Multiplication function for encryption and prints it
	EncryptArrays(HeloNumberMatrix, KeyNumberMatrix, EncryptMatrix);



	//calculate inverse
	CofactorArrays(KeyNumberMatrix, CofactorMatrix);	//calculates cofactor matrix

														//find determinant
	Det = KeyNumberMatrix[0][0] * CofactorMatrix[0][0] + KeyNumberMatrix[0][1] * CofactorMatrix[0][1] + KeyNumberMatrix[0][2] * CofactorMatrix[0][2];
	Det = Det % 26;
	if (Det < 0)
	{
		Det += 26;
	}


	//flips cofactors rows and columns
	FlipCofactorMatrix(CofactorMatrix, FlippedCofactorMatrix);

	//Modulo 26 of Flipped Cofactor Matrix
	cout << endl << endl << "Inverse Matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			FlippedCofactorMatrix[i][j] *= 17;
			InverseMatrix[i][j] = FlippedCofactorMatrix[i][j] % 26;
			if (InverseMatrix[i][j] < 0)
			{
				InverseMatrix[i][j] += 26;
			}
			cout << InverseMatrix[i][j] << " ";
		}
		cout << endl;
	}


	cout << endl;



	//decryption multiplication
	DecryptArrays(EncryptMatrix, InverseMatrix, DecryptMatrix);


	//conversion to plaintext
	DecryptLetters(DecryptLetterMatrix, DecryptMatrix);


	//print plaintext decrypted
	cout << "Decrypted Matrix in Plaintext: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << DecryptLetterMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	myfile.close();

	system("pause");
	return 0;

}


void passArrays(char CharArr[3][3], int IntArr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'a')
				IntArr[i][j] = 0;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'b')
				IntArr[i][j] = 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'c')
				IntArr[i][j] = 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'd')
				IntArr[i][j] = 3;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'e')
				IntArr[i][j] = 4;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'f')
				IntArr[i][j] = 5;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'g')
				IntArr[i][j] = 6;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'h')
				IntArr[i][j] = 7;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'i')
				IntArr[i][j] = 8;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'j')
				IntArr[i][j] = 9;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'k')
				IntArr[i][j] = 10;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'l')
				IntArr[i][j] = 11;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'm')
				IntArr[i][j] = 12;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'n')
				IntArr[i][j] = 13;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'o')
				IntArr[i][j] = 14;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'p')
				IntArr[i][j] = 15;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'q')
				IntArr[i][j] = 16;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'r')
				IntArr[i][j] = 17;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 's')
				IntArr[i][j] = 18;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 't')
				IntArr[i][j] = 19;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'u')
				IntArr[i][j] = 20;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'v')
				IntArr[i][j] = 21;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'w')
				IntArr[i][j] = 22;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'x')
				IntArr[i][j] = 23;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'y')
				IntArr[i][j] = 24;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CharArr[i][j] == 'z')
				IntArr[i][j] = 25;
		}
	}


}


void EncryptArrays(int IntArrOne[3][3], int IntArrTwo[3][3], int IntArrThree[3][3])
{

	// 1 = key
	// 2 = message
	// 3 = new

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			IntArrThree[i][j] = 0;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				IntArrThree[i][j] += IntArrOne[i][k] * IntArrTwo[k][j];
			}

		}


	}


	cout << "Encrypted Message Matrix: " << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			IntArrThree[i][j] = IntArrThree[i][j] % 26;
			cout << IntArrThree[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;


}


void CofactorArrays(int KeyArr[3][3], int CoArr[3][3])
{
	CoArr[0][0] = KeyArr[1][1] * KeyArr[2][2] - KeyArr[1][2] * KeyArr[2][1];
	CoArr[0][1] = KeyArr[1][0] * KeyArr[2][2] - KeyArr[1][2] * KeyArr[2][0];
	CoArr[0][2] = KeyArr[1][0] * KeyArr[2][1] - KeyArr[1][1] * KeyArr[2][0];

	CoArr[1][0] = KeyArr[0][1] * KeyArr[2][2] - KeyArr[0][2] * KeyArr[2][1];
	CoArr[1][1] = KeyArr[0][0] * KeyArr[2][2] - KeyArr[0][2] * KeyArr[2][0];
	CoArr[1][2] = KeyArr[0][0] * KeyArr[2][1] - KeyArr[0][1] * KeyArr[2][0];

	CoArr[2][0] = KeyArr[0][1] * KeyArr[1][2] - KeyArr[0][2] * KeyArr[1][1];
	CoArr[2][1] = KeyArr[0][0] * KeyArr[1][2] - KeyArr[0][2] * KeyArr[1][0];
	CoArr[2][2] = KeyArr[0][0] * KeyArr[1][1] - KeyArr[0][0] * KeyArr[1][0];


	CoArr[0][1] *= -1;
	CoArr[1][0] *= -1;
	CoArr[1][2] *= -1;
	CoArr[2][1] *= -1;

	//test output, please remove
	cout << "cofactor matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << CoArr[i][j] << " ";
		}
		cout << endl;
	}

}

void FlipCofactorMatrix(int CoArr[3][3], int FlipArr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			FlipArr[j][i] = CoArr[i][j];
		}

	}

	//test output, please remove
	cout << endl << "flipped cofactor matrix: " << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << FlipArr[i][j] << " ";
		}
		cout << endl;
	}


}

void DecryptArrays(int IntArrOne[3][3], float IntArrTwo[3][3], int IntArrThree[3][3])
{

	// 1 = Encrypted matrix
	// 2 = Inverse of Key
	// 3 = Decrypted

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			IntArrThree[i][j] = 0;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				IntArrThree[i][j] += IntArrOne[i][k] * IntArrTwo[k][j];
			}

		}


	}


	cout << "Decrypted Message Matrix Pre Modulo: " << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << IntArrThree[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;



	cout << "Decrypted Message Matrix Post Modulo: " << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			IntArrThree[i][j] = IntArrThree[i][j] % 26;
			if (IntArrThree[i][j] < 0)
			{
				IntArrThree += 26;
			}
			cout << IntArrThree[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;


}


void DecryptLetters(char CharArr[3][3], int IntArr[3][3])
{


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 0)
				CharArr[i][j] = 'a';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 1)
				CharArr[i][j] = 'b';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 2)
				CharArr[i][j] = 'c';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 3)
				CharArr[i][j] = 'd';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 4)
				CharArr[i][j] = 'e';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 5)
				CharArr[i][j] = 'f';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 6)
				CharArr[i][j] = 'g';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 7)
				CharArr[i][j] = 'h';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 8)
				CharArr[i][j] = 'i';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 9)
				CharArr[i][j] = 'j';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 10)
				CharArr[i][j] = 'k';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 11)
				CharArr[i][j] = 'l';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 12)
				CharArr[i][j] = 'm';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 13)
				CharArr[i][j] = 'n';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 14)
				CharArr[i][j] = 'o';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 15)
				CharArr[i][j] = 'p';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 16)
				CharArr[i][j] = 'q';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 17)
				CharArr[i][j] = 'r';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 18)
				CharArr[i][j] = 's';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 19)
				CharArr[i][j] = 't';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 20)
				CharArr[i][j] = 'u';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 21)
				CharArr[i][j] = 'v';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 22)
				CharArr[i][j] = 'w';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 23)
				CharArr[i][j] = 'x';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 24)
				CharArr[i][j] = 'y';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IntArr[i][j] == 25)
				CharArr[i][j] = 'z';
		}
	}



}