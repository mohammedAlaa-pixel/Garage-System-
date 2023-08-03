
#include <avr/io.h>
#include "LCD.h"
#include "timer.h"
#define F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	LCD_vInit();
	LCD_vSend_string("there are 0 cars");
	LCD_movecursor(2,1);
	LCD_vSend_string("garage has space");
	signed char flag1=0,flag2=0,IR1,IR2,counter=0;
    while(1)
    {
         IR1=DIO_u8read('D',0);
		 if(IR1==1 && flag1==0 && counter<3)
		 {
			 counter++;
			 LCD_movecursor(1,11);
			 LCD_vSend_char(counter+48);
			 flag1=1;
			  if(counter==3)
			  {
				 LCD_clearscreen();
				 LCD_vSend_string("there are 3 cars");
				 LCD_movecursor(2,1);
				 LCD_vSend_string("garage is full");
			  }
			  timer1_wave_fastPWM_B(0.999999);
			  _delay_ms(1000);
			  timer1_wave_fastPWM_B(1.499999);
		 }
		 else if(IR1==0)
		 {
			 flag1=0;
		 }
		 
		 IR2=DIO_u8read('D',1);
		 if(IR2==1 && flag2==0 && counter>0)
		 {
			 counter--;
			 LCD_movecursor(1,11);
			 LCD_vSend_char(counter+48);
			 flag2=1;
			 
			 LCD_clearscreen();
			 LCD_vSend_string("there are ");
			 LCD_vSend_char(counter+48);
			 LCD_vSend_string(" cars");
			 LCD_movecursor(2,1);
			 LCD_vSend_string("garage has space");
			 timer1_wave_fastPWM_A(0.999999);
			 _delay_ms(1000);
			 timer1_wave_fastPWM_A(1.499999);
		 }
		 else if(IR2==0)
		 {
			 flag2=0;
		 }
    }
}