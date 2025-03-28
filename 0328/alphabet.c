#include <stdio.h>
#define LOWERCASE 0
#define UPPERCASE 1

int isAlphabet(char x) {
	if (x >= 'a' && x <= 'z')
		return LOWERCASE;
	else if (x >= 'A' && x <= 'Z')
		return UPPERCASE;
	return -1;
}

int main() {
	while(1) {
		char x;
		
		printf("문자 입력: ");
		scanf(" %c", &x);

		if (x == '0')
			break;
		else if (isAlphabet(x) == LOWERCASE)
			printf("%c의 대문자는 %c입니다.\n", x, x ^ 32);
		else if (isAlphabet(x) == UPPERCASE)
			printf("%c의 소문자는 %c입니다.\n", x, x ^ 32);
		else
			printf("%c는 알파벳 문자가 아닙니다.\n", x);
	}

	return 0;
}		
