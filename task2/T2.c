#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char buf[100]; // buffer hold one row of inputs 
	int temp; // temperature value
	int log[10]; // array with all temperature logs
	int count = 0; // keep track of log-array index
	
	// unsigned ints for bit manipulation
	unsigned int value; // to store the input value of each row
	unsigned int type; // bit 26, 27, 28 - "type" of data
	unsigned int reserved; // bit 29, 30, 31 - should all be zero
	
	while(1){
		
		// read the next row in standard input  
		if (fgets(buf, sizeof(buf), stdin) == NULL){
			return 0; // quit the program if reached end of file
		}
		    
		sscanf(buf, "%x", &value); // convert the input char array into a value, interpreted as hexadecimal
		
		type = (value >> 26) & 0b000111; // keep only the type-bits
		reserved = (value >> 29); // 
		
		// jump to the next loop iteration if reserved bits are not zero
		if (reserved != 0){
			printf("Input Error\n");
			continue;
		}
		
		// look at type to determine what the action should be
		switch(type){
			
			case 0b000:
				// check if log is full
				if (count == 10){
					printf("Log Full\n");
					break;
				}
				
				// add temperature to log if log is not full
				temp = value & 0x3FFFFFF; // mask away reserved and type bits (keep data)	
				log[count] = temp;
				count ++;
				printf("Received Temperature: %d\n", temp);
				break;
				
			case 0b010:
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

			case 0b011:
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

			case 0b100:
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

			case 0b101:
				// iterate through and print every value in log
				printf("Log: %d entries\n", count);
				for (int i=0; i<count; i++){
					printf("Temperature: %d\n", log[i]);
				}
				break;

			case 0b110:
				// quit program by running return
				printf("Exiting...\n");
				return 0;
				
			default: // any other input than above stated is an error
				printf("Input Error\n");
		}
	}

	return 0;
}

