/*Diseñar un cronómetro que cuente de 0 a 60 segundos utilizando un display LCD. El cronómetro
  debe tener cuatro conteos, 3 implementados con los timers del PIC16F877 y otro que utilice
  la función delay_ms(). Los cuatro conteos se deben mostrar de forma simultánea en el display
  LCD. Cuando termine la cuenta debe permamecer el 60 en pantalla hasta que se reinicie el sistema
  a través de un pulsador. */
  
#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT //Características del PIC
#use delay(clock=4Mhz) //Frecuencia del PIC
#include <lcd.c>
#use standard_io(D)

long timer0 = 0, timer1 = 0, timer2 = 0, delay = 0, delay2 = 0, flag0 = 0, flag1 = 0, flag2 = 0;

#INT_TIMER0
void timer_0(void){
   if(timer0!=60){
      if(flag0>=19){
         timer0 = timer0 + 1;
         flag0 = 0;
      } else flag0 = flag0+1;
   }
   set_timer0(61);
}

#INT_TIMER1
void timer_1(void){
   if(timer1!=60){
      if(flag1 == 1){
         timer1 = timer1 + 1;
         flag1 = 0;
      } else flag1 = 1;
   }
   set_timer1(3036);
}

#INT_TIMER2
void timer_2(void){
   if(timer2!=60){
      if(flag2>=260){
         timer2 = timer2 + 1;
         flag2 = 0;
      } else flag2 = flag2+1;
   }
   set_timer2(178);
}

void main(){
   lcd_init();
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   set_timer0(61);
   enable_interrupts(INT_TIMER0);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(INT_TIMER1);
   setup_timer_2(T2_DIV_BY_1,250,16);
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);
   while (TRUE){
      printf(lcd_putc, "\fdel:%ld  TMR0:%ld\nTMR1:%ld TMR2:%ld", delay,timer0,timer1,timer2);
      if (delay!=60) {         
         delay_ms(1000);
         delay=delay+1;
      }
      else delay_ms(100);
      delay2= delay/1000;
   }
}
