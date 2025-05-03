// Programação 2 Displays de 7 Segmentos

#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char dig7seg[16] = {  0x3F, 0x06, 0x5B, 0x4F, 
                      0x66, 0x6D, 0x7D, 0x07, 
                      0x7F, 0x6F, 0x77, 0x7C, 
                      0x39, 0x5E, 0x79, 0x71  };

void disp7seg_int( void ){
    DDRD  = 0xFF; //pino 0 ao 7 como saída
    PORTD = 0x00; //Zerando o port D
    DDRB |= (1<<0); //Pino 8 saída
    DDRB |= (1<<1); //Pino 9 saída
}

unsigned char disp7seg_dig =0;

void disp7seg( unsigned char d ){
    
    if(disp7seg_dig%2){
        PORTB &= ~(1<<1);
        PORTD = dig7seg[d%10];
        PORTB |= (1<<0);
    }else{
        PORTB &= ~(1<<0);
        PORTD = dig7seg[(d/10)%10];
        PORTB |= (1<<1);
    }

    disp7seg_dig++;
}

int main(void) {
    char t = 0;
    unsigned long n=0;

    disp7seg_int();
    while( 1 )
    {
        disp7seg(t);

        if((t%1000)==0){     
            t = ++t % 100;
        }
        _delay_ms(1);
        n++;
    }
}
