#include "T3.h"
#include <stdio.h>
	
int action(unsigned int type, unsigned int temp, unsigned int humidity, SensorLog *log) 
{
	// look at type to determine what the action should be
	switch(type){
		
		case 0:
			// check if log is full
			if (log->count == 10){
				printf("Log Full\n");
				break;
			}
			
			// add temperature to log if log is not full
			log->temp[log->count] = temp;
			log->humidity[log->count] = humidity;
			log->count ++;
			printf("Received Temperature: %d\n", temp);
			printf("Received Humidity: %d\n", humidity);
			break;
			
		case 2:
			// check if anything in log
			if (log->count == 0){
				printf("Average Temperature: N/A\n");
				printf("Average Humidity: N/A\n");
				break;
			}
			
			// Print average Temperature
			float average = 0;
			for (int i=0; i<log->count; i++) average += log->temp[i];
			average = average/log->count;
			printf("Average Temperature: %.2f\n", average);
			
			// Print average Humidity
			average = 0;
			for (int i=0; i<log->count; i++) average += log->humidity[i];
			average = average/log->count;
			printf("Average Humidity: %.2f\n", average);
			break;

		case 3:
			// check if anything in log
			if (log->count == 0){
				printf("Minimum Temperature: N/A\n");
				printf("Minimum Humidity: N/A\n");
				break;
			}
			
			// Print minimum Temperature
			int minimum = log->temp[0];
			for (int i=1; i<log->count; i++) if (minimum>log->temp[i]) minimum = log->temp[i];
			printf("Minimum Temperature: %d\n", minimum);
			
			// Print minimum Humidity
			minimum = log->humidity[0];
			for (int i=1; i<log->count; i++) if (minimum>log->humidity[i]) minimum = log->humidity[i];
			printf("Minimum Humidity: %d\n", minimum);
			
			break;

		case 4:
			// check if anything in log
			if (log->count == 0){
				printf("Maximum Temperature: N/A\n");
				printf("Maximum Humidity: N/A\n");
				break;
			}
			
			// Print maximum Temperature
			int maximum = log->temp[0];
			for (int i=1; i<log->count; i++) if (maximum<log->temp[i]) maximum = log->temp[i];
			printf("Maximum Temperature: %d\n", maximum);
			
			// Print maximum Humidity
			maximum = log->humidity[0];
			for (int i=1; i<log->count; i++) if (maximum<log->humidity[i]) maximum = log->humidity[i];
			printf("Maximum Humidity: %d\n", maximum);
			break;

		case 5:
			// iterate through and print every value in log
			printf("Log: %d entries\n", log->count);
			for (int i=0; i<log->count; i++){
				printf("Temperature: %d; Humidity: %d\n", log->temp[i], log->humidity[i]);
			}
			break;

		case 6:
			// quit program by running return
			printf("Exiting...\n");
			return 1;
			
		default: // any other input than above stated is an error
			printf("Input Error\n");
			
	}
	
	return 0;
}




