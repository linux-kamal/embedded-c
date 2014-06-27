#ifndef _LCD_H
#define _LCD_H
#endif
/* Necessary Headers */
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


#ifndef NULL
	#define NULL (void*)0
#endif
//extern unsigned int start_location;
/* Just pass some Parameters */
//unsigned int start_location;
//start_location = 0;

#define STARTING_LOCATION 2

#define DATA	B
#define SIGNAL	B
#define _RS 0	
#define _EN 1
/*****************************/
/* LCD Commands */
#define clear()					cmd(LCD_CLEAR)
#define home()					cmd(LCD_HOME)		
#define fourbitmode()			cmd(LCD_4BITMODE)
#define decrement_cursor()		cmd(LCD_DCRCURSOR)
#define increment_cursor()		cmd(LCD_INCCURSOR)
#define shiftdispright()			cmd(LCD_SHIFTDISPR)
#define shiftdispleft()			cmd(LCD_SHIFTDISPL)
#define dispoffcursoroff()		cmd(LCD_DISPOFFCUROFF)
#define dispoffcursoron()		cmd(LCD_DISPOFFCURON)
#define disponcursoroff()		cmd(LCD_DISPONCUROFF)
#define disponcursoron()			cmd(LCD_DISPONCURON)
#define disponcursorblink()		cmd(LCD_DISPONCURBLI)
/* these two are working fine to shift cursor position left/right*/
#define shiftcursorleft()		cmd(LCD_SHIFTCURPOSL)
#define shiftcursorright()		cmd(LCD_SHIFTCURPOSR)
/*******************************************************/
#define shiftentiredispleft()	cmd(LCD_SHIFTDISPLEFT)
#define shiftentiredispright()	cmd(LCD_SHIFTDISPLEFR)
#define firstrow() 				cmd(LCD_CURSORFIRSTROW)
#define secondrow() 			cmd(LCD_CURSORSECONDROW)
#define inittwolines() 			cmd(LCD_TWOLINE5BY7MAT)

/* SIGNAL PORT  */
#define _CONCAT(i,j,k) i##j##k
#define P(a,b)	_CONCAT(P,a,b)

#define RS P(SIGNAL,_RS)	
#define EN P(SIGNAL,_EN)

#define SIGNALPORT	PORT(SIGNAL) 
#define SIGNALDDR	DDR(SIGNAL)
	
/*****************************/

/*   DATA PORT */
#define CONCAT(x,y) x##y

#define PORT(x) CONCAT(PORT,x) 
#define DDR(x) CONCAT(DDR,x)

#define LCDDATAPORT PORT(DATA)
#define LCDDATADIR  DDR(DATA)

/****************************/

#define LCD_CLEAR			0X01
#define LCD_HOME			0X02

#define LCD_DCRCURSOR		0X04
#define LCD_INCCURSOR		0X06

#define LCD_SHIFTDISPR		0X05
#define LCD_SHIFTDISPL		0X07

#define LCD_DISPOFFCUROFF	0X08
#define LCD_DISPOFFCURON	0X0A
#define LCD_DISPONCUROFF	0X0C
#define LCD_DISPONCURON		0X0E
#define LCD_DISPONCURBLI	0X0F

#define LCD_SHIFTCURPOSL	0X10
#define LCD_SHIFTCURPOSR	0X14

#define LCD_SHIFTDISPLEFT	0X18
#define LCD_SHIFTDISPLEFR	0X1C
#define LCD_CURSORFIRSTROW	0X80
#define LCD_CURSORSECONDROW	0XC0
#define LCD_4BITMODE		0X28
#define LCD_TWOLINE5BY7MAT	0X38

/* Functions Declarartions are here */
void lcd_init();
void cmd(char);
void printchar(char);
void lcdcmd(char);
void lcddata(char);
void printstring(char*);
void printinteger(signed int);
int locate(unsigned int, unsigned int);
/*************************************/
