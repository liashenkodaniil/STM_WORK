#include <stdint.h>
#include "stm32f4xx.h"

int main(void){
	(*RCC).AHB1ENR |= (1U | 1U << 1);
	for (volatile int i = 0; i <= 18; i+=2){
		(*GPIOA).MODER |= (1U << i);
		(*GPIOA).MODER &= ~(1U << (i + 1));
	}
	(*GPIOB).MODER &= ~((1U | (1U << 1)) << 28);
	int k = 0;
	while(1){
		if(((*GPIOB).IDR & (1U << 14)) != 0) {
			for(volatile int i = 0; i <= 5000; i++);
			if(((*GPIOB).IDR & (1U << 14)) != 0){
				if (k == 9)
					k = 0;
				(*GPIOA).BSRR = (1U << k);
				for(volatile int i = 0; i <= 1000000; i++);
				(*GPIOA).BSRR = (1U << (k + 16));
				k++;
			} else {
				k = 0;
			}
		} else {
			k = 0;
		}
	}
}
