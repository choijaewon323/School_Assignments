#include <iostream>
using namespace std;

int main() {
	unsigned char LEDs;

	for (int i = 0; i < 4; i++) {
		LEDs = 0x01;
		printf("%d ", LEDs);

		for (int j = 0; j < 7; j++) {
			LEDs <<= 1;
			printf("%d ", LEDs);
		}

		for (int j = 0; j < 7; j++) {
			LEDs >>= 1;
			printf("%d ", LEDs);
		}
	}

	return 0;
}