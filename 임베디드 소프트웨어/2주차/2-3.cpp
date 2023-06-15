#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int LED_function(int input) {
	unsigned char LEDs;

	LEDs = (1 << input);

	return LEDs;
}

int countOfOne(unsigned char input) {
	int result = 0;

	if (input & 0x80) {
		result++;
	}
	if (input & 0x40) {
		result++;
	}
	if (input & 0x20) {
		result++;
	}
	if (input & 0x10) {
		result++;
	}
	if (input & 0x08) {
		result++;
	}
	if (input & 0x04) {
		result++;
	}
	if (input & 0x02) {
		result++;
	}
	if (input & 0x01) {
		result++;
	}

	return result;
}

int resultOfCount(int count) {
	unsigned char result = 0x00;
	int flag = 7;
	for (int i = 0; i < count; i++) {
		result |= LED_function(flag);
		flag--;
	}
	return result;
}

int main() {
	unsigned char LEDs;

	scanf("%hhu", &LEDs);

	int count = countOfOne(LEDs);
	int result = resultOfCount(count);

	cout << "1의 개수? " << count << '\n';
	cout << "Shift 시의 값은? " << result << '\n';

	return 0;
}