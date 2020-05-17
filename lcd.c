#include "DIO.h"
#include "lcd.h"

//mazidi page 444
// this function enable the trigger for the LCD to fetch data
void enable_trigger(void){
	DIO_WritePort(LCD_PORT, HIGH, (1<<LCD_EN));	// set the enable pin to high // b7dd l mask b eni ashfit 1 by l pin l mtwsl 3lha l enable
	_delay_us(1);
	DIO_WritePort(LCD_PORT, LOW, (1<<LCD_EN));	// set the enable pin to low
	_delay_us(2);
}

// this function sends instruction to the LCD in 4-bit mood
// it sends the the high nibble first then the low nibble
void send_command(uint8_t cmnd){

	DIO_WritePort(LCD_PORT, cmnd, DATA_MASK);		 // write the cmnd's high nibble to the four bits
	DIO_WritePort(LCD_PORT, LOW, (1<<LCD_RS)); // clear the RS pin to enable instuction mood
	enable_trigger();					 // enable the trigger for the LCD to fetch data
	_delay_us(20);						 // wait
	DIO_WritePort(LCD_PORT, (cmnd <<4), DATA_MASK); // write the cmnd's low nibble to the four bits
	enable_trigger() ;								
}


// this function sends character to the LCD to display 
// it sends the the high nibble first then the low nibble
void LCD_write_char(uint8_t character){

	// it operates the same way as the send_command function 
	DIO_WritePort(LCD_PORT, character, DATA_MASK);
	DIO_WritePort(LCD_PORT, HIGH, (1<<LCD_RS));
	enable_trigger();	
	DIO_WritePort(LCD_PORT,(character <<4), DATA_MASK);
	enable_trigger() ;

}

// this function initialize the LCD in 4-bit mood
void LCD_init(){

	DIO_InitPortDirection(LCD_PORT, OUTPUT, 0xFF);	// set the LCD port as output 
	DIO_WritePort(LCD_PORT, LOW, (1<<LCD_EN));		// clear the enable pin

	_delay_us(2000);
	send_command(0x33);					// command for 4-bit mood
	_delay_us(100);
	send_command(0x32);					// command for 4-bit mood
	_delay_us(100);
	send_command(0x28);					// command for 4-bit mood
	_delay_us(100);
	send_command(0x0E);					// display on, cursor on 
	_delay_us(100);
	send_command(0x01);					// clear LCD
	_delay_us(100);
	send_command(0x06);					// shift cursor right
	_delay_us(100);
}


// this function sets the cursor to a specific location  
// according to the lines addresses in the LCD

// Line   | Address Range 
//---------------------------------------
// Line 1 : 80 81 82 83 ... 8C 8D 8E 8F
// Line 2 : C0 C1 C2 C3 ... CC CD CE CF

void LCD_gotoxy(uint8_t x, uint8_t y){
	uint8_t firsAdr[] = {0x80, 0xC0} ;
	send_command(firsAdr[y-1] + x - 1);
	_delay_us(100);
}


// this functions sends character by character for the LCD to display
// it terminates when it reaches a NULL character which means that
// the string has ended
void LCD_display_string(char* str){
	uint8_t  i = 0;
	while(str[i]!=0){
		LCD_write_char(str[i]);
		i ++ ;	
	}
}

// clears the display 
void LCD_clear_display(){
	send_command(0x01) ;
}

// display an int on the LCD
void LCD_display_int(int decimal)
{
	//a memory to hold the transfered number into string
	char string[6] ;
	sprintf(string ,"%d" , decimal);		//use the sprintf to create a string of that number
	LCD_display_string(string);				//display that number as a string
}