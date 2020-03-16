#include <iostream>
#include "base64.h"

int main() {

	BYTE inArr[] = "Texto a ser colocado em base64 c";
	int sizeOut = base64Encode((PBYTE) inArr, 32, NULL, 0);
	
	char outArr[sizeOut];
	
	base64Encode((PBYTE) inArr, 32, outArr, sizeOut);
	
	std::cout << "Result Encode: " << outArr << std::endl;
	
	memset(inArr, 0, 32);
	
	base64Decode(outArr, sizeOut, inArr, 32);
	
	std::cout << "Result Decode: " << inArr << std::endl;
	
	return 0;
}