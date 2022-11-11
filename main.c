#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, const char** argv) {
	/* Check arg count. */
	if (argc < 2) {
		printf("Not enough args!\n%s <hex string>\n", argv[0]);
		return 1;
	}

	/* Check size of string. */
	int strSize = strlen(argv[1]);
	if (strSize & 1) {
		printf("String must be an even length!\n");
		return 2;
	}

	/* Allocate array. */
	int arrSize = strSize / 2;
	uint8_t* values = malloc(arrSize);

	/* Convert string to hex. */
	int arrIdx = 0;
	int txtIdx = 0;
	const char* str = argv[1];
	while (arrIdx < arrSize) {
		for (int i = 0; i < 2; i++) {
			values[arrIdx] <<= 4;

			/* Check for decimal integer. */
			if ('0' <= str[txtIdx] && '9' >= str[txtIdx]) {
				values[arrIdx] |= str[txtIdx] - '0';
			}
			/* Check of uppercase hex. */
			else if ('A' <= str[txtIdx] && 'F' >= str[txtIdx]) {
				values[arrIdx] |= str[txtIdx] - 'A' + 10;
			}
			/* Check for lowercase hex. */
			else if ('a' <= str[txtIdx] && 'f' >= str[txtIdx]) {
				values[arrIdx] |= str[txtIdx] - 'a' + 10;
			}
			else {
				printf("All characters must be 0-9 and A-F!\n");
				return 3;
			}

			txtIdx++;
		}
		arrIdx++;
	}

	/* Print byte array. */
	int remaining = arrSize;
	for (int i = 0; i < (arrSize + 0xF) / 0x10; i++) {
		for (int j = 0; j < min(remaining, 0x10); j++) {
			printf("0x%02X, ", values[i * 0x10 + j]);
		}
		remaining -= 0x10;
		printf("\n");
	}

	return 0;
}