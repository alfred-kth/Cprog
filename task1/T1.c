#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[100]; // buffer hold one row of inputs 
	int temp; // temperature 
	int log[10]; // array with all temperature logs
	int count = 0; // keep track of log-array index
	
	
	while(1){
		
		// read the next row in standard input  
		if (fgets(buf, sizeof(buf), stdin) == NULL){
			return 0; // quit the program if reached end of file
		}
		
		// look at first char in buf for what the action should be
		switch(buf[0]){
			
			case 'T':
				// check if log is full
				if (count == 10){
					printf("Log Full\n");
					break;
				}
				
				// add temperature to log if log is not full
				temp = atoi(&buf[1]);			
				log[count] = temp;
				count ++;
				printf("Received Temperature: %d\n", temp);
				break;
				
			case 'A':
				// check if anything in log
				if (count == 0){
					printf("Average Temperature: N/A\n");
					break;
				}
				
				// calculate and print average temperatur in log if not empty
				float average = 0;
				for (int i=0; i<count; i++) average += log[i];
				average = average/count;
				printf("Average Temperature: %.2f\n", average);
				break;

			case 'N':
				// check if anything in log
				if (count == 0){
					printf("Minimum Temperature: N/A\n");
					break;
				}
				
				// find minimum value in log if not empty
				int minimum = log[0];
				for (int i=1; i<count; i++) if (minimum>log[i]) minimum = log[i];
				printf("Minimum Temperature: %d\n", minimum);
				break;

			case 'X':
				// check if anything in log
				if (count == 0){
					printf("Maximum Temperature: N/A\n");
					break;
				}
				
				// find maximum value in log if not empty
				int maximum = log[0];
				for (int i=1; i<count; i++) if (maximum<log[i]) maximum = log[i];
				printf("Maximum Temperature: %d\n", maximum);
				break;

			case 'L':
				// iterate through and print every value in log
				printf("Log: %d entries\n", count);
				for (int i=0; i<count; i++){
					printf("Temperature: %d\n", log[i]);
				}
				break;

			case 'Q':
				// quit program by running return
				printf("Exiting...\n");
				return 0;
				
			default: // any other input than above stated is an error
				printf("Input Error\n");
		}
	}

	return 0;
}














