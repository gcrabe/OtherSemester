#include "stm32f30x.h"

int wait(unsigned int ms);
volatile int period;

extern unsigned long GlobalTime;
#define MAXGLOBALTIME 0x10000000

#define MAXN 4

unsigned int store[MAXN];
unsigned int data = 0;
unsigned int isr = 0;
unsigned int isEmptyStore = 0;

int main() {
	//unsigned int data = 0;
	
	RCC->APB2ENR |= 0x00004000; // tacting running on
	USART1->BRR = 0x228; //0x8a; 		// velocity
	USART1->CR1 |= 0x0000000d;	// turn on
	
	RCC->AHBENR |= 0x00020000; // влючение тактирования
	GPIOA->MODER |= 0x00280000; // alternative function for output
	GPIOA->AFR[1] = 0x00000770; // choise the function
}

void input() {
	main();
	
	while (1) {
		
		__disable_irq();
		isr = USART1->ISR;	
		
		if (isr & 0x00000008) {
			USART1->ICR |= 0x00000008;
		}
		
		if ((isr & 0x00000020) && !isEmptyStore) {
			data = USART1->RDR;
			isEmptyStore = 1;
		}
		
		__enable_irq();
	}
}

void output() {
	while (1) {
		
		__disable_irq();
		
		isr = USART1->ISR;
		if ((isr & 0x00000080) && isEmptyStore) {
			USART1->TDR = data;
			isEmptyStore = 0;
		}
		
		__enable_irq();
	}
}

void greatWork() {
	// init
	
	while (1) {
		//
	}
}

void *const Tasks[] __attribute__((at(0x08001000)))= {
	input,
	output,
	greatWork,
	greatWork,
	0
};
