/*

		Taking the simple XOR encryption using pre-defined static (hard-coded) private key.

		Generates a NULL-terminated binary-string output (1's and 0's) instead of decimal number output.

		Deciphers the binary-string ciphertext back into plaintext and verifies output.

		Can verify the process using this nifty website:
		https://www.dcode.fr/xor-cipher

		Copy the output text into "TEXT TO BE XORED"
		Copy the XOR key into "ASCII KEY"
		Results format to ASCII.
		Go!

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to XOR decrypt a binary ciphertext and convert to plaintext
char *xorDecryptFromBinary(const char *binaryCipher, const char *xorKey)
{
	int cipherLength = strlen(binaryCipher);
	int keyLength = strlen(xorKey);

	char *decryptedText = malloc(cipherLength / 8 + 1); // 8-bit chunks plus 1-bit for the null terminator

	// check that we have allocated memory properly
	if (decryptedText == NULL)
	{
		fprintf(stderr, "Memory allocation failed: NULL\n");
		exit(EXIT_FAILURE);
	}

	// cycle through the binary cipher text and extract chunks for conversion
	for (int i = 0; i < cipherLength; i += 8)
	{
		char binaryChunk[9]; // 8 bits + null terminator
		// Grab the next 8-bit chunk
		strncpy(binaryChunk, binaryCipher + i, 8);
		binaryChunk[8] = '\0';

		// convert the 8-bit chunk into a decimal number
		int decimalValue = (int)strtol(binaryChunk, NULL, 2);

		// XOR each decimal value with the key: using corresponding characters from the string with the key
		char decryptedChar = (char)(decimalValue ^ xorKey[i / 8 % keyLength]);

		// Append the decrypted character to the result string
		decryptedText[i / 8] = decryptedChar;
	}

	// Make the final sequence NULL-terminated
	decryptedText[cipherLength / 8] = '\0';

	return decryptedText;
}

// Function to XOR encrypt a string and convert it to binary string
void xorEncryptToBinary(char *plaintext, char *key, char *binarySequence)
{
	int len = strlen(plaintext);
	int keyLen = strlen(key);

	for (int i = 0; i < len; i++)
	{
		// XOR the string with the key: one character from string with the corresponding character from the key
		char encryptedChar = plaintext[i] ^ key[i % keyLen];

		// Convert the XOR result to binary
		for (int j = 7; j >= 0; j--)
		{
			binarySequence[(i * 8) + (7 - j)] = ((encryptedChar >> j) & 1) + '0'; // pad with zeros if needed
		}
	}

	// Make the sequence NULL-terminated
	binarySequence[len * 8] = '\0';
}

int main()
{
	// Sample configuration
	char plaintext[] = "This is plaintext that will be XOR encrypted with the xorKey!";
	char xorKey[] = "<<< Replace SecretKey With YOUR SecretKey >>>";
	char binarySequence[(strlen(plaintext) * 8) + 1]; // +1 for the null terminator

	// Display the pre-encryption settings
	printf("Plaintext: \n%s\n\n", plaintext);
	printf("XOR Key: \n%s\n\n", xorKey);

	// XOR encrypt plaintext with xorKey and produce a NULL-terminated binarySequence
	xorEncryptToBinary(plaintext, xorKey, binarySequence);

	// Display the encryption outcome
	printf("XOR Encrypted Binary Sequence: \n%s\n\n", binarySequence);

	// Run a decryption on the binary ciphertext
	char *decryptedText = "DID NOT WORK"; // set the placeholder as FAILED if the decryption does not update the decryptedText
	printf("Pre-decrypted text is: \n%s\n\n", decryptedText);

	// Call the XOR decryption of the binary ciphertext with the xorKey
	decryptedText = xorDecryptFromBinary(binarySequence, xorKey);

	// Sanity check
	printf("Working Decrypted Text is: \n%s\n", decryptedText); // if the decryption worked, the output is not "FAILED"

	return 0;
}
