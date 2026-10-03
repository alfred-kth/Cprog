#ifndef T3_H
#define T3_H


// Define a struct to log the different data and keep track of log
#define LOG_SIZE 10
typedef struct {
	unsigned int temp[LOG_SIZE];
	unsigned int humidity[LOG_SIZE];
	unsigned int count;
} SensorLog;

// function for handling all the different actions
int action(unsigned int type, unsigned int temp, unsigned int humidity, SensorLog *log);

#endif
