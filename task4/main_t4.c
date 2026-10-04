#include "t4.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char buf[100]; // buffer hold one row of inputs 
	unsigned int value; // stores the input value translated from hexadecimal
	
	// all the variables inside "value"
	unsigned int temp; // temperature value, first 13 bits
	unsigned int humidity; // humidity value, the next 13 bits
	unsigned int type; // bit 26, 27, 28 - "type" of data
	unsigned int reserved; // bit 29, 30, 31 - should all be zero
	
	SensorLog log = {0}; // temp and humidity logs with a count variable
	
	while(1){
		
		// read the next row in standard input  
		if (fgets(buf, sizeof(buf), stdin) == NULL){
			return 0; // quit the program if reached end of file
		}
		    
		sscanf(buf, "%x", &value); // convert the input char array into a value, interpreted as hexadecimal
		
		type = (value >> 26) & 0b000111; // keep only the type-bits
		
		if (type == 7){
			unsigned int increment; // temporary variable 
			increment = value & 0b00000011111111111111111111111111; // mask away reserved and type bits 
			if (increment <= 0){ // increment must be positive
				printf("Input Error\n");
				continue;
			}
			log.increment = increment; // update the real increment value in log
			printf("New Log Increment: %u\nCurrent Log Size: %u\n", log.increment, log.size);
			continue;
		}
	
		// first allocation of log
		if (log.size == 0){
			// check that log is initialized
			if (log.increment == 0) {
				printf("Log Not Initialized\n");
				continue;
			}
			// allocate space to logs
			log.size = log.increment;
			log.temp = malloc(log.size * sizeof *log.temp);
			log.humidity = malloc(log.size * sizeof *log.humidity);
			
			// check for successful allocation
			if (!log.temp || !log.humidity) {
			    free(log.temp);
			    free(log.humidity);
			    exit(1);
			}
			printf("Log Size Expanded To: %u\n", log.size);
		}
		
		
		reserved = value >> 29; // get the last three reserved bits
		humidity = (value >> 13) & 0b0000001111111111111; // get only the humidity bits
		temp = value & 0b000000000000000000011111111111; // get only the temperature bits
		
		// jump to the next loop iteration if reserved bits are not zero
		if (reserved != 0){
			printf("Input Error\n");
			continue;
		}
		
		action(type, temp, humidity, &log);
		
	}
}
	