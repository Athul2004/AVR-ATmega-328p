/*
 * modular_1.c
 *
 * Created: 26-09-2025 20:44:53
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "athul.h"
#include<stdint.h>

int main(void)
{
    DDRB|=(1<<DDB5);

    while (1)
    {


        PORTB^=(1<<PORTB5);
        athul(1000);
    }
}


