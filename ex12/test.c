#include <stdio.h>

int main(){
	char x[4] = {65, 66, 67, '\0'};
	printf("%s\n", x);
	int y = 4407873;
	printf("%s\n", (char*)&y);
}