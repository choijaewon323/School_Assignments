#include <iostream>
using namespace std;

int LED_function(int input) {
	unsigned char LEDs;
	
	LEDs = (1 << input);

	return LEDs;
}

int main() {
	int return_value;
	return_value = LED_function(3);

	printf("return_value:%d\n", return_value);

	return 0;
}