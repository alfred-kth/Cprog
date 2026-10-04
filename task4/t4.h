#ifndef T4_H
#define T4_H


// Define a struct to log the different data and keep track of log
typedef struct {
	unsigned int *temp;
	unsigned int *humidity;
	unsigned int count;
	unsigned int size;
	unsigned int increment;
} SensorLog;

// function for handling all the different actions
void action(unsigned int type, unsigned int temp, unsigned int humidity, SensorLog *log);

#endif
