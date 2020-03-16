#include "base64.h"
#include <iostream>

/** Returns the amount of data written in the output
	if output is NULL returns the size needed for output
*/
int base64Encode(PBYTE input, int inputSize, char* output, int outputSize) {

	{
		// Formula: Integer part of inputSize divided by 3 times 4 
		// if the modulus of intputSize by 3 is greater than 0 add 4
		int sizeNeeded = ((inputSize / 3) * 4) + ((inputSize % 3) > 0 ? 4 : 0);
		
		if (output == NULL) 
			return sizeNeeded;
		
		if (outputSize != sizeNeeded)
			return 0;
			
	}
	
	memset (output,0,outputSize);
	
	int pos = 0;
	int baseValue = 1;
	
	int value, posValue, rest;
	PBYTE outputBytes = new BYTE[outputSize];
	
	memset(outputBytes, 0, outputSize);
	
	for (int i = 0; i < inputSize; i++) {
		
		value = 0;
		posValue = 0;
		rest = 0;
		
		if (pos % 4 == 0) {
			pos++;
		}
		
		// Formula to get baseValue of the position
		baseValue = getBaseValue(pos);
		
		value = input[i] * baseValue;
		rest = value / 64;
		posValue = value % 64;
		
		outputBytes[pos] = posValue;
		outputBytes[pos-1] = outputBytes[pos-1] + rest;
		
		pos++;
	}
	
	int bytesWritten = 0;
	int expectedTotal = ((inputSize/3)*4)+(inputSize % 3);
	
	for (int i = 0; i < outputSize; i++) {
		if (i > expectedTotal) {
			output[i] = '=';
			continue;
		}
		
		output[i] = base64mapping[outputBytes[i]];
		bytesWritten++;
	}
	
	delete[] outputBytes;
	
	return bytesWritten;
}

// Returns the amount of data written in the output
int base64Decode(char* input, int inputSize, PBYTE output, int outputSize) {
	
	PBYTE inputBytes = new BYTE[inputSize];
	
	int baseValue;
	
	int posOutput = 0;
	int leftOver = 0;
	
	for (int i = 0; i < inputSize; i++) {
		
		baseValue = getBaseValue(i);
		
		int value = findChar(base64mapping, 64, input[i]);
		if (value < 0) continue;
		
		int rest = value % baseValue;
		int posValue = value / baseValue;
		
		if (baseValue != 64) {
			
			output[posOutput] = posValue + (leftOver * 64 / baseValue);
			
			posOutput++;
		}
		
		leftOver = rest;
		
	}
	
	delete[] inputBytes;
	
	return 0;
}

int findChar(const char * arr, int arrSize, char charToFind) {
	int ret = -1;
	
	for (int i = 0; i < arrSize && ret < 0; i++) {
		if (arr[i] == charToFind) ret = i;
	}
	
	return ret;
}

int getBaseValue(int pos) {
	// 1 = 16, 2 = 4, 3 = 1
	return 16 * 1 / (pow(4,((pos % 4) - 1)));
}
