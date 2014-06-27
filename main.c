/******************************************
Author 	:	Kamal BABU
About	:	LCD+UART Demo Code
*******************************************/

#include "header.h"
#include "lcd.h"
#include "uart.h"
#ifndef F_CPU 
#	define F_CPU 16000000UL
#endif

int main(void)
{
	char data0[11]="LCD TEST";
	char txbuff[] = "kamal";
	char rxbuffer[10];
	signed int val = 0;
	uint8_t byte_count = 0;

	char id1[10] = "55000E2B86";
	char id2[10] = "55000E209B";

	/* Initialization start here */
	_delay_ms(10);
	lcd_init();
	usart_init();
	_delay_us(10); 			
	printstring(data0);
	_delay_ms(2000);
	clear();
	//home();
	//while(1);
	locate(1,1);
	printstring("Loading System");
	
	for(val=0;val<=100;val++)
	{
		locate(1,2);
		printinteger(val);
		printchar('%');
		_delay_ms(200);
	}	
	_delay_ms(1000);
	clear();
	
	//_delay_ms(2000);;
	//clear();
	//txbyte('a');
	//txstring(txbuff,strlen(txbuff));
	locate(1,1);
	while(1)
	{
		//int check = ischarwaiting();
		if (ischarwaiting() > 0)
		{ 	
			
			rxbuffer[byte_count] = rxbyte();
			byte_count++;
			//clear();
			//printchar(var);
		}
		if (byte_count > 9) {
			*(rxbuffer + byte_count)= '\0';
			byte_count = 0;			
			printstring(rxbuffer);
			// string compare
			if(strcmp(rxbuffer, id2) == 0){
				printstring("match2");
			}
			if(strcmp(rxbuffer, id1) == 0){
				printstring("match1");
			}
			*rxbuffer = '\0';
			//asm ( "jmp 0x0000" );
		}
		
	}
	return 0;
}
