#include <stdio.h>

int main(void)
{
	char c; // first input character, must be ascii, so stored in char 
	int temp; // temperatur integer, only positive
	int log[10]; // array with all temperature logs
	int count = 0; // keep track of array index
	int running = 1;
	
	while(running == 1){
		if (scanf(" %c", &c) != 1){
			break;
			}
		switch(c){
			case 't':
			case 'T':
				if (count == 10){
					printf("Log Full\n");
					break;
				}
				
				if (scanf("%d", &temp) == 1) {
					log[count] = temp;
					count ++;
					printf("Received Temperature: %d\n", temp);
				}
				else printf("Input Error\n");
				break;
			case 'a':
			case 'A':
				if (count == 0){
					printf("Average Temperature: N/A\n");
					break;
				}
				
				float average = 0;
				for (int i=0; i<count; i++) average += log[i];
				average = average/count;
				printf("Average Temperature: %.2f\n", average);
				break;
			case 'n':
			case 'N':
				if (count == 0){
					printf("Minimum Temperature: N/A\n");
					break;
				}
				
				int minimum = log[0];
				for (int i=1; i<count; i++) if (minimum>log[i]) minimum = log[i];
				printf("Minimum Temperature: %d\n", minimum);
				break;
			case 'x':
			case 'X':
				if (count == 0){
					printf("Maximum Temperature: N/A\n");
					break;
				}
				
				int maximum = log[0];
				for (int i=1; i<count; i++) if (maximum<log[i]) maximum = log[i];
				printf("Maximum Temperature: %d\n", maximum);
				break;
			case 'l':
			case 'L':
				printf("Log: %d entries\n", count);
				for (int i=0; i<count; i++){
					printf("Temperature: %d\n", log[i]);
				}
				break;
			case 'q':
			case 'Q':
				printf("Exiting...\n");
				running = 0;
				return 0;
			default:
				printf("Input Error\n");
		}
		
		// clear the rest of the input characters (newline, extra characters added)
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF){}
	
	}
	
	return 0;
}














