#include <stdio.h>

int main(void){

	DDRB |= 0b00100000;
	DDRD &= 0b11111011;
	while(1){
		if (PIND & 0b00000100){
			PORTB |= 0b00100000;
		}
		else{
			PORTB &= 0b11011111;
		}
	}
}