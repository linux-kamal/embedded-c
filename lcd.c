#include "lcd.h"

/* to calulate shifting at port pins */
unsigned int val;
/* mention port's pin number*/

//static unsigned int *p;
/* 	always return a value from init function to 
	check weather it was executed successfully or not*/

void lcd_init()
{
	
	/* we can check for start_location to go beyond the range  0< and <7*/
	//start_location = 0;
	//STARTING_LOCATION = 0;
	/*ONLY DECLARE USED PINS AS OUTPUT 
	 WE WILL DO IT LATER */
	SIGNALDDR |=(1<<RS)|(1<<EN);
	LCDDATADIR =0xFF;
	LCDDATAPORT ^=	LCDDATAPORT; 
	SIGNALPORT ^= SIGNALPORT;

	clear();
	_delay_us(50);
	home();
	_delay_us(50);
	fourbitmode();	
	_delay_us(10);
	clear();	
	_delay_us(50);
	disponcursorblink();
	_delay_us(20);
}

void cmd(char cmd_value)
{
	char cmd_value1;
	//unsigned int STARTING_LOCATION=0;
	//STARTING_LOCATION = *p;
	// power function 
	val = pow(2,STARTING_LOCATION) + pow(2,(STARTING_LOCATION+1)) + pow(2,(STARTING_LOCATION+2)) + pow(2,(STARTING_LOCATION+3));
	cmd_value1 = (cmd_value>>(4-STARTING_LOCATION)) & val;		//mask lower nibble because PA4-PA7 pins are used. 
	lcdcmd(cmd_value1);			// send to LCD
 
	cmd_value1 = ((cmd_value<<STARTING_LOCATION) & val);	//shift 4-bit and mask
	lcdcmd(cmd_value1);			// send to LCD
}						
 
 
void printchar(char data_value)
{
	char data_value1;
	//unsigned int STARTING_LOCATION=0;
	//STARTING_LOCATION = *p;
	// power function
	val = pow(2,STARTING_LOCATION) + pow(2,(STARTING_LOCATION+1)) + pow(2,(STARTING_LOCATION+2)) + pow(2,(STARTING_LOCATION+3));
	data_value1=((data_value>>(4-STARTING_LOCATION)) & val);
	lcddata(data_value1);
 
	data_value1=((data_value<<STARTING_LOCATION) & val);
	lcddata(data_value1);
}
 
/* 	Inspite of writing 2 function use a single function
	for data & cmd just pass the RS , 0 for cmd and 1 for data for 
	use macro */
void lcdcmd(char cmdout)
{
	LCDDATAPORT = cmdout;
	SIGNALPORT &= ~(1<<RS);
	SIGNALPORT |= (1<<EN);
	_delay_ms(2);
	SIGNALPORT &= ~(1<<EN);
	_delay_us(100);
}
 
void lcddata(char dataout)
{
	LCDDATAPORT = dataout;
	SIGNALPORT |= (1<<RS);
	SIGNALPORT |= (1<<EN);
	_delay_ms(2);
	SIGNALPORT &= ~(1<<EN);
	_delay_us(100);
}


void printstring(char *buffer)
{
	char *localbuffer;
	localbuffer = buffer;
	uint8_t i=0;
	while(*(localbuffer+i) != '\0')
	{
		printchar(*(localbuffer+i));
		*(localbuffer+i) = '\0';
		i++;

	}
/*	buffer = NULL;
	buffer = '\0';
	localbuffer = NULL;
	localbuffer = '\0';
*/
}

void printinteger(signed int value)
{
	signed int localvalue, i;
	char buffer[50];
	localvalue = i = 1;
	localvalue = value;
	/* find the length*/
	do
	{
		value = value/10;
		i++;
	}while(value);
	if(value < 0)
		i++;
	sprintf((char*)buffer, "%d", localvalue);
	*(buffer+i) = '\0';
	printstring(buffer);
	
}

/* Y starting from 1 , X starting form 1*/
int locate(unsigned int X, unsigned int Y)
{
	uint8_t row;
	uint8_t colmn;
	uint8_t i;
	row = Y;
	colmn = X;

	if ((row>2)||(colmn>16))	
		return -1;
	
	switch(row)
	{
		case 1:	firstrow();
				break;
		case 2: secondrow();
				break;
		default:
				/*No operation required */
				break;
	}
	for(i=1;i<colmn;i++)
		shiftcursorright();
	return 0;
}
